#include "App.h"
#include <Agmd3D/Core/MediaManager.h>
#include <Agmd3D/Core/Driver.h>
#include <Agmd3D/Core/Enums.h>
#include <Agmd3D/Core/Declaration.h>
#include <Agmd3D/Core/DeclarationElement.h>
#include <Agmd3D/Core/ResourceManager.h>
#include <Agmd3D/Core/RenderObject/GeometryFactory.h>

#include <Agmd3D/Core/Buffer/FrameBuffer.h>

#include <Agmd3D/Core/RenderObject/GraphicString.h>

#include <Agmd3D/Core/SceneObject/Scene.h>
#include <Agmd3D/Core/SceneObject/Water.h>
#include <Agmd3D/Core/SceneObject/SkyBox.h>
#include <Agmd3D/Core/SceneObject/Light.h>
#include <Agmd3D/Core/SceneObject/Material.h>

#include <Agmd3D/Core/SceneNode/MeshNode.h>

#include <Agmd3D/Core/RenderingMode/DeferredRendering.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>

#include <Agmd3D/Core/Camera/FPCamera.h>
#include <Agmd3D/Core/Camera/FollowCamera.h>

#include <AgmdUtilities/Utilities/Color.h>

#include <Agmd3D/Core/Effects/PostEffectMgr.h>
#include <Agmd3D/Core/Effects/AntiAliasing.h>

#include <Agmd3D/Core/RenderObject/MeshRender.h>

#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <Agmd3D/Core/GUI/AWindow.h>

#include <Agmd3D/Core/Shader/ShaderPreCompiler.h>

#include <Agmd3D/Core/Tools/Statistics.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include <glm/ext.hpp>
#include <libnoise/noise.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <Core/Shader/ShaderPipeline.h>


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
	wxEntryStart( argc, argv );
	AgmdApplication::Run(argc,argv);
}


void App::MakeWindow()
{
	//wxApp::SetInstance(m_wxApplication);
}

void App::init()
{ 

	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 1000.f);
	m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	ForwardRendering* mode = new ForwardRendering(getScreen());

	RenderingMode::setRenderingMode(mode);
	m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black,"Arial",20);
	m_Scene = new SceneMgr();
	
	Model* sphere = GeometryFactory::createSphere(1,100,100,(float)M_PI*2);
	SceneNode* node = new MeshNode(sphere);
	m_Scene->AddNode(node);
	
	GUIMgr& guimgr = GUIMgr::Instance();



	Driver::Get().SetActiveScene(m_Scene);
	Driver::Get().SetCullFace(2);
	cam3D = new FPCamera(m_MatProj3D,vec3(3,0,0));
	cam2D = new FPCamera(m_MatProj2D);
	Camera::setCurrent(cam3D, CAMERA_3D);
	Camera::setCurrent(cam2D, CAMERA_2D);
}

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
}



void App::OnRender3D()
{

}

void App::OnRender2D()
{

}


void App::OnClick( int click, vec2 pos,bool up)
{
	AgmdApplication::OnClick(click,pos,up);
}


void App::OnMove(vec2 pos)
{
	AgmdApplication::OnMove(pos);
}

void App::OnKey(a_char key, bool up)
{
	AgmdApplication::OnKey(key,up);
}








