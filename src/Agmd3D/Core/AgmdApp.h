
#ifndef AGMDAPP_H
#define AGMDAPP_H

#include <Config/Export.h>
#include <Utilities/Plugin.h>
#include <Utilities/SmartPtr.h>
#include <map>
#include <assert.h>
#include <AgmdDefines.h>
#include <Core/Camera/Camera.h>

#define SECONDS_IN_MS 1000

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD_EXPORT AgmdApp
    {
    public:
        void Run();
        void Exit();
        ivec2 getScreen() {return m_ScreenSize;}
        float getFps() { if(m_fps < 1) return 0.0f; return m_fps;} 
    private:

        void MakeWindow();
        void MainLoop();
        static LRESULT CALLBACK GlobalWindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);


        HINSTANCE          m_Instance;
        HWND               m_Hwnd;
        bool               m_IsRunning;
        static AgmdApp*       m_Application;
        SmartPtr<Plugin>   m_Renderer;
        uint64 last_time;
        uint32 frame;
        uint64 fps_timer;

        float m_fps;

    protected:
        AgmdApp();
        ~AgmdApp();
        virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
        virtual void OnInit() = 0;
        virtual void OnUpdate(uint64 time_diff) = 0;
        virtual void OnRender() = 0;
        Camera*              camera;
        ivec2 last_mouse_pos;
        ivec2 m_ScreenSize;
        uint32 mouseState;

    };
    
}

#endif