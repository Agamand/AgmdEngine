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

BaseShaderProgram* default_program;

const char* gradient ="Texture/gradient_terra_desat.png";
const char* seed = NULL;
float layer = 0;
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
Planet* p;
vec3 pos ;
float radius = 1.0f;
float kr = 0.0025f;
float km = 0.0015f;
float eSun = 15.0f;
vec3 rgb(0.650,0.570,0.475);
float g = -0.98f;
Texture ptexture[6];
void App::OnInit()
{  
    pause = true;
    m_timer = 1000;
	printf("Loading... \n");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = true;
    //DeferredRendering* mode = new DeferredRendering(getScreen());
    ForwardRendering* mode = new ForwardRendering(getScreen());
	
	RenderingMode::SetRenderingMode(mode);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	
	printf("init scene\n");
	if(gradient)
		color_gradiant.CreateFromFile(gradient,PXF_A8R8G8B8);
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
	p = new Planet(ptexture,mat,0.05f);
   // m_Scene->AddNode(p->getRoot());

	printf("init planet\n");
	slider_kr = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_kr);
	slider_kr->SetPosition(1300,800);
	slider_kr->SetSize(200,20);
	slider_kr->setValue(&kr,0,0.1f);

	slider_km = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slider_km);
	slider_km->SetPosition(1300,775);
	slider_km->SetSize(200,20);
	slider_km->setValue(&km,0,0.1f);

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
	cam3D =new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),10.f);//m_MatProj3D,4.8f,8.8f,vec2(0,-7.55264f),9.87785f); //Follow Camera Theta(4.8) _phi(8.8) angles(0,-7.55264) distance(9.87785)
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
	slder->setValue(&p->m_offset,-0.1,0.1);

	slder = new ASlider(NULL);
	GUIMgr::Instance().AddWidget(slder);
	slder->SetPosition(1300,500);
	slder->setLabel(std::string("Precision export"));
	slder->SetSize(200,20);
	slder->setValue(&layer,0,10);



	printf("Loading end");
	skyTransform->Scale(1.025,1.025,1.025);
	//skyTransform->Translate(2,0,0);
	skyTransform->Update(NULL);

	lightTransform->Translate(50,50,50);
	lightTransform->Scale(0.2,0.2,0.2);
	
	lightTransform->Update(NULL);
	pos = cam3D->GetPosition();
}
float timespeed= 1.0f;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	
	if(pause)
		return;

	FollowCamera* cam = static_cast<FollowCamera*>(cam3D);
    const vec2& angles = cam->GetAngles();
}

std::vector<DisplayNode*> displayable;
std::vector<LightNode*> l;

void App::OnRender3D()
{
	Driver& driver = Driver::Get();



	

	ivec2 screen = getScreen();
	driver.Enable(TRenderParameter::RENDER_ZTEST,true);
	driver.Enable(TRenderParameter::RENDER_ZWRITE,true);
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,false);
	displayable.clear();
	p->getRoot()->Update(NULL,true,false);
	p->getRoot()->FindVisible(cam3D,displayable,l);
	
	float inner = 1.0f*radius;
	float outer = 1.025f*radius;
/*	if(displayable.size())
		displayable[0]->Render(RENDERPASS_DIFFUSE);
	*/
	//if(pause)
	for(int i = 0; i < displayable.size(); i++)
		displayable[i]->Render(RENDERPASS_DIFFUSE);

	return;
	vec3 campos = cam3D->GetPosition();
	//render sphere / planer
	cam3D->SetActive();
	driver.SetCullFace(2);

	driver.SetCurrentProgram(lightProgram.GetShaderProgram());
	sphere->Draw(lightTransform);
	driver.SetCurrentProgram(NULL);

	if(pause)
		return;

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
			p->exportToFile("planet_1.obj",(int)layer);
			break;
		case 'G':
			GUIMgr::Instance().Enable(!GUIMgr::Instance().isEnable());
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







#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

