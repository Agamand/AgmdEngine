/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef AGMDAPP_H
#define AGMDAPP_H

#include <Config/Export.h>
#include <Utilities/Plugin.h>
#include <Utilities/SmartPtr.h>
#include <map>
#include <assert.h>
#include <CommonDefines.h>
#include <Core/Camera/Camera.h>

#define SECONDS_IN_MS 1000

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD3D_EXPORT AgmdApp
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
        a_uint32 last_time;
        a_uint32 frame;
        a_uint32 fps_timer;

        float m_fps;

    protected:
        AgmdApp(ivec2 screenSize = ivec2(1600,900));
        ~AgmdApp();
        virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
		virtual void OnClick(int click, vec2 pos) = 0;
		virtual void OnMove(vec2 pos) = 0;
        virtual void OnInit() = 0;
        virtual void OnUpdate(a_uint64 time_diff) = 0;
        virtual void OnRender3D() = 0;
        virtual void OnRender2D() = 0;
        Camera*              camera;
        ivec2 last_mouse_pos;
        ivec2 m_ScreenSize;
        a_uint32 mouseState;

    };
    
}

#endif