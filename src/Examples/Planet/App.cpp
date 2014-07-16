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
#include <Agmd3D/Core/Effects/BlurEffect.h>
#include <Agmd3D/Core/Effects/AsciEffect.h>

#include <Agmd3D/Core/RenderObject/MeshRender.h>

#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <Agmd3D/Core/GUI/AWindow.h>

#include <Agmd3D/Core/Shader/ShaderPreCompiler.h>

#include <Agmd3D/Core/Tools/Statistics.h>



#include <Renderer/OpenGL/GlDriver.h>

#include <Agmd3D/Core/Tools/Fast2DSurface.h>

#include <glm/ext.hpp>
#include "PerlinNoise.h"
#include <libnoise/noise.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "simplexnoise.h"
#include "noiseutils.h"
#include <Core/Shader/ShaderPipeline.h>


using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);





void generateNoiseFace(Texture& t,int size,int seed,int face, vec4 bounds = vec4(0,1,0,1));
void generateNoiseFace(Texture& t,int size,int seed,int face, vec4 bounds)
{
	//heightMapBuilder.SetBounds (-90.0, 90.0, -180.0, 180.0);

	//PerlinNoise p(1,0.1,1,6,seed);
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(8);
	_perlin.SetFrequency(0.2f);
	_perlin.SetPersistence(0.5f);
	_perlin.SetSeed(5465463);
	_perlin.SetNoiseQuality(noise::NoiseQuality::QUALITY_FAST);
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule (_perlin);
	heightMapBuilder.SetDestSize (size, size);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetBounds (bounds.x,bounds.y,bounds.z,bounds.w);
	//heightMapBuilder.Build ();


	noise::utils::RendererImage renderer;
	noise::utils::Image image(size,size);
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	//image.GetValue()
	Image _img;
	uint32 * img = new uint32[size*size];
	float max,min = max = 0;
	heightMapBuilder.Build(face);
	renderer.Render ();
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)	
		{
			//noise::utils::Color a= image.GetValue(i,j);
			vec3 pos(-0.5f+i/(float)size,-0.5f+j/(float)size,0.5f);
			pos = normalize(pos);
			float value = _perlin.GetValue(pos.x,pos.y,pos.z);
			a_uint8* c =(a_uint8*)&img[i*size+j];
			c[0] = c[1] =c[2] =0;
			if(value > 1)
				c[0] = 255;
			else if(value < 0)
				c[1] = 255;
			else c[2] = 255;
			c[3] = 255;
			
		}
	}
	_img = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);
	delete img;

	t.CreateFromImage(_img,PXF_A8R8G8B8);
}



BaseShaderProgram* default_program;

const char* gradient ="Texture/gradient_terra_desat.png";//superb_terra.png";
const char* seed = NULL;
float layer = 0;

Texture height_test;
Texture normal_test;







void App::Run(int argc, char** argv)
{
    if(argc > 0)
	{
		File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
		ShaderPreCompiler::Instance().AddSearchPath(main.Path()+"/Shader");
	}
	if(argc > 1)
		gradient = argv[1];
	if(argc > 2)
		seed = argv[2];
    AgmdApp::Run();
}

#include "Planet/Planet.h"
SkyBox* boox;
Texture t;
Texture test;
Texture color_gradiant;
Material* mat;

Model* sphere;
Model* sphere2;
Model* plane_test;
Material* test_material;
Transform* test_transform;

ShaderProgram groundProgram[2];
ShaderProgram skyProgram[2];



ShaderProgram lightProgram;

Transform* sphereTransform = new Transform();
Transform* skyTransform = new Transform();
Transform* lightTransform = new Transform();

ASlider* slider_kr,
	 *slider_km,
	 *slider_esun,
	 *slider_r,
	 *slider_g,
	 *slider_b,
	 *slider_gg;
