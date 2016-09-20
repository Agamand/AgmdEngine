/*
============================================================================
Sample particles - A test application for particles !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef APP_H
#define APP_H

#include <Agmd3D/Config/Fwd.h>
#include <Agmd3D/Core/AgmdApplication.h>
#include <AgmdMaths/Vector2.h>
#include <AgmdMaths/Vector3.h>
#include <AgmdMaths/Matrix4.h>
#include <AgmdUtilities/Utilities/Singleton.h>
#include <Agmd3D/Core/Model/Model.h>
#include <Agmd3D/Core/Model/SceneMgr.h>
#include <Agmd3D/Core/Shader/ShaderProgram.h>
#include <Agmd3D/Core/GUI/AWindow.h>
#include <map>
#include <vector>


#define SCREEN_WIDTH_APP 1920
#define SCREEN_HEIGHT_APP 1080	

class App : public Agmd::AgmdApplication, public Singleton<App>
{
    MAKE_SINGLETON(App);
public:
    App(): AgmdApplication(ivec2(SCREEN_WIDTH_APP,SCREEN_HEIGHT_APP))
    {
    }

    Agmd::GraphicString* m_text;

    void Run(int argc, char** argv);
private :

    virtual void init();

    virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
    virtual void OnClick(int click, vec2 pos, bool up);
    virtual void OnKey(a_char key, bool up);
    virtual void OnMove(vec2 pos);
    virtual void OnUpdate(a_uint64 time_diff);
    virtual void OnRender3D();
    virtual void OnRender2D();
    typedef std::map<std::string, std::string> TDescTable;
    typedef std::vector<Agmd::TModelPtr> ModelVector;

    glm::mat4 m_MatProj2D;
    glm::mat4 m_MatProj3D;
    glm::mat3 m_MatNormal;

    Agmd::SceneMgr* m_Scene;

    Agmd::GraphicString* m_fps;

    Agmd::Camera* cam3D;
    Agmd::Camera* cam2D;

    a_uint64 m_timer;
    bool pause;
    bool fxaa;
};

#endif // APP_H
