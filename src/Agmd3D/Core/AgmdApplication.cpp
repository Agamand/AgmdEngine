/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <Core/AgmdApplication.h>
#include <Core/Driver.h>
#include <Core/Enums.h>
#include <Core/MediaManager.h>
#include <Core/ResourceManager.h>
//#include <Windowsx.h>
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


/*
bool MyApp::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	// Create the main frame window
	m_frame = new AgmdFrame(m_app,NULL, wxT("wxWidgets Penguin Sample"),
		wxDefaultPosition, wxDefaultSize);

#if wxUSE_ZLIB
	if (wxFileExists(wxT("penguin.dxf.gz")))
		m_frame->GetCanvas()->LoadDXF(wxT("penguin.dxf.gz"));
#else
	if (wxFileExists(wxT("penguin.dxf")))
		frame->GetCanvas()->LoadDXF(wxT("penguin.dxf"));
#endif
	
	
	m_frame->Show(true);

	return true;
}

MyApp::MyApp( Agmd::AgmdApplication* app )
{
	m_app = app;
}*/

//IMPLEMENT_APP(MyApp)

	// ---------------------------------------------------------------------------
	// AgmdFrame
	// ---------------------------------------------------------------------------
bool Application::OnInit()
	{
		if ( !wxApp::OnInit() )
			return false;

		// Create the main frame window
		/* Show the frame */
		

		return true;
	}
	Application::Application(bool dframe, wxString& str) : m_dframe(dframe),m_name(str),m_frame(NULL)
	{}


	wxBEGIN_EVENT_TABLE(AgmdFrame, wxFrame)
	EVT_MENU(wxID_OPEN, AgmdFrame::OnMenuFileOpen)
	EVT_MENU(wxID_EXIT, AgmdFrame::OnMenuFileExit)
	EVT_MENU(wxID_HELP, AgmdFrame::OnMenuHelpAbout)
	wxEND_EVENT_TABLE()

	// AgmdFrame constructor
	AgmdFrame::AgmdFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
	const wxSize& size, long style)
	: wxFrame(frame, wxID_ANY, title, pos, size, style)
{
	SetIcon(wxICON(sample));

	// Make the "File" menu
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(wxID_OPEN, wxT("&Open..."));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tALT-X"));
	// Make the "Help" menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP, wxT("&About"));

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(helpMenu, wxT("&Help"));
	SetMenuBar(menuBar);

	Show(true);

	m_canvas = new GLCanvas(this, wxID_ANY, wxDefaultPosition,
		GetClientSize(), wxSUNKEN_BORDER);
	m_canvas->Show(true);
	m_canvas->InitGL();
}

// File|Open... command
void AgmdFrame::OnMenuFileOpen( wxCommandEvent& WXUNUSED(event) )
{
	wxString filename = wxFileSelector(wxT("Choose DXF Model"), wxT(""), wxT(""), wxT(""),
#if wxUSE_ZLIB
		wxT("DXF Drawing (*.dxf;*.dxf.gz)|*.dxf;*.dxf.gz|All files (*.*)|*.*"),
#else
		wxT("DXF Drawing (*.dxf)|*.dxf)|All files (*.*)|*.*"),
#endif
		wxFD_OPEN);
	if (!filename.IsEmpty())
	{
		m_canvas->LoadDXF(filename);
		//																																																						->Refresh(false);
	}
}

// File|Exit command
void AgmdFrame::OnMenuFileExit( wxCommandEvent& WXUNUSED(event) )
{
	// true is to force the frame to close
	Close(true);
}

// Help|About command
void AgmdFrame::OnMenuHelpAbout( wxCommandEvent& WXUNUSED(event) )
{
	wxMessageBox(wxT("Agmd Sample"));
}
// ---------------------------------------------------------------------------
// TestGLCanvas
// ---------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
	EVT_SIZE(GLCanvas::OnSize)
	EVT_PAINT(GLCanvas::OnPaint)
	EVT_ERASE_BACKGROUND(GLCanvas::OnEraseBackground)
	EVT_MOUSE_EVENTS(GLCanvas::OnMouse)
	EVT_KEY_DOWN(GLCanvas::keyPressed)
	EVT_KEY_UP(GLCanvas::keyReleased)
	//EVT_MOTION(GLCanvas::OnMouseMotion)
	EVT_IDLE(GLCanvas::OnIdle)
wxEND_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow *parent,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxGLCanvas(parent, id, NULL, pos, size,
	style | wxFULL_REPAINT_ON_RESIZE, name)
{
	m_application = Agmd::AgmdApplication::getApplication();
	// Explicitly create a new rendering context instance for this canvas.
	m_glRC = new wxGLContext(this);
	this->SetExtraStyle( wxWS_EX_PROCESS_IDLE );
	SetCurrent(*m_glRC);

}

