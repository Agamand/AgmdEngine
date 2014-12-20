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
#include "M2Model.h"
#include "M2Loader.h"
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
#include <Agmd3D\Core\SceneObject\Scene.h>
#include <Agmd3D\Core\SceneObject\Water.h>
#include <Agmd3D\Core\SceneObject\SkyBox.h>
#include <Agmd3D/Core/Model/Light.h>
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
#include "PerlinNoise.h"
#include <libnoise/noise.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Core/Shader/ShaderPreCompiler.h>
#include <random>
#include "simplexnoise.h"
#include "noiseutils.h"

#include <Agmd3D/Core/Effects/BlurMotionEffect.h>
#include <Agmd3D/Core/Effects/Inverse.h>
#include <Agmd3D/Core/Effects/DrugEffect.h>
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

Texture tvelocity;
Texture tmass;
ShaderProgram velocity_program;
ShaderProgram mass_program;
BlurMotionEffect* blur;
DrugEffect* drug;
Texture tex[2];

void App::init()
{  
    pause = true;
    m_timer = 1000;
	printf("Loading...");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	drawMouse = false;
	draw = true;
	pause = false;
    DeferredRendering* mode = new DeferredRendering(getScreen());
    //RenderingMode::SetRenderingMode(mode);
	tex[0].Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
	tex[1].Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
    m_fxaa = new AntiAliasing();
	blur = new BlurMotionEffect(getScreen());
	//drug = new DrugEffect();
	//PostEffectMgr::Instance().AddEffect(drug);
	//PostEffectMgr::Instance().AddEffect(new BlurMotionEffect(getScreen()));
    //PostEffectMgr::Instance().AddEffect(m_fxaa);
	//PostEffectMgr::Instance().AddEffect(new Inverse());
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	Texture t;
	Texture color_gradiant;
	
	Material* mat = new Material();
	mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
	mat->SetTexture(color_gradiant,1,(TRenderPass)(1<<RENDERPASS_DEFERRED));
    Driver::Get().SetActiveScene(m_Scene);
    Driver::Get().SetCullFace(2);

    m_light = new Light(vec3(0, 0 ,10),-normalize(vec3(0,0.2,-1)),LightType::LIGHT_DIR);//new Light(vec3(0,0,10),-normalize(vec3(0,0.5,-1)),LIGHT_SPOT);
    m_Scene->AddLight(m_light);
    m_light->SetRange(2000.0f);
	ShaderProgram prog;
	ShaderProgram prog2;
	/*particles1 = new ParticlesEmitter("Shader/particle_1.glsl",250,new Transform(vec3(-6,0,0)));
	particles2 = new ParticlesEmitter("Shader/particle_2.glsl",250,new Transform(vec3(6,0,0)));*/
	
	string cubemap[6];
	/*for(int i = 0; i < 6; i++)
	{
		cubemap[i] = StringBuilder("Texture/background/")(i+1)(".png");
	}*/
	//Texture tex_cubemap;
	//tex_cubemap.CreateFromFile(cubemap,PXF_A8R8G8B8);
	mouse_emitter = new ParticlesEmitter(std::string("shader/particle_3.glsl"),2,new Transform());
	AWindow* position =new AWindow();
	AWindow* velocity = new AWindow();
	AWindow* life = new AWindow();


	//particles->velocity_buffer[1]);
	//life->SetBackground(mouse_emitter->extra_buffer[0]);
	//GUIMgr::Instance().AddWidget(position);
	//GUIMgr::Instance().AddWidget(velocity);
//	GUIMgr::Instance().AddWidget(life);
	SkyBox* box = new SkyBox();
	//box->SetTexture(tex_cubemap);
	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),10.f);//m_MatProj3D,4.8f,8.8f,vec2(0,-7.55264f),9.87785f); //Follow Camera Theta(4.8) _phi(8.8) angles(0,-7.55264) distance(9.87785)
	cam2D = new FPCamera(m_MatProj2D);

	velocity_program.LoadFromFile("Shader/particle_velocity_render.glsl");
	mass_program.LoadFromFile("Shader/particle_mass_render.glsl");
	tmass.Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
	tvelocity.Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
	position->SetBackground(tmass);
	velocity->SetBackground(tvelocity);
	

    Camera::setCurrent(cam3D, CAMERA_3D);
    Camera::setCurrent(cam2D, CAMERA_2D);

	m_particles.push_back(new ParticlesEmitter(std::string("shader/particle_4.glsl"),2500	,new Transform(vec3((0),0.f,0)*30.f)));
	printf("Loading end");
}
float timespeed= 1.0f;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	
	if(pause)
		return;
	//drug->Update(time_diff*timespeed);
	for(int i = 0; i < m_particles.size(); i++)
		m_particles[i]->Update(time_diff*timespeed);

	if(drawMouse)
		mouse_emitter->Update(time_diff);

	FollowCamera* cam = static_cast<FollowCamera*>(cam3D);
    const vec2& angles = cam->GetAngles();
	//cam3D->onMouseMotion(1,0);
}

