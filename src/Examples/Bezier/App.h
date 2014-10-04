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

#include <Agmd3D\Config\Fwd.h>
#include <Agmd3D\Core\AgmdApp.h>
#include <AgmdMaths\Vector2.h>
#include <AgmdMaths\Vector3.h>
#include <AgmdMaths\Matrix4.h>
#include <AgmdUtilities\Utilities\Singleton.h>
#include <Agmd3D\Core\SceneObject\Model.h>
#include <Agmd3D\Core\SceneObject\SceneMgr.h>
#include <Agmd3D\Core\Shader\ShaderProgram.h>

#include <Core/2DRender/DrawablePlane.h>
#include <Core/2DRender/LineRenderer.h>
#include <Core/2DRender/BaseSpline.h>
#include <Core/2DRender/BSpline.h>
#include <Core/2DRender/Bezier.h>

#include <map>
#include <Container/Vector.h>
#define SCREEN_WIDTH_PLANET 800
#define SCREEN_HEIGHT_PLANET 600
class App : public Agmd::AgmdApp, public Singleton<App>
{
    MAKE_SINGLETON(App);
public:

    void Run(int argc, char** argv);
private :
	App() : AgmdApp(ivec2(SCREEN_WIDTH_PLANET,SCREEN_HEIGHT_PLANET))
	{}
    virtual void OnInit();

    virtual LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
    void OnClick(int click, vec2 pos);
	void OnMove(vec2 pos);
    virtual void OnUpdate(a_uint64 time_diff);
    virtual void OnRender3D();
    virtual void OnRender2D();
    glm::mat4             m_MatProj2D;
    glm::mat4             m_MatProj3D;

    Agmd::GraphicString* m_fps;

    Agmd::Camera*       cam3D;
    Agmd::Camera*       cam2D;


    bool pause;


	//Bezier

	Agmd::DrawablePlane* m_plane;


};

#endif // APP_H