GLCanvas::~GLCanvas()
{
	delete m_glRC;
}

void GLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	if(!m_application->isReady())
		return;
	wxPaintDC dc(this);
	SetCurrent(*m_glRC);
	m_application->draw();
	SwapBuffers();
	//printf("redraw !! \n");
}

void GLCanvas::OnSize(wxSizeEvent& WXUNUSED(event))
{
	SetCurrent(*m_glRC);
	int w, h;
	GetClientSize(&w, &h);
	m_application->onResize(ivec2(w,h));
	Refresh(false);
}

void GLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{

}


void GLCanvas::LoadDXF(const wxString& filename)
{

}

void GLCanvas::OnMouse(wxMouseEvent& event)
{
	if(event.IsButton())
		m_application->OnClick(event.GetButton(),vec2(event.m_x,event.m_y),!event.ButtonDown(event.GetButton()));
	else m_application->OnMove(vec2(event.m_x,event.m_y));
	event.Skip();
}
void GLCanvas::OnMouseMotion(wxMouseEvent& event)
{
	m_application->OnMove(vec2(event.m_x,event.m_y));
}
void GLCanvas::OnKeyDown(wxKeyEvent& event)
{

	wxChar uc = event.GetUnicodeKey();
	if ( uc != WXK_NONE )
	{
		m_application->OnKey(uc,false);
	}
	else // No Unicode equivalent.
	{
		m_application->OnKey(event.GetKeyCode(),false);
	}
	
}
void GLCanvas::OnKeyUp(wxKeyEvent& event)
{
	wxChar uc = event.GetUnicodeKey();
	if ( uc != WXK_NONE )
	{
		m_application->OnKey(uc,true);
	}
	else // No Unicode equivalent.
	{
		m_application->OnKey(event.GetKeyCode(),true);
	}
}
void GLCanvas::keyPressed(wxKeyEvent& event) {
	printf("%c pressed\n",event.GetKeyCode());
	m_application->OnKey(event.GetKeyCode(),false);
}
void GLCanvas::keyReleased(wxKeyEvent& event) {
	printf("%c release\n",event.GetKeyCode());
	m_application->OnKey(event.GetKeyCode(),true);
}
void GLCanvas::InitGL()
{
	SetCurrent(*m_glRC);
}

void GLCanvas::ResetProjectionMode()
{

}

void GLCanvas::OnIdle( wxIdleEvent& event )
{
	Refresh(false);
}


namespace Agmd
{

    AgmdApplication* AgmdApplication::s_application = NULL;
    
    AgmdApplication::AgmdApplication(ivec2 screenSize) : 
    m_Instance      (GetModuleHandle(L"Agmd3D.dll")),
#ifndef USE_WX
    m_Hwnd          (NULL),
#else
	m_frame			(NULL),
	m_glcanvas		(NULL),
#endif
    m_isRunning     (true),
    camera          (NULL),
    last_mouse_pos  (0,0),
    mouseState      (MOUSE_NONE),
    m_lastTime       (0),
    m_fps           (0),
    m_fpsTimer       (SECONDS_IN_MS),
    m_ScreenSize    (screenSize),
	m_createDefaultFrame(false),
	m_isReady		(false),
	m_frameName		("Agmd sample application")
    {
        assert(m_Instance != NULL);
        s_application = this;
        RegisterLoaders();
    }

	AgmdApplication::AgmdApplication(const std::string& frameName) :
		m_Instance      (GetModuleHandle(L"Agmd3D.dll")),
		
#ifndef USE_WX
		m_Hwnd          (NULL),
#else
		m_frame			(NULL),
		m_glcanvas		(NULL),
		m_createDefaultFrame(true),
#endif
		m_isRunning     (true),
		camera          (NULL),
		last_mouse_pos  (0,0),
		mouseState      (MOUSE_NONE),
		m_lastTime      (0),
		m_fps           (0),
		m_fpsTimer      (SECONDS_IN_MS),
		m_isReady		(false),
		m_ScreenSize    (1920,1080),
		m_frameName		(frameName)
	{
		assert(m_Instance != NULL);
		s_application = this;
		RegisterLoaders();
	}
    AgmdApplication::~AgmdApplication()
    {
//         if (m_Hwnd)
//         {
//             DestroyWindow(m_Hwnd);
//             UnregisterClass(L"AgmdEngine", m_Instance);
//         }
	}