Planet* planet;
PlanetModel* pmodel;
vec3 pos ;
float radius = 100.0f;
float kr = 0.0025f;
float km = 0.0015f;
float eSun = 15.0f;
vec3 rgb(0.650,0.570,0.475);
float g = -0.98f;
void App::OnInit()
{ 

    pause = true;
    m_timer = 1000;
	printf("Loading... \n");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 1000.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = true;
    //DeferredRendering* mode = new DeferredRendering(getScreen());
    ForwardRendering* mode = new ForwardRendering(getScreen());
	
	RenderingMode::SetRenderingMode(mode);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	
	printf("init scene\n");
	if(gradient)
		color_gradiant.CreateFromFile(gradient,PXF_A8R8G8B8,TEX_WRAP_CLAMP);
	else
		color_gradiant.CreateFromFile("Texture/gradient_terra_desat.png",PXF_A8R8G8B8);

	int _seed;
	if(seed)
		_seed = std::atoi(seed);
	else _seed = rand();
	
	ShaderPipeline* _default= ShaderPipeline::GetDefaultPipeline();
	ShaderPipeline * planetpipe = new ShaderPipeline(*_default);
	ShaderProgram diffuseShader;
	diffuseShader.LoadFromFile("Shader/planet/planet_rendering.glsl");
	planetpipe->setShader(diffuseShader,RENDERPASS_DIFFUSE);
	mat = new Material(planetpipe);
	mat->SetTexture(color_gradiant,1,(TRenderPass)(1<<RENDERPASS_DEFERRED | (1<<RENDERPASS_DIFFUSE)));
	pmodel = new PlanetModel(0,0,0);
	pmodel->m_persistance = 1.f;
	pmodel->m_octave = 1.0f;
	pmodel->m_frequency = 3.f;
	planet = new Planet(pmodel,mat,0.05f);
	sphere = GeometryFactory::createSphere(1,80,80,M_PI*2);
	plane_test = GeometryFactory::createPlane(ivec2(1),ivec2(20));
	Texture test;
	test_material = new Material();
	generateNoiseFace(test,256,0,0);
	test_transform = new Transform(vec3(1,0,0));
	MeshNode* n = new MeshNode(plane_test,test_transform);
	test_material->SetTexture(test,0,(TRenderPass)(1<<RENDERPASS_DIFFUSE));
	n->setMaterial(test_material);


	// m_Scene->AddNode(p->getRoot());

	printf("init planet\n");
	
	m_persistanceSlider = new ASlider("Persistance",ivec2(1300.0f,800.0f),ivec2(200,20));
	m_persistanceSlider->setValue(&pmodel->m_persistance,0.0f,2.0f);
	GUIMgr::Instance().AddWidget(m_persistanceSlider);

	m_octaveCountSlider = new ASlider("Octave",ivec2(1300.f,750.0f),ivec2(200,20));
	m_octaveCountSlider->setValue(&pmodel->m_octave,0.0f,2.0f);
	GUIMgr::Instance().AddWidget(m_octaveCountSlider);

	m_frequencySlider = new ASlider("Frequency",ivec2(1300.0f,700.0f),ivec2(200,20));
	m_frequencySlider->setValue(&pmodel->m_frequency,0.0f,2.0f);
	GUIMgr::Instance().AddWidget(m_frequencySlider);
	/*
	slider_esun = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_esun);
	slider_esun->SetPosition(1300,750);
	slider_esun->SetSize(200,20);
	slider_esun->setValue(&eSun,0,30.f);

	slider_r = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_r);
	slider_r->SetPosition(1300,725);
	slider_r->SetSize(200,20);
	slider_r->setValue(&rgb.r,0,1.f);

	slider_g = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_g);
	slider_g->SetPosition(1300,700);
	slider_g->SetSize(200,20);
	slider_g->setValue(&rgb.g,0,1.f);

	slider_b = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_b);
	slider_b->SetPosition(1300,675);
	slider_b->SetSize(200,20);
	slider_b->setValue(&rgb.b,0,1);

	slider_gg = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_gg);
	slider_gg->SetPosition(1300,650);
	slider_gg->SetSize(200,20);
	slider_gg->setValue(&g,-1,-0.5);
	*/

	ASlider *slder = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slder);
	slder->SetPosition(1300,600);
	slder->setLabel(std::string("Cam Speed"));
	slder->SetSize(200,20);
	

	printf("init slider\n");

	
    Driver::Get().SetActiveScene(m_Scene);
    Driver::Get().SetCullFace(2);

    m_light = new Light(vec3(0, 0 ,10),-normalize(vec3(0,0.2,-1)),LightType::LIGHT_DIR);//new Light(vec3(0,0,10),-normalize(vec3(0,0.5,-1)),LIGHT_SPOT);
    m_Scene->AddLight(m_light);
    m_light->SetRange(2000.0f);	
	string cubemap[6];
	for(int i = 0; i < 6; i++)
	{
		cubemap[i] = StringBuilder("Texture/background/")(i+1)(".png");
	}
	test.CreateFromFile(cubemap[0],PXF_A8R8G8B8);
	Texture tex_cubemap;
	tex_cubemap.CreateFromFile(cubemap,PXF_A8R8G8B8);
	SkyBox* box = new SkyBox();
	box->SetTexture(tex_cubemap);
    //m_Scene->SetSkybox(box);
	boox = box;
	cam3D =new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),120.f);//m_MatProj3D,4.8f,8.8f,vec2(0,-7.55264f),9.87785f); //Follow Camera Theta(4.8) _phi(8.8) angles(0,-7.55264) distance(9.87785)
	slder->setValue(cam3D->GetSpeedPtr(),0.1,20.0f);
	cam2D = new FPCamera(m_MatProj2D);
	groundProgram[0].LoadFromFile("shader/planet/ground_from_space.glsl");
	groundProgram[1].LoadFromFile("shader/planet/ground_from_atmo.glsl");
	skyProgram[0].LoadFromFile("shader/planet/sky_from_space.glsl");
	skyProgram[1].LoadFromFile("shader/planet/sky_from_atmo.glsl");
	lightProgram.LoadFromFile("shader/planet/light.glsl");
    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);


	slder = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slder);
	slder->SetPosition(1300,550);
	slder->setLabel(std::string("Offset"));
	slder->SetSize(200,20);
	slder->setValue(&planet->m_offset,-0.1,0.1);
	
	slder = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slder);
	slder->SetPosition(1300,500);
	slder->setLabel(std::string("Precision export"));
	slder->SetSize(200,20);
	slder->setValue(&layer,0,10);



	printf("Loading end");
	skyTransform->Scale(1.025,1.025,1.025);
	skyTransform->Scale(100.0f,100.0f,100.0f);
	//skyTransform->Translate(2,0,0);
	skyTransform->Update(NULL);

	lightTransform->Translate(50,50,50);
	lightTransform->Scale(0.2,0.2,0.2);
	sphereTransform->Scale(100.0f,100.0f,100.0f);
	
	lightTransform->Update(NULL);
	pos = cam3D->GetPosition();
}
float timespeed= 1.0f;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	
	if(pause)
		return;
}

