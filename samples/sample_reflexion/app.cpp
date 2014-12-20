#include "App.h"
#include <Agmd3D/Core/MediaManager.h>
#include <Agmd3D/Core/Driver.h>
#include <Agmd3D/Core/Enums.h>
#include <Agmd3D/Core/Declaration.h>
#include <Agmd3D/Core/DeclarationElement.h>
#include <Agmd3D/Core/ResourceManager.h>
#include <Agmd3D/Core/Model/GeometryFactory.h>

#include <Agmd3D/Core/Buffer/FrameBuffer.h>

#include <Agmd3D/Core/RenderObject/GraphicString.h>

#include <Agmd3D/Core/Model/Scene.h>
#include <Agmd3D/Core/Model/Water.h>
#include <Agmd3D/Core/Model/SkyBox.h>
#include <Agmd3D/Core/Model/Light.h>
#include <Agmd3D/Core/Model/Material.h>

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
#define WATER_RESOLUTION 2048



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
struct _WaveParameters
{
	float speed;
	float amplitude;
	float wavelength;
	float steepness;
};

struct _WaveDirections
{
	float x;
	float y;
};
#define WAVE_COUNT 1
_WaveParameters m_PWave[WAVE_COUNT];

_WaveDirections m_DWave[WAVE_COUNT];

void App::MakeWindow()
{
	//wxApp::SetInstance(m_wxApplication);
}
ShaderPipeline * refractionPipe;
ShaderProgram tmp_program;
Texture water_normal;



void App::init()
{ 

	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 1000.f);
	m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	ForwardRendering* mode = new ForwardRendering(getScreen());

	RenderingMode::setRenderingMode(mode);
	m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black,"Arial",20);
	m_Scene = new SceneMgr();
	


	Image img[6];
	for(int i = 0; i < 6; i++)
	{
		img[i] = Image(ivec2(512));
		img[i].LoadFromFile(StringBuilder("texture/watercube/")(i)(".tga"));
	}
	Texture texCube;
	texCube.CreateFromImage(img,PXF_A8R8G8B8);
	water_normal.Create(ivec2(WATER_RESOLUTION),PXF_A8R8G8B8,TEXTURE_2D);
	ShaderPipeline* _default= ShaderPipeline::GetDefaultPipeline();
	refractionPipe = new ShaderPipeline(*_default);
	ShaderProgram diffuseShader;
	diffuseShader.LoadFromFile("Shader/test/refraction.glsl");
	Texture normal;
	normal.CreateFromFile("texture/water_normal.png",PXF_A8R8G8B8);
	refractionPipe->setShader(diffuseShader,RENDERPASS_DIFFUSE);
	Material* mat = new Material(refractionPipe);
	mat->SetTexture(texCube,0,(TRenderPass)(1<<RENDERPASS_DEFERRED | (1<<RENDERPASS_DIFFUSE)));
	mat->SetTexture(water_normal,1,(TRenderPass)(1<<RENDERPASS_DEFERRED | (1<<RENDERPASS_DIFFUSE)));
	Model* mesh = GeometryFactory::createPlane(ivec2(100),ivec2(100));
	MeshNode* node = new MeshNode(mesh);
	node->setMaterial(mat);
	node->getTransform().rotate(90.0f,vec3(1,0,0));
	m_Scene->AddNode(node);
	mesh = GeometryFactory::createSphere(1,100,100,(float)M_PI*2);
	node = new MeshNode(mesh);
	node->setMaterial(mat);
	m_Scene->AddNode(node);
	
	tmp_program.LoadFromFile("shader/waterNormal.glsl");
	GUIMgr& guimgr = GUIMgr::Instance();

	SkyBox* sk = new SkyBox();
	sk->SetTexture(texCube);
	m_Scene->SetSkybox(sk);

        memset(m_PWave,0,sizeof(m_PWave));
        memset(m_DWave,0,sizeof(m_DWave));

        static float overallSteepness = 0.2f;
        // Wave One
        m_PWave[0].speed = 4.f;
        m_PWave[0].amplitude = 0.05f;
        m_PWave[0].wavelength = 0.5f;
        m_PWave[0].steepness = overallSteepness / (m_PWave[0].wavelength * m_PWave[0].amplitude * 4);
        m_DWave[0].x = +1.0f;
        m_DWave[0].y = +1.5f;

        // Wave Two
//         m_PWave[1].speed = 0.1f;
//         m_PWave[1].amplitude = 0*0.01f;
//         m_PWave[1].wavelength = 0.4f;
//         m_PWave[1].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
//         m_DWave[1].x = +0.8f;
//         m_DWave[1].y = +0.2f;
// 
//         // Wave Three
//         m_PWave[2].speed = 0.04f;
//         m_PWave[2].amplitude = 0*0.035f;
//         m_PWave[2].wavelength = 0.1f;
//         m_PWave[2].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
//         m_DWave[2].x = -0.2f;
//         m_DWave[2].y = -0.1f;
// 
//         // Wave Four
//         m_PWave[3].speed = 0.05f;
//         m_PWave[3].amplitude = 0*0.007f;
//         m_PWave[3].wavelength = 0.2f;
//         m_PWave[3].steepness = overallSteepness / (m_PWave[1].wavelength * m_PWave[1].amplitude * 4);
//         m_DWave[3].x = -0.4f;
//         m_DWave[3].y = -0.3f;

	Driver::Get().SetActiveScene(m_Scene);
	Driver::Get().SetCullFace(2);
	cam3D = new FPCamera(m_MatProj3D,vec3(3,0,0));
	cam2D = new FPCamera(m_MatProj2D);
	Camera::setCurrent(cam3D, CAMERA_3D);
	Camera::setCurrent(cam2D, CAMERA_2D);
}
void generateNormalMap(Texture& tex,float time)
{
	//mat4 tempProjection = glm::ortho(-(float)size.x/2.0f,(float)size.x/2.0f, -(float)size.y/2.0f,(float)size.y/2.0f);
	Driver& driver = Driver::Get();
	driver.SetCurrentProgram(tmp_program.GetShaderProgram());
	driver.SetViewPort(ivec2(0),ivec2(WATER_RESOLUTION));
	Texture::BeginRenderToTexture(water_normal);
	tmp_program.SetParameter("u_waveParameters[0]",(vec4*)m_PWave,WAVE_COUNT);
	tmp_program.SetParameter("u_waveDirections[0]",(vec2*)m_DWave,WAVE_COUNT);
	float _time = time;
	tmp_program	.SetParameter("u_passedTime",_time);
	Fast2DSurface::Instance().Draw();
	Texture::EndRenderToTexture();
}
float _time = 0;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	_time += time_diff/10000.0f;

	refractionPipe->setParameter("u_camPosition",cam3D->getPosition());
	generateNormalMap(water_normal,_time);
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








