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
#include <Agmd3D/Core/AgmdApp.h>
#include <AgmdMaths/Vector2.h>
#include <AgmdMaths/Matrix4.h>
#include <AgmdUtilities/Utilities/Singleton.h>
#include <Agmd3D/Core/SceneObject/Model.h>
#include <Agmd3D/Core/SceneObject/SceneMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <map>
#include <Container/Vector.h>

#define SCREEN_WIDTH_PLANET 1920
#define SCREEN_HEIGHT_PLANET 1080

class App : public Agmd::AgmdApp, public Singleton<App>
{
    MAKE_SINGLETON(App);
public:
    static Agmd::Model* CreateSphere(float r,float stack, float slice,float angle, std::string texture, Agmd::TPrimitiveType type, a_uint32 color = -1);
    static Agmd::Model* CreatePlane(ivec2 size, ivec2 n_poly, std::string texture, Agmd::TPrimitiveType type);
    static Agmd::Model* CreateBox(vec3 size, std::string texture, Agmd::TPrimitiveType type);
    static Agmd::Model* CreateTriangle(float size, Agmd::TPrimitiveType type);
    static Agmd::Model* CreateMetaSphere(float r, int stack, int slice);
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
    glm::mat3             m_MatNormal;

    Agmd::SceneMgr*        m_Scene;
    Agmd::GraphicString* m_fps;

    Agmd::Camera*       cam3D;
    Agmd::Camera*       cam2D;

    Agmd::Light* m_light;
    a_uint64  m_timer;
    bool pause;


	/*
		UISLider	
	*/

	Agmd::ASlider*  m_frequencySlider;
	Agmd::ASlider*  m_octaveCountSlider;
	Agmd::ASlider*  m_persistanceSlider;
	bool m_animated;
};

#endif // APP_H