void App::OnRender3D()
{

	Texture::BeginRenderToTexture(tex[0]);
	if(drawMouse)
		mouse_emitter->Draw();
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->Draw();
	}
	Texture::EndRenderToTexture();
	//blur->ApplyEffect(tex[0],tex[1]);
	 //PostEffectMgr::Instance().ApplyEffect(tex[0],tex[1]);
	Texture::TextureRender(tex[1],ivec2(0),m_ScreenSize);
	/*
	for(int i = 0; i < m_particles.size(); i++)
	{
		Texture::BeginRenderToTexture(tvelocity);
		m_particles[i]->Draw(velocity_program.GetShaderProgram());
		Texture::EndRenderToTexture();
	}
	for(int i = 0; i < m_particles.size(); i++)
	{
		Texture::BeginRenderToTexture(tmass);
		m_particles[i]->Draw(mass_program.GetShaderProgram());
		Texture::EndRenderToTexture();
	}*/
}

void App::OnRender2D()
{
    Driver& render = Driver::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer)("\n Speed : ")(timespeed	);
    m_fps->draw();

}

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_KEYDOWN)
    {
		char c = LOWORD(wParam);
        switch(LOWORD(wParam))
        {
        case 'P':
            pause = !pause;
			//cam3D->SetRecvInput(pause);
            break;
		case 'C':
			for(int i =0; i< m_particles.size(); i++)
				delete m_particles[i];
			m_particles.clear();
			break;
		case 'M':
			draw = !draw;
			break;
		case 'L':
			drawMouse = !drawMouse;
			break;
		case 107:
			timespeed *=2.f;
			break;
		case 109:
			timespeed /=2.f;
		}
		
    }
	return 0;
    //return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

int pCount = 6000;
void App::OnClick( int click, vec2 pos, bool up)
{
	printf("click %i at pos (%f,%f), up: i\n",click,pos.x,pos.y,up);
	float f = Driver::Get().GetAspectRatio();
	if(!draw)
		return;
	if(click == 1 && up)
	{
		m_particles.push_back(new ParticlesEmitter(std::string("shader/particle_4.glsl"),pCount	,new Transform(vec3(0,0,0)*30.f)));
	}
	if(click == 2 && up)
	{
		m_particles.push_back(new ParticlesEmitter(std::string("shader/particle_2.glsl"),250,new Transform(vec3((pos.x-0.5f)*f,pos.y-0.5f,0)*30.f)));
	}
	AgmdApplication::OnClick(click,pos,up);
}

void App::OnMove(vec2 pos)
{

	float f = Driver::Get().GetAspectRatio();
	mouse_emitter->GetTransform()->setPosition(vec3((pos.x-0.5f)*f,pos.y-0.5f,0)*30.f);
	mouse_emitter->GetTransform()->update(NULL);
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
		case 'C':
			for(int i =0; i< m_particles.size(); i++)
				delete m_particles[i];
			m_particles.clear();
			break;
		case 'M':
			draw = !draw;
			break;
		case 'L':
			drawMouse = !drawMouse;
			break;
		case WXK_ADD:
			timespeed *=2.f;
			break;
		case WXK_SUBTRACT:
			timespeed /=2.f;
		}

	}
	AgmdApplication::OnKey(key,up);
}
