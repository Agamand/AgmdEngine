/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef AGMDAPP_H
#define AGMDAPP_H

#define USE_WX
#ifdef USE_WX
#include "wx/frame.h"
#include "wx/defs.h"
#include "wx/app.h"
#include "wx/menu.h"
#include "wx/dcclient.h"
#include "wx/wfstream.h"
#if wxUSE_ZLIB
#include "wx/zstream.h"
#endif

#include "wx/window.h"

#include "wx/glcanvas.h"
#endif
#include <Config/Export.h>
#include <Utilities/Plugin.h>
#include <Utilities/SmartPtr.h>
#include <map>
#include <assert.h>
#include <CommonDefines.h>
#include <Core/Camera/Camera.h>


#include <Container/Vector.h>
#include <string>
#define SECONDS_IN_MS 1000

using namespace AgmdUtilities;



// Define a new frame type
//namespace Agmd
//{
	// Define a new application type
#if defined(USE_WX)
	class Application : public wxApp
	{
	public:
		Application(bool dframe, wxString& str);
		virtual bool OnInit();
	private:
		wxFrame* m_frame;
		wxString m_name;
		bool m_dframe;
	};


	class GLCanvas;
	class AgmdFrame : public wxFrame
	{
	public:
		AgmdFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
			const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

		void OnMenuFileOpen(wxCommandEvent& event);
		void OnMenuFileExit(wxCommandEvent& event);
		void OnMenuHelpAbout(wxCommandEvent& event);
		void SetCanvas(GLCanvas *canvas) { m_canvas = canvas; }
		GLCanvas *GetCanvas() { return m_canvas; }
	private:
	
		GLCanvas *m_canvas;

		wxDECLARE_EVENT_TABLE();
		void reDrawCanvas();
	};


	class GLCanvas : public wxGLCanvas
	{
	public:
		GLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize, long style = 0,
			const wxString& name = wxT("TestGLCanvas"));

		virtual ~GLCanvas();

		void LoadDXF(const wxString& filename);
		void InitGL();
	protected:
		void OnIdle(wxIdleEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnSize(wxSizeEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnMouse(wxMouseEvent& event);
		void OnMouseUp(wxMouseEvent& event);
		void OnMouseDown(wxMouseEvent& event);
		void OnMouseMotion(wxMouseEvent& event);
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
		void keyPressed(wxKeyEvent& event);
		void keyReleased(wxKeyEvent& event);
	private:
	
		void ResetProjectionMode();

		wxGLContext* m_glRC;
		Agmd::AgmdApplication* m_application;
		wxDECLARE_NO_COPY_CLASS(GLCanvas);
		wxDECLARE_EVENT_TABLE();
	
	};
#endif
namespace Agmd{
    class AGMD3D_EXPORT AgmdApplication
    {
    public:
		class InputListener
		{
		public:
			virtual void OnClick(int click,int state, const vec2& pos, bool up) = 0;
			virtual void OnKey(char key, bool up) = 0;
			virtual void OnMouseMotion(const vec2& pos, const ivec2& posdiff) = 0;
		};
        virtual void Run(int argc = 0, char** argv=NULL);
        void Exit();
        ivec2 getScreen() {return m_ScreenSize;}
        float getFps() { if(m_fps < 1) return 0.0f; return m_fps;}
		void addInputListener(InputListener* listener){m_inputListener.push_back(listener);};
		virtual void OnClick(int click, vec2 pos, bool up);
		virtual void OnMove(vec2 pos);
		virtual void OnKey(a_char key,bool up);
		void onResize( ivec2 size );
		void draw();
		static AgmdApplication* getApplication(){return s_application;}
		bool isReady() const {return m_isReady;}
		InputController* m_sceneController;
		a_uint32 getDeltaTime(){return m_deltaTime;}
    private:
        
		HINSTANCE				m_Instance;
#if defined(USE_WX)
		
#else 
        static LRESULT CALLBACK GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
		HWND					m_Hwnd;
		void MainLoop();
#endif
        bool					m_isRunning;
        static AgmdApplication* s_application;
        SmartPtr<Plugin>		m_renderer;
        a_uint32				m_lastTime;
        a_uint32				m_fpsTimer;
        float					m_fps;
		a_uint32				m_deltaTime;

    protected:
        AgmdApplication(ivec2 screenSize = ivec2(SCREEN_WIDTH,SCREEN_HEIGHT));
		AgmdApplication(const std::string& frameName);
#ifdef USE_WX
		virtual bool OnInit();
		wxFrame*				m_frame;
		GLCanvas*				m_glcanvas;
		Application*			m_wxApplication;
		void CreateGlCanvas( wxWindow* m_viewPanel );
#endif

        ~AgmdApplication();
#ifndef USE_WX
        virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
		
#endif
		virtual void MakeWindow();
		virtual void init() = 0;
        virtual void OnUpdate(a_uint64 time_diff) = 0;
        virtual void OnRender3D() = 0;
        virtual void OnRender2D() = 0;

		Camera*              camera;
        ivec2 last_mouse_pos;
        ivec2 m_ScreenSize;
        a_uint32 mouseState;
		a_vector<InputListener*> m_inputListener;
		std::string m_frameName;
		bool m_createDefaultFrame;
		bool m_isReady;
		
	};
}




#if defined(__BORLANDC__)
#define AGMD_MAIN int main(int argc, char** argv) {
#define AGMD_MAIN_END(RETURNV) return RETURNV; }
#define AGMD_MAIN_CONSOLE AGMD_MAIN
#define AGMD_MAIN_CONSOLE_END AGMD_MAIN_END
#elif defined(__GNUC__)
#define AGMD_MAIN int main(int argc, char** argv) {
#define AGMD_MAIN_END(RETURNV) return RETURNV; }
#define AGMD_MAIN_CONSOLE AGMD_MAIN
#define AGMD_MAIN_CONSOLE_END AGMD_MAIN_END
#elif defined(__MINGW32__) || defined(__MINGW64__)
#define AGMD_MAIN int main(int argc, char** argv) {
#define AGMD_MAIN_END(RETURNV) return RETURNV; }
#define AGMD_MAIN_CONSOLE AGMD_MAIN
#define AGMD_MAIN_CONSOLE_END AGMD_MAIN_END
#elif defined(__WIN32__) || defined(__WIN64__)

inline void getArgs(int& argc,char** &argv)
{
	LPWSTR *szArglist;												
	int nArgs;																  
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	argc = nArgs;
	if( NULL == szArglist )
		return;
	argv = new char*[nArgs];
	for(int i = 0; i < nArgs; i++)
	{

		argv[i] = new char [wcslen(szArglist[i]) + 1];
		wsprintfA ( argv[i], "%S", szArglist[i]);
		
	}
}

#define AGMD_MAIN													  \
extern "C" int WINAPI WinMain(HINSTANCE hInstance,                    \
							HINSTANCE hPrevInstance,                  \
							wxCmdLineArgType WXUNUSED(lpCmdLine),     \
							int nCmdShow)                             \
{                                                                     \
																	  \
	int argc = 0;													  \
	char** argv = NULL;												  \
	getArgs(argc,argv);

#define AGMD_MAIN_END(RETURNV)										  \
	for(int i = 0; i < argc; i++)									  \
		delete argv[i];												  \
	delete argv;													  \
	return RETURNV;													  \
}

#define AGMD_MAIN_CONSOLE int main(int argc, char** argv) {
#define AGMD_MAIN_CONSOLE_END(RETURNV) return RETURNV; }
#endif

#define AGMD_IMPL													  \
	int agmd_main(int argc,char** argv);							  \
	AGMD_MAIN														  \
	int rv = agmd_main(argc,argv);									  \
	AGMD_MAIN_END(rv)									  

#define AGMD_CONSOLE_IMPL											  \
	int agmd_main(int argc,char** argv);							  \
	AGMD_MAIN_CONSOLE											      \
	int rv = agmd_main(argc,argv);									  \
	AGMD_MAIN_CONSOLE_END(rv)										  




#endif