Model* App::CreateSphere(float r,float stack, float slice,float angle, std::string texture, TPrimitiveType type, a_uint32 color)
{
    float cosa = 1.0f;
    float sina = 0.0f;
    float cosa1 = cos(angle/stack);
    float sina1 = sin(angle/stack);

    std::vector<Model::TVertex> vertices;
    std::vector<Model::TIndex> index;

    for(int i = 0; i <= stack; i++)
    {
        for(int j = 0; j <= slice; j++)
        {
            Model::TVertex vertex;
            vertex.color = color;
            vertex.normal = vec3(cos(i*angle/stack)*sin(j*M_PI/slice),sin(i*angle/stack)*sin(j*M_PI/slice), cos(j*M_PI/slice));
            vertex.position = vec3(r*cos(i*angle/stack)*sin(j*M_PI/slice),r*sin(i*angle/stack)*sin(j*M_PI/slice), r*cos(j*M_PI/slice));
            vertex.texCoords = vec2(i/stack*angle/(M_PI*2),1.0f-j/slice);
            vertices.push_back(vertex);
        }
    }

    for(int i = 0; i < stack;i++)
    {
        for(int j = 0; j < slice; j++)
        {
            /*(i,j+1) _ _ (i+1,j+1)
            |  /|
            | / |
            (i,j)|/  |(i+1,j)
            */
            int _i = SELECT(i+1,stack+1), _j = SELECT(j+1,(slice+1));

            index.push_back(_i*((int)slice+1)+j);
            index.push_back(i*((int)slice+1)+j);
            index.push_back(_i*((int)slice+1)+_j);

            index.push_back(i*((int)slice+1)+j);
            index.push_back(i*((int)slice+1)+_j);
            index.push_back(_i*((int)slice+1)+_j);
        }
    }
    Model* m = new Model(&vertices[0],vertices.size(),&index[0],index.size(),type);
    Texture tex;
    if(texture.length() != 0)
        tex.CreateFromFile(texture,PXF_A8R8G8B8);

    return m;
}