	bool AgmdApplication::OnInit()
	{
		return true;
	}

    void AgmdApplication::Run(int argc,char** argv)
	{
		
        //if(m_RendererType = RENDERER_DIRECTX)
        //m_Renderer = new Plugin("DXRender.dll");
        //else
        
		
		
		m_wxApplication = new Application(m_createDefaultFrame,wxString(m_frameName));
		m_renderer = new Plugin("GLRender.dll");

       

		wxApp::SetInstance(m_wxApplication);
		wxEntryStart( argc, argv );
		m_wxApplication->OnInit();
		//new BaseFrame(NULL);
		MakeWindow();

		if(!m_frame)
		{

			m_frame =new AgmdFrame(NULL, wxString(m_frameName),
				wxDefaultPosition, wxDefaultSize);
			m_frame->Show(true);
		}else m_frame->Show(true);
        Driver::Get().Initialize(NULL);
        Driver::Get().SetScreen(m_ScreenSize);

        Material* mat = new Material(ShaderPipeline::GetDefaultPipeline());
        Image img = Image();    
        img.Fill(Color::white);
        Texture t = Texture();
        t.CreateFromImage(img,PXF_A8R8G8B8);
        mat->SetTexture(t,0,TRenderPass::RENDERPASS_DEFERRED);
        ResourceManager::Instance().Add("DEFAULT_MATERIAL",mat);
        init();
		if(m_frame)
			m_isReady = true;
		m_wxApplication->MainLoop();
        
		//MainLoop();


    }

    void AgmdApplication::Exit()
    {
        m_isRunning = false;
    }

    void AgmdApplication::MakeWindow()
    {
		

//         const int left   = (GetDeviceCaps(GetDC(NULL), HORZRES) - m_ScreenSize.x)  / 2;
//         const int top    = (GetDeviceCaps(GetDC(NULL), VERTRES) - m_ScreenSize.y) / 2;
// 
// 
//         WNDCLASSEX WindowClass;
//         WindowClass.cbSize        = sizeof(WNDCLASSEX);
//         WindowClass.style         = 0;
//         WindowClass.lpfnWndProc   = GlobalWindowProc;
//         WindowClass.cbClsExtra    = 0;
//         WindowClass.cbWndExtra    = 0;
//         WindowClass.hInstance     = m_Instance;
//         WindowClass.hIcon         = NULL;
//         WindowClass.hCursor       = 0;
//         WindowClass.hbrBackground = 0;
//         WindowClass.lpszMenuName  = NULL;
//         WindowClass.lpszClassName = ENGINE_NAME;
//         WindowClass.hIconSm       = NULL;
//         RegisterClassEx(&WindowClass);
// 
//         m_Hwnd = CreateWindow(ENGINE_NAME, ENGINE_NAME, 0, left, top, m_ScreenSize.x, m_ScreenSize.y, NULL, NULL, m_Instance, NULL);
//         assert(m_Hwnd != NULL);
//         //ShowWindow(m_Hwnd, SW_NORMAL);
//         LONG lStyle = GetWindowLong(m_Hwnd, GWL_STYLE);
//         lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
//         SetWindowLong(m_Hwnd, GWL_STYLE, lStyle);
//         LONG lExStyle = GetWindowLong(m_Hwnd, GWL_EXSTYLE);
//         lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
//         SetWindowLong(m_Hwnd, GWL_EXSTYLE, lExStyle);
//         SetWindowPos(m_Hwnd, NULL, 0,0,0,0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
//         ShowCursor(1);
    }

