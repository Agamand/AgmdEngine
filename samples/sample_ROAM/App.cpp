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
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D\Core\RenderObject\GraphicString.h>
#include <Agmd3D/Core/Model/Light.h>
#include <Agmd3D/Core/SceneNode/CameraNode.h>
#include <Agmd3D/Core/Controller/FirstPersonController.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D/Core/RenderingMode/DeferredRendering.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>
#include <Agmd3D/Core/Camera/FPCamera.h>
#include <Agmd3D/Core/Camera/FollowCamera.h>
#include <AgmdUtilities/Utilities/Color.h>
#include <AgmdUtilities/Debug/Profiler.h>
#include <Agmd3D/Core/Effects/PostEffectMgr.h>
#include <Agmd3D/Core/Effects/BlurEffect.h>
#include <Agmd3D/Core/Effects/AsciEffect.h>
#include <Agmd3D/Core/RenderObject/MeshRender.h>
#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <Agmd3D/Core/Shader/ShaderPipeline.h>
#include <Agmd3D/Core/Tools/Statistics.h>
#include <Agmd3D/Core/Model/Material.h>
#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include <Demo/Loader/MeshLoader.h>
#include <glm/ext.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Core/Shader/ShaderPreCompiler.h>
#include <random>

using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

BaseShaderProgram* default_program;

void App::Run(int argc, char** argv)
{
    if(argc > 0)
	{
		File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
		ShaderPreCompiler::Instance().AddSearchPath(main.Path()+"/Shader");
	}

    AgmdApplication::Run();
}
void App::init()
{  
    pause = true;
    m_timer = 1000;
	printf("Loading...");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = false;
    //DeferredRendering* mode = new DeferredRendering(getScreen());
    ForwardRendering* mode = new ForwardRendering(getScreen());
    RenderingMode::setRenderingMode(mode);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();

    ShaderProgram p;
    p.LoadFromFile("shader/debug/simple.glsl");
    ShaderPipeline* pipe = new ShaderPipeline(*ShaderPipeline::GetDefaultPipeline());
    pipe->setShader(p,TRenderPass::RENDERPASS_DIFFUSE);
	
	Material* mat = new Material(pipe);
    
    Driver::Get().SetActiveScene(m_Scene);
    Driver::Get().SetCullFace(2);

    //Setups cameras
    cam3D = new Camera(PROJECTION_PERSPECTIVE,ProjectionOption(vec2(getScreen()),60.0f,0));
    cam2D =  new Camera(PROJECTION_ORTHO,ProjectionOption(vec4(0,100.0f,0,100.0f)));

    //Create input controller
    InputController* controller = new FirstPersonController();
    //Create node for camera
    CameraNode* camNode = new CameraNode(cam3D,controller);
    camNode->setController(controller);
    // add Camera to scene
    m_Scene->AddNode(camNode);


    Camera::setCurrent(cam3D, CAMERA_3D);
    Camera::setCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
}
float timespeed= 1.0f;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	
	if(pause)
		return;
}

void App::OnRender3D()
{

}

void App::OnRender2D()
{
    Driver& render = Driver::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer)("\n Speed : ")(timespeed	);
    m_fps->draw();

}

int pCount = 6000;
void App::OnClick( int click, vec2 pos, bool up)
{
	printf("click %i at pos (%f,%f), up: i\n",click,pos.x,pos.y,up);
	float f = Driver::Get().GetAspectRatio();
	if(!draw)
		return;
	AgmdApplication::OnClick(click,pos,up);
}

void App::OnMove(vec2 pos)
{
	AgmdApplication::OnMove(pos);
}	

void App::OnKey( a_char key, bool up )
{
	if(up)
	{
		printf("%c key, up: %i\n",key,up);
		switch(key)
		{
		case 'P':
			pause = !pause;
			//cam3D->SetRecvInput(pause);
			break;
		}

	}
	AgmdApplication::OnKey(key,up);
}