Model* App::CreatePlane(ivec2 size,ivec2 n_poly, std::string texture, TPrimitiveType type)
{

    std::vector<Model::TVertex> vertices;
    std::vector<Model::TIndex> index;

    float x_2 = size.x/2.0f;
    float y_2 = size.y/2.0f;

    vec2 polysize = vec2(size);
    polysize /= n_poly;

    for(int i = 0; i <= n_poly.x; i++)
    {
        for(int j = 0; j <= n_poly.y; j++)
        {
            Model::TVertex vertex;
            vertex.color = -1;
            vertex.normal = vec3(0.0f,0.0f,1.0f);
            vertex.position = vec3(i*polysize.x-x_2,j*polysize.y-y_2,0.0f);
            vertex.texCoords = vec2(i/((float)n_poly.x),j/((float)n_poly.y));
            vertices.push_back(vertex);
        }
    }

    a_uint32 npoly = n_poly.x*n_poly.y;


    for(int i = 0; i < n_poly.x;i++)
    {
        for(int j = 0; j < n_poly.y; j++)
        {
            int _i = SELECT(i+1, n_poly.x+1), _j = SELECT(j+1, n_poly.y+1);
            index.push_back(i*(n_poly.y+1)+j);
            index.push_back(_i*(n_poly.y+1)+j);
            index.push_back(_i*(n_poly.y+1)+_j);

            index.push_back(i*(n_poly.y+1)+j);
            index.push_back(_i*(n_poly.y+1)+_j);
            index.push_back(i*(n_poly.y+1)+_j);
        }
    }

    Model* m = new Model(&vertices[0],vertices.size(),&index[0],index.size(),type);
    Texture tex;
    if(texture.length() != 0)
        tex.CreateFromFile(texture,PXF_A8R8G8B8);

    return m;
}
Model* App::CreateBox(vec3 size, std::string texture, Agmd::TPrimitiveType type)
{
    Model::TVertex vertex[] = 
    {    
        //Z+
        {vec3(size.x/2,size.y/2,size.z/2),vec3(0,0,1),-1,vec2(1,0)},
        {vec3(size.x/2,-size.y/2,size.z/2),vec3(0,0,1),-1,vec2(1,1)},
        {vec3(-size.x/2,size.y/2,size.z/2),vec3(0,0,1),-1,vec2(0,0)},
        {vec3(-size.x/2,-size.y/2,size.z/2),vec3(0,0,1),-1,vec2(0,1)},
        //Z-
        {vec3(-size.x/2,-size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(0,0)},
        {vec3(size.x/2,-size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(1,0)},
        {vec3(-size.x/2,size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(0,1)},
        {vec3(size.x/2,size.y/2,-size.z/2),vec3(0,0,-1),-1,vec2(1,1)},
        //X-
        {vec3(-size.x/2,-size.y/2,-size.z/2),vec3(-1,0,0),-1,vec2(0,0)},
        {vec3(-size.x/2,size.y/2,-size.z/2),vec3(-1,0,0),-1,vec2(1,0)},
        {vec3(-size.x/2,-size.y/2,size.z/2),vec3(-1,0,0),-1,vec2(0,1)},
        {vec3(-size.x/2,size.y/2,size.z/2),vec3(-1,0,0),-1,vec2(1,1)},
        //Y+
        {vec3(-size.x/2,size.y/2,-size.z/2),vec3(0,1,0),-1,vec2(0,0)},
        {vec3(size.x/2,size.y/2,-size.z/2),vec3(0,1,0),-1,vec2(1,0)},
        {vec3(-size.x/2,size.y/2,size.z/2),vec3(0,1,0),-1,vec2(0,1)},
        {vec3(size.x/2,size.y/2,size.z/2),vec3(0,1,0),-1,vec2(1,1)},
        //X+
        {vec3(size.x/2,size.y/2,-size.z/2),vec3(1,0,0),-1,vec2(0,0)},
        {vec3(size.x/2,-size.y/2,-size.z/2),vec3(1,0,0),-1,vec2(1,0)},
        {vec3(size.x/2,size.y/2,size.z/2),vec3(1,0,0),-1,vec2(0,1)},
        {vec3(size.x/2,-size.y/2,size.z/2),vec3(1,0,0),-1,vec2(1,1)},
        //Y-
        {vec3(size.x/2,-size.y/2,-size.z/2),vec3(0,-1,0),-1,vec2(0,0)},
        {vec3(-size.x/2,-size.y/2,-size.z/2),vec3(0,-1,0),-1,vec2(1,0)},
        {vec3(size.x/2,-size.y/2,size.z/2),vec3(0,-1,0),-1,vec2(0,1)},
        {vec3(-size.x/2,-size.y/2,size.z/2),vec3(0,-1,0),-1,vec2(1,1)}
    };

    std::vector<Model::TIndex> indices;

    for(a_uint32 i = 0; i < 6; i++)
    {
        indices.push_back(2+i*4);
        indices.push_back(1+i*4);
        indices.push_back(0+i*4);

        indices.push_back(1+i*4);
        indices.push_back(2+i*4);
        indices.push_back(3+i*4);
    }
    Model* m = new Model(vertex,4*6,&indices[0],indices.size(),type);
    Texture tex;
    if(texture.length() != 0)
        tex.CreateFromFile(texture,PXF_A8R8G8B8);

    return m;
}

void _CreatePlane(vec3 orientation, quat rot,int size, int offset_index, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
{
    float x_2 = 1;
    float y_2 = 1;
    vec3 o = -vec3(0.5f,0.5f,0);
    int count = size;
    float offset = 1.f/count;
	
    for(int i = 0; i <= count; i++)
    {
        for(int j = 0; j <= count; j++)
        {
            Model::TVertex vertex;
            vertex.color = -1;
            vertex.normal = orientation;
            vertex.position = orientation/2.f+rot*vec3(o.x+offset*i,o.y+offset*j,0.f);
            vertex.texCoords = vec2(i*offset,j*offset);
            vertices.push_back(vertex);
        }
    }



    for(int i = 0; i < count;i++)
    {
        for(int j = 0; j < count; j++)
        {
            int _i = SELECT(i+1, count+1), _j = SELECT(j+1, count+1);
            index.push_back(offset_index+i*(count+1)+j);
            index.push_back(offset_index+_i*(count+1)+j);
            index.push_back(offset_index+_i*(count+1)+_j);

            index.push_back(offset_index+i*(count+1)+j);
            index.push_back(offset_index+_i*(count+1)+_j);
            index.push_back(offset_index+i*(count+1)+_j);
        }
    }
}


Model* App::CreateMetaSphere(float r, int stack, int slice)
{
	std::vector<Model::TVertex> vertices;
	std::vector<Model::TIndex> indices;

	quat sRot[] = {
		quat(),
		quat(glm::rotate(mat4(1),180.f,vec3(1,0,0))),
		quat(glm::rotate(mat4(1),90.f,vec3(0,1,0))),
		quat(glm::rotate(mat4(1),-90.f,vec3(0,1,0))),
		quat(glm::rotate(mat4(1),-90.f,vec3(1,0,0))),
		quat(glm::rotate(mat4(1),90.f,vec3(1,0,0)))
	};

	vec3 sOri[] = {
		vec3(0,0,1),
		vec3(0,0,-1),
		vec3(1,0,0),
		vec3(-1,0,0),
		vec3(0,1,0),
		vec3(0,-1,0)
	};

	for(a_uint32 i = 0; i < 6; i++)
		_CreatePlane(sOri[i],sRot[i],20,vertices.size(),vertices,indices);
	
	for(int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = r*normalize(vertices[i].position);
		vertices[i].normal = vertices[i].position;
	}
	return new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
}
