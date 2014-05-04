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


#include "App.h"
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Driver.h>
#include <Agmd3D\Core\Enums.h>
#include <Agmd3D\Core\Declaration.h>
#include <Agmd3D\Core\DeclarationElement.h>
#include <Agmd3D\Core\ResourceManager.h>
#include <Agmd3D\Core\SceneObject\Terrain.h>
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D\Core\RenderObject\GraphicString.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <AgmdUtilities/Utilities/Color.h>
#include <AgmdUtilities/Debug/Profiler.h>
#include <Agmd3D/Core/Shader/ShaderPipeline.h>
#include <Agmd3D/Core/Tools/Statistics.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include <Agmd3D/Core/Camera/FollowCamera.h>
#include <Agmd3D/Core/Camera/FPCamera.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Core/Shader/ShaderPreCompiler.h>
#include <random>


using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

void App::Run(int argc, char** argv)
{
    if(argc > 0)
	{
		File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
		ShaderPreCompiler::Instance().AddSearchPath(main.Path()+"/Shader");
	}
    AgmdApp::Run();
}

void App::OnInit()
{  
    pause = true;
	printf("Loading...");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = false;
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    Driver::Get().SetCullFace(2);

	/*
		Bezier
	*/

	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),10.f);
	cam2D = new FPCamera(m_MatProj2D);

	m_plane = new DrawablePlane(getScreen(),vec2(100,100));
	vec2 points[] = {vec2(-50,-50), vec2(-50,50), vec2(50,50)};
	BaseSpline* spline = new BaseSpline(points,3);
	Bezier* bezier = new Bezier(points,3);
	LineRenderer* renderer = new LineRenderer(bezier);
	m_plane->addSpline(renderer);
	addInputListener(m_plane);

    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
}
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{

}

void App::OnRender3D()
{
	m_plane->render();
	Texture::TextureRender(m_plane->getTexture());
}

void App::OnRender2D()
{
    Driver& render = Driver::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString());
    m_fps->Draw();

}

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

void App::OnClick( int click, vec2 pos )
{

}

void App::OnMove(vec2 pos)
{

}	