    /*void AgmdApp::MainLoop()
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
                a_uint32 time = clock();
                a_uint32 time_diff = time - last_time;
                last_time = time;
                Driver& render =  Driver::Get();
                render.GetStatistics().ResetStatistics();
                render.OnUpdate(time_diff);
                GUIMgr::Instance().Update(time_diff);
                OnUpdate(time_diff);
                render.InitScene();
                //Render 3D objects
                timer.start();
                RenderingMode* current = RenderingMode::getRenderingMode();
                if(current != NULL)
                    current->compute();
                OnRender3D();
                renderTime = (float)timer.getElapsedTimeInMicroSec();
                timer.stop();
                timer.start();
                //Render 2D GUI
                GUIMgr::Instance().DrawGUI();
                OnRender2D();
                timer.stop();
                guiTime = (float)timer.getElapsedTimeInMicroSec();
                
                frame++;
				//if(time_diff < 15)
					//Sleep(15-time_diff);
                render.EndScene();
                if(fps_timer <= time_diff)
                {
                    m_fps = ((float)frame*SECONDS_IN_MS)/(SECONDS_IN_MS + time_diff - fps_timer);
                    fps_timer = SECONDS_IN_MS;
                    render.GetStatistics().SetMainTime((float)time_diff);
                    render.GetStatistics().SetRenderingTime(renderTime);
                    render.GetStatistics().SetGuiTime(guiTime);
                    frame = 0;
                }else fps_timer -= time_diff;
                
            }
        }
    }*/

#ifdef USE_WINAPI
    LRESULT CALLBACK AgmdApplication::GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        return s_application->WindowProc(Hwnd, Message, WParam, LParam);
    }


    LRESULT CALLBACK AgmdApplication::WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        GUIMgr& guimgr = GUIMgr::Instance();
        camera = Camera::getCurrent();
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

				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnKey((char)LOWORD(WParam),Message == WM_KEYUP ? true : false);
                camera->onKeyboard((char)LOWORD(WParam),Message == WM_KEYUP ? true : false);
                switch(LOWORD(WParam))
                {
                case VK_F1:
                    RenderingMode::getRenderingMode()->setRenderMode(MODE_FILL);
                    return 0;
                case VK_F2:
                    RenderingMode::getRenderingMode()->setRenderMode(MODE_LINE);
                    return 0;
                case VK_F3:
                    RenderingMode::getRenderingMode()->setRenderMode(MODE_POINT);
                    return 0;
                }
                return 0;

            case WM_XBUTTONDOWN:
                mouseState |= MOUSE_NONE;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_NONE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_RBUTTONDOWN:
                mouseState |= MOUSE_RIGHT;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_RIGHT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
				OnClick(mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize));
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_MBUTTONDOWN:
                mouseState |= MOUSE_MIDDLE;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_MIDDLE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
                camera->onMouseWheel(true);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_LBUTTONDOWN:
                mouseState |= MOUSE_LEFT;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_LEFT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
				OnClick(mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize));
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;

            case WM_XBUTTONUP:
                mouseState &= ~MOUSE_NONE;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_NONE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_RBUTTONUP:
                mouseState &= ~MOUSE_RIGHT;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_RIGHT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_MBUTTONUP:

                mouseState &= ~MOUSE_MIDDLE;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_MIDDLE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
                camera->onMouseWheel(false);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_LBUTTONUP:
                mouseState &= ~MOUSE_LEFT;
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnClick(MOUSE_LEFT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
                guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
                return 0;
            case WM_MOUSEWHEEL:
                camera->onMouseWheel((float)GET_WHEEL_DELTA_WPARAM(WParam));
                return 0;
            case WM_MOUSEMOVE:
                ivec2 posDiff = last_mouse_pos - ivec2(GET_X_LPARAM(LParam),m_ScreenSize.y-GET_Y_LPARAM(LParam));
				for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
					m_inputListener[i]->OnMouseMotion(vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1));
                if(mouseState & MOUSE_RIGHT || mouseState & MOUSE_MIDDLE)
                    camera->onMouseMotion(posDiff.x, posDiff.y);
                

				
                last_mouse_pos.x = GET_X_LPARAM(LParam);
                last_mouse_pos.y = m_ScreenSize.y-GET_Y_LPARAM(LParam);
				OnMove(vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.f-vec2(1));
                guimgr.AddEvent(EventEntry(EV_ON_MOUVE_MOVE,last_mouse_pos,posDiff,mouseState,0));
                return 0;
        }
        return DefWindowProc(Hwnd, Message, WParam, LParam);
    }