a_vector<DisplayNode*> displayable;
a_vector<LightNode*> l;

void App::OnRender3D()
{
	//pmodel->generateTexture(height_test,normal_test,translate(mat4(1),vec3(0,0,0.5f)));
	//return;
	Driver& driver = Driver::Get();
	


	

	ivec2 screen = getScreen();
	driver.Enable(TRenderParameter::RENDER_ZTEST,true);
	driver.Enable(TRenderParameter::RENDER_ZWRITE,true);
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,false);
	displayable.clear();
	planet->getRoot()->Update(NULL,true,false);
	planet->getRoot()->FindVisible(cam3D,displayable,l);
	
	float inner = 1.0f*radius;
	float outer = 1.025f*radius;
/*	if(displayable.size())
		displayable[0]->Render(RENDERPASS_DIFFUSE);
	*/
	//if(pause)
	for(int i = 0; i < displayable.size(); i++)
		displayable[i]->Render(RENDERPASS_DIFFUSE);

	if(pause)
		return;
	vec3 campos = cam3D->GetPosition();
	//render sphere / planer
	cam3D->SetActive();
	driver.SetCullFace(2);

	driver.SetCurrentProgram(lightProgram.GetShaderProgram());
	sphere->Draw(lightTransform);
	driver.SetCurrentProgram(NULL);

	

	driver.SetCullFace(1);
	int use;
	float l = length(campos);
	if(l > outer)
	{
		driver.Enable(TRenderParameter::RENDER_ZWRITE,false);
		driver.Enable(TRenderParameter::RENDER_ALPHABLEND,true);
		driver.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
		use = 0; 
	}else use = 1;

	driver.SetCurrentProgram(skyProgram[use].GetShaderProgram());
	skyProgram[use].SetParameter("v3CameraPos",campos);
	skyProgram[use].SetParameter("v3LightPos",normalize(vec3(5,5,5)));
	skyProgram[use].SetParameter("v3InvWavelength",vec3(1.0 / pow(rgb.r, 4.0f), 1.0 / pow(rgb.g, 4.0f), 1.0 / pow(rgb.b, 4.0f)));

	skyProgram[use].SetParameter("fCameraHeight",length(campos));
	skyProgram[use].SetParameter("fCameraHeight2",length(campos)*length(campos));

	skyProgram[use].SetParameter("fInnerRadius",inner);
	skyProgram[use].SetParameter("fInnerRadius2",inner*inner);
	skyProgram[use].SetParameter("fOuterRadius",outer);
	skyProgram[use].SetParameter("fOuterRadius2",outer*outer);
	skyProgram[use].SetParameter("fKrESun", kr * eSun);
	skyProgram[use].SetParameter("fKmESun", km * eSun);
	skyProgram[use].SetParameter("fKr4PI",kr * 4.0f * 3.141592653f);
	skyProgram[use].SetParameter("fKm4PI",km * 4.0f * 3.141592653f);
	skyProgram[use].SetParameter("fScale", 1.0f / (outer - inner));
	skyProgram[use].SetParameter("fScaleDepth",0.25f);
	skyProgram[use].SetParameter("fScaleOverScaleDepth", 4.0f / (outer - inner));
	skyProgram[use].SetParameter("g",g);
	skyProgram[use].SetParameter("g2",g*g);
	sphere->Draw(skyTransform);
	driver.SetCurrentProgram(NULL);
	driver.SetCullFace(2);
	use = 0;
	mat->Enable(RENDERPASS_DEFERRED);
	driver.Enable(TRenderParameter::RENDER_ZWRITE,false);
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,true);
	driver.Enable(TRenderParameter::RENDER_ZTEST,false);
	driver.SetupAlphaBlending(BLEND_ONE, BLEND_SRCCOLOR);
	driver.SetCurrentProgram(groundProgram[use].GetShaderProgram());
	groundProgram[use].SetParameter("v3CameraPos",campos);
	groundProgram[use].SetParameter("v3LightPos",normalize(vec3(5,5,5)));
	groundProgram[use].SetParameter("v3InvWavelength",vec3(1.0 / pow(rgb.r, 4.0f), 1.0 / pow(rgb.g, 4.0f), 1.0 / pow(rgb.b, 4.0f)));

	groundProgram[use].SetParameter("fCameraHeight",length(campos));
	groundProgram[use].SetParameter("fCameraHeight2",length(campos)*length(campos));

	groundProgram[use].SetParameter("fInnerRadius",inner);
	groundProgram[use].SetParameter("fInnerRadius2",inner*inner);
	groundProgram[use].SetParameter("fOuterRadius",outer);
	groundProgram[use].SetParameter("fOuterRadius2",outer*outer);
	groundProgram[use].SetParameter("fKrESun", kr * eSun);
	groundProgram[use].SetParameter("fKmESun", km * eSun);
	groundProgram[use].SetParameter("fKr4PI",kr * 4.0f * 3.141592653f);
	groundProgram[use].SetParameter("fKm4PI",km * 4.0f * 3.141592653f);
	groundProgram[use].SetParameter("fScale", 1.0f / (outer - inner));
	groundProgram[use].SetParameter("fScaleDepth",0.25f);
	groundProgram[use].SetParameter("fScaleOverScaleDepth", 4.0f / (outer - inner));
	groundProgram[use].SetParameter("g",g);
	groundProgram[use].SetParameter("g2",g*g);
	sphere->Draw(sphereTransform);
	driver.SetCurrentProgram(NULL);
	mat->Disable();
	
	//Fast2DSurface::Instance().Draw();
	
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,false);
	driver.Enable(TRenderParameter::RENDER_ZWRITE,true);
	driver.Enable(TRenderParameter::RENDER_ZTEST,true);

	

}

void App::OnRender2D()
{
	if(!GUIMgr::Instance().isEnable())
		return;
    Driver& render = Driver::Get();
    /**(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer)("\n Speed : ")(timespeed	)
	("\nkr : ")(kr)
	("\nkm : ")(km)
	("\neSun : ")(eSun)
	("\nrbg.r")(rgb.r)
	("\nrgb.g")(rgb.g)
	("\nrgb.b")(rgb.b)
	("\ng")(g);*/
    m_fps->Draw();

}
//103 100 104 101 105 102
LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	MeshNode *node;
    if(message == WM_KEYDOWN)
    {
		char c = LOWORD(wParam);
        switch(LOWORD(wParam))
        {
        case 'P':
            pause = !pause;
            break;
		case 'E':
			planet->exportToFile("planet_1.obj",(int)layer);
			break;
		case 'G':
			GUIMgr::Instance().Enable(!GUIMgr::Instance().isEnable());
			break;
		case 'N':
			pmodel->m_normal_mapping = pmodel->m_normal_mapping ? 0 : 1;
			break;
		
		}


		
    }

    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

void App::OnClick( int click, vec2 pos )
{
	
}
	

void App::OnMove(vec2 pos)
{

}	








