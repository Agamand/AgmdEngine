/*
============================================================================
Demo - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/Kinroux)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef APP_H
#define APP_H
#include <Agmd3D/Config/Fwd.h>
#include <Agmd3D/Core/AgmdApplication.h>
#include <AgmdMaths/Vector2.h>
#include <AgmdMaths/Matrix4.h>
#include <AgmdUtilities/Utilities/Singleton.h>
#include <Agmd3D/Core/Model/Model.h>
#include <Agmd3D/Core/Model/SceneMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <map>
#include <Container/Vector.h>


#define SCREEN_WIDTH_PLANET 1600
#define SCREEN_HEIGHT_PLANET 900

class App : public Agmd::AgmdApplication, public Singleton<App>
{
    MAKE_SINGLETON(App);
public:
    virtual void Run(int argc, char** argv);
private :
    App() : AgmdApplication("Sample 1")
    {}
    virtual void init();


    virtual void OnClick(int click, vec2 pos, bool up);
    virtual void OnMove(vec2 pos);
    virtual void OnKey(a_char key, bool up);

    virtual void OnUpdate(a_uint64 time_diff);

    virtual void OnRender3D();
    virtual void OnRender2D();

    virtual void MakeWindow();


    glm::mat4             m_MatProj2D;
    glm::mat4             m_MatProj3D;

    Agmd::SceneMgr*        m_Scene;
    Agmd::GraphicString*   m_fps;

    Agmd::Camera*       cam3D;
    Agmd::Camera*       cam2D;
    Agmd::SceneNode* camNode;



};

#endif // APP_H