#endif

	void AgmdApplication::draw()
	{
		Timer timer;
		int frame = 0;
		float renderTime = 0, guiTime = 0;
		a_uint32 time = clock();
		a_uint32 time_diff = time - m_lastTime;
		m_lastTime = time;
		Driver& render =  Driver::Get();
		render.GetStatistics().ResetStatistics();
		render.OnUpdate(time_diff);
		GUIMgr::Instance().Update(time_diff);
		OnUpdate(time_diff);
		render.InitScene();
		//Render 3D objects
		timer.start();
		RenderingMode* current = RenderingMode::getRenderingMode();
		if(current != NULL)
			current->compute();
		OnRender3D();
		renderTime = (float)timer.getElapsedTimeInMicroSec();
		timer.stop();
		timer.start();
		//Render 2D GUI
		GUIMgr::Instance().DrawGUI();
		OnRender2D();
		timer.stop();
		guiTime = (float)timer.getElapsedTimeInMicroSec();

		frame++;
		//if(time_diff < 15)
		//Sleep(15-time_diff);
		render.EndScene();
		if(m_fpsTimer <= time_diff)
		{
			m_fps = ((float)frame*SECONDS_IN_MS)/(SECONDS_IN_MS + time_diff - m_fpsTimer);
			m_fpsTimer = SECONDS_IN_MS;
			render.GetStatistics().SetMainTime((float)time_diff);
			render.GetStatistics().SetRenderingTime(renderTime);
			render.GetStatistics().SetGuiTime(guiTime);
		}else m_fpsTimer -= time_diff;

	
	}

	void AgmdApplication::OnClick( int click, vec2 pos, bool up )
	{
		GUIMgr& guimgr = GUIMgr::Instance();
		camera = Camera::getCurrent();
		printf("click %i, up : %i\n",click,up);
		switch (click)
		{
		case 1:
			if(up)
			mouseState &= ~MOUSE_LEFT;
			else mouseState |= MOUSE_LEFT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_LEFT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),up);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;

		case 2:
			if(up)
				mouseState &= ~MOUSE_MIDDLE;
			else mouseState |= MOUSE_MIDDLE;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_MIDDLE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),up);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case 3:
			if(up)
				mouseState &= ~MOUSE_RIGHT;
			else mouseState |= MOUSE_RIGHT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_RIGHT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),up);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		/*case WM_XBUTTONDOWN:
			mouseState |= MOUSE_NONE;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_NONE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_RBUTTONDOWN:
			mouseState |= MOUSE_RIGHT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_RIGHT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
			//OnClick(mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize));
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_MBUTTONDOWN:
			mouseState |= MOUSE_MIDDLE;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_MIDDLE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
			camera->onMouseWheel(true);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_LBUTTONDOWN:
			mouseState |= MOUSE_LEFT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_LEFT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),false);
			//OnClick(mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize));
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;

		case WM_XBUTTONUP:
			mouseState &= ~MOUSE_NONE;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_NONE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_RBUTTONUP:
			mouseState &= ~MOUSE_RIGHT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_RIGHT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_MBUTTONUP:

			mouseState &= ~MOUSE_MIDDLE;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_MIDDLE,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
			camera->onMouseWheel(false);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;
		case WM_LBUTTONUP:
			mouseState &= ~MOUSE_LEFT;
			for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
				m_inputListener[i]->OnClick(MOUSE_LEFT,mouseState,vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1),true);
			guimgr.AddEvent(EventEntry(EV_ON_MOUSE_BUTTON,last_mouse_pos,ivec2(0),mouseState,0));
			return;*/
		}
	}

	void AgmdApplication::OnMove( vec2 pos )
	{
		GUIMgr& guimgr = GUIMgr::Instance();
		camera = Camera::getCurrent();
		ivec2 posDiff = last_mouse_pos - ivec2(pos);
		for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
			m_inputListener[i]->OnMouseMotion(vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.0f-vec2(1));
		if(mouseState & MOUSE_RIGHT || mouseState & MOUSE_MIDDLE)
			camera->onMouseMotion(posDiff.x, posDiff.y);

		last_mouse_pos.x = pos.x;
		last_mouse_pos.y = pos.y;
		//OnMove(vec2(last_mouse_pos)/vec2(m_ScreenSize)*2.f-vec2(1));
		guimgr.AddEvent(EventEntry(EV_ON_MOUVE_MOVE,last_mouse_pos,posDiff,mouseState,0));
	}

	void AgmdApplication::OnKey( a_char key,bool up )
	{
		camera = Camera::getCurrent();
		for(a_uint32 i = 0, len = m_inputListener.size(); i < len; i++)
			m_inputListener[i]->OnKey(key,up);
		camera->onKeyboard(key,up);
		switch(key)
		{
		case WXK_F1:
			RenderingMode::getRenderingMode()->setRenderMode(MODE_FILL);
			return;
		case WXK_F2:
			RenderingMode::getRenderingMode()->setRenderMode(MODE_LINE);
			return;
		case WXK_F3:
			RenderingMode::getRenderingMode()->setRenderMode(MODE_POINT);
			return;
		}		
	}

	void AgmdApplication::onResize( ivec2 size )
	{
		m_ScreenSize = size;
		Driver::Get().SetViewPort(ivec2(0,0),size);
		Driver::Get().SetScreen(m_ScreenSize);
	}

#ifdef  USE_WX
	void AgmdApplication::CreateGlCanvas( wxWindow* frame )
	{
		if(!m_frame)
			return;
		m_glcanvas = new GLCanvas(frame);
		frame->GetSizer()->Add(m_glcanvas, 1, wxEXPAND | wxALL, 5);
	}
#endif //USE_WX




}
