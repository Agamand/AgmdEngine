#include <Core\AgmdApp.h>
#include <Core\Renderer.h>
#include <Core\Enums.h>
#include <Windowsx.h>
#include <time.h>
#include <Loaders\Loaders.h>
#include <Core\Camera\FPCamera.h>
#include <Core\Camera\TPCamera.h>
#include <Core\GUI\GUIMgr.h>

namespace Agmd
{
	AgmdApp* AgmdApp::m_Application = NULL;
	
	AgmdApp::AgmdApp() : 
	m_Instance (GetModuleHandle("AgmdEngine.dll")),
	m_Hwnd     (NULL),
	m_IsRunning(true),
	camera	   (new TPCamera()),
	last_mouse_pos(0,0),
	mouseState(MOUSE_NONE),
	last_time(0),
	frame (0),
	m_fps (0),
	fps_timer(SECONDS_IN_MS)
	{
		assert(m_Instance != NULL);
		m_Application = this;

		RegisterLoaders();
	}

	AgmdApp::~AgmdApp()
	{
		if (m_Hwnd)
		{
			DestroyWindow(m_Hwnd);
			UnregisterClass("AgmdEngine", m_Instance);
		}
	}

	void AgmdApp::Run()
	{
		m_Renderer = new Plugin("OpenGLRenderer.dll");

		MakeWindow();

		Renderer::Get().Initialize(m_Hwnd);
		Renderer::Get().SetScreen(m_ScreenSize);
		Renderer::Get().SetCamera(camera);

		OnInit();

		MainLoop();
	}

	void AgmdApp::Exit()
	{
		m_IsRunning = false;
	}

	void AgmdApp::MakeWindow()
	{
		m_ScreenSize = ivec2(1280,720);
		const int left   = (GetDeviceCaps(GetDC(NULL), HORZRES) - m_ScreenSize.x)  / 2;
		const int top    = (GetDeviceCaps(GetDC(NULL), VERTRES) - m_ScreenSize.y) / 2;

		// Définition de la classe de la fenêtre
		WNDCLASSEX WindowClass;
		WindowClass.cbSize        = sizeof(WNDCLASSEX);
		WindowClass.style         = 0;
		WindowClass.lpfnWndProc   = GlobalWindowProc;
		WindowClass.cbClsExtra    = 0;
		WindowClass.cbWndExtra    = 0;
		WindowClass.hInstance     = m_Instance;
		WindowClass.hIcon         = NULL;
		WindowClass.hCursor       = 0;
		WindowClass.hbrBackground = 0;
		WindowClass.lpszMenuName  = NULL;
		WindowClass.lpszClassName = ENGINE_NAME;
		WindowClass.hIconSm       = NULL;
		RegisterClassEx(&WindowClass);

		// Création de la fenêtre
		m_Hwnd = CreateWindow(ENGINE_NAME, ENGINE_NAME, WS_SYSMENU, left, top, m_ScreenSize.x, m_ScreenSize.y, NULL, NULL, m_Instance, NULL);
		assert(m_Hwnd != NULL);
		ShowWindow(m_Hwnd, SW_NORMAL);
	}

	void AgmdApp::MainLoop()
	{
		MSG Message;
		while (m_IsRunning)
		{
			if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
			else
			{
				uint64 time = clock();
				uint64 time_diff = time - last_time;
				last_time = time;
				camera->OnUpdate(time_diff);
				GUIMgr::Instance().Update(time_diff);
				OnUpdate(time_diff);

				Renderer::Get().InitScene();
				OnRender();
				Renderer::Get().EndScene();
				frame++;

				if(fps_timer <= time_diff)
				{
					m_fps = ((float)frame*SECONDS_IN_MS)/(SECONDS_IN_MS + time_diff - fps_timer);
					fps_timer = SECONDS_IN_MS;
					frame = 0;
				}else fps_timer -= time_diff;

			}
		}
	}

	LRESULT CALLBACK AgmdApp::GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		return m_Application->WindowProc(Hwnd, Message, WParam, LParam);
	}


	LRESULT CALLBACK AgmdApp::WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		GUIMgr& guimgr = GUIMgr::Instance();
		if(Message == WM_CHAR)
		{

		}
		switch (Message)
		{
			// Destruction de la fenêtre = quitter
			case WM_DESTROY :
				Exit();
				return 0;
			case WM_KEYUP:
			case WM_KEYDOWN:
				camera->OnKeyboard((char)LOWORD(WParam),Message == WM_KEYUP ? true : false);
				switch(LOWORD(WParam))
				{
				case VK_F1:
					Renderer::Get().setRenderMode(MODE_FILL);
					return 0;
				case VK_F2:
					Renderer::Get().setRenderMode(MODE_LINE);
					return 0;
				case VK_F3:
					Renderer::Get().setRenderMode(MODE_POINT);
					return 0;
				case VK_F4:
					Renderer::Get().ReloadPipeline();
					return 0;
				}
				return 0;

			case WM_XBUTTONDOWN:
				mouseState |= MOUSE_NONE;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_RBUTTONDOWN:
				mouseState |= MOUSE_RIGHT;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_MBUTTONDOWN:
				mouseState |= MOUSE_MIDDLE;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_LBUTTONDOWN:
				mouseState |= MOUSE_LEFT;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;

			case WM_XBUTTONUP:
				mouseState &= ~MOUSE_NONE;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_RBUTTONUP:
				mouseState &= ~MOUSE_RIGHT;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_MBUTTONUP:
				mouseState &= ~MOUSE_MIDDLE;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_LBUTTONUP:
				mouseState &= ~MOUSE_LEFT;
				guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
				return 0;
			case WM_MOUSEWHEEL:
				camera->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(WParam));
				return 0;
			case WM_MOUSEMOVE:
				ivec2 posDiff = last_mouse_pos - ivec2(GET_X_LPARAM(LParam),m_ScreenSize.y-GET_Y_LPARAM(LParam));
				if(mouseState == MOUSE_RIGHT)
					camera->OnMouseMotion(posDiff.x, posDiff.y);
				last_mouse_pos.x = GET_X_LPARAM(LParam);
				last_mouse_pos.y = m_ScreenSize.y-GET_Y_LPARAM(LParam);
				guimgr.AddEvent(EventEntry(EV_ON_MOUVE_MOVE,last_mouse_pos,posDiff,mouseState,0));
				return 0;
		}
		return DefWindowProc(Hwnd, Message, WParam, LParam);
	}

}