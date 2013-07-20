/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/AgmdApp.h>
#include <Core/Renderer.h>
#include <Core/Enums.h>
#include <Core/MediaManager.h>
#include <Core/ResourceManager.h>
#include <Windowsx.h>
#include <time.h>
#include <Loaders/Loaders.h>
#include <Core/Camera/FPCamera.h>
#include <Core/Camera/TPCamera.h>
#include <Core/GUI/GUIMgr.h>
#include <Core/RenderingMode/RenderingMode.h>
#include <Core/SceneObject/Material.h>
#include <Core/Shader/ShaderPipeline.h>
#include <Core/Tools/Statistics.h>
#include <Debug/Profiler.h>

#include <chrono>

namespace Agmd
{
    AgmdApp* AgmdApp::m_Application = NULL;
    
    AgmdApp::AgmdApp(ivec2 screenSize) : 
    m_Instance      (GetModuleHandle("Agmd3D.dll")),
    m_Hwnd          (NULL),
    m_IsRunning     (true),
    camera          (NULL),
    last_mouse_pos  (0,0),
    mouseState      (MOUSE_NONE),
    last_time       (0),
    frame           (0),
    m_fps           (0),
    fps_timer       (SECONDS_IN_MS),
    m_ScreenSize    (screenSize)
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
        //if(m_RendererType = RENDERER_DIRECTX)
        //m_Renderer = new Plugin("DXRender.dll");
        //else
        m_Renderer = new Plugin("GLRender.dll");

        MakeWindow();

        Renderer::Get().Initialize(m_Hwnd);
        Renderer::Get().SetScreen(m_ScreenSize);

        Material* mat = new Material(ShaderPipeline::GetDefaultPipeline());
        ResourceManager::Instance().Add("DEFAULT_MATERIAL",mat);
        OnInit();

        MainLoop();
    }

    void AgmdApp::Exit()
    {
        m_IsRunning = false;
    }

    void AgmdApp::MakeWindow()
    {
        
        const int left   = (GetDeviceCaps(GetDC(NULL), HORZRES) - m_ScreenSize.x)  / 2;
        const int top    = (GetDeviceCaps(GetDC(NULL), VERTRES) - m_ScreenSize.y) / 2;


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

        m_Hwnd = CreateWindow(ENGINE_NAME, ENGINE_NAME, 0, left, top, m_ScreenSize.x, m_ScreenSize.y, NULL, NULL, m_Instance, NULL);
        assert(m_Hwnd != NULL);
        ShowWindow(m_Hwnd, SW_NORMAL);
        LONG lStyle = GetWindowLong(m_Hwnd, GWL_STYLE);
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        SetWindowLong(m_Hwnd, GWL_STYLE, lStyle);
        LONG lExStyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
        lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
        SetWindowLong(m_Hwnd, GWL_EXSTYLE, lExStyle);
        SetWindowPos(m_Hwnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
        //ShowCursor(0);
    }

    void AgmdApp::MainLoop()
    {
        MSG Message;
        Timer timer;
        float renderTime = 0, guiTime = 0;
        while (m_IsRunning)
        {
            if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
            else
            {
                uint32 time = clock();
                uint32 time_diff = time - last_time;
                last_time = time;
                Renderer& render =  Renderer::Get();
                render.GetStatistics().ResetStatistics();
                render.OnUpdate(time_diff);
                GUIMgr::Instance().Update(time_diff);
                OnUpdate(time_diff);
                render.InitScene();
                //Render 3D objects
                timer.start();
                RenderingMode::GetRenderingMode()->Compute();
                OnRender3D();
                renderTime = timer.getElapsedTimeInMicroSec();
                timer.stop();
                timer.start();
                //Render 2D GUI
                GUIMgr::Instance().DrawGUI();
                OnRender2D();
                timer.stop();
                guiTime = timer.getElapsedTimeInMicroSec();
                render.EndScene();
                frame++;
				if(time_diff < 15)
					Sleep(15-time_diff);
                if(fps_timer <= time_diff)
                {
                    m_fps = ((float)frame*SECONDS_IN_MS)/(SECONDS_IN_MS + time_diff - fps_timer);
                    fps_timer = SECONDS_IN_MS;
                    render.GetStatistics().SetMainTime(time_diff);
                    render.GetStatistics().SetRenderingTime(renderTime);
                    render.GetStatistics().SetGuiTime(guiTime);
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
        camera = Camera::GetCurrent();
        if(Message == WM_CHAR)
        {

        }
        switch (Message)
        {
            case WM_DESTROY :
                Exit();
                return 0;
            case WM_KEYUP:
            case WM_KEYDOWN:
                camera->OnKeyboard((char)LOWORD(WParam),Message == WM_KEYUP ? true : false);
                switch(LOWORD(WParam))
                {
                case VK_F1:
                    RenderingMode::GetRenderingMode()->SetRenderMode(MODE_FILL);
                    return 0;
                case VK_F2:
                    RenderingMode::GetRenderingMode()->SetRenderMode(MODE_LINE);
                    return 0;
                case VK_F3:
                    RenderingMode::GetRenderingMode()->SetRenderMode(MODE_POINT);
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
