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


double freq = 8.0f;
double persi = 0.5f;
int octave = 1;
void generateNoise(Texture& t,int size,int seed)
{
	uint32* img = new uint32[size*size];
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(8.f);
	_perlin.SetFrequency(4.f);
	_perlin.SetPersistence(0.5f);
	_perlin.SetSeed(135445);
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule (_perlin);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize (size, size);
	//heightMapBuilder.SetBounds (2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build(0);
	/*noise::utils::RendererImage renderer;
	noise::utils::Image image(size,size);
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);*/
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)	
		{
			float a= heightMap.GetValue(i,j);
			unsigned char* color = (unsigned char*)(&img[i*size+j]); 
			color[0] = a*255; color[1] = a*255; color[2] =a*255;
			color[3] = 255;
			//img[i] = c+((c)<<8)+((c)<<16)+((255)<<24);
		}
	}
	Image _img = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);;
	delete img;

	t.CreateFromImage(_img,PXF_A8R8G8B8);
}
void generateNoise3d(Texture& t,int size,int seed)
{
	//heightMapBuilder.SetBounds (-90.0, 90.0, -180.0, 180.0);

	//PerlinNoise p(1,0.1,1,6,seed);
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(octave);
	_perlin.SetFrequency(freq);
	_perlin.SetPersistence(persi);
	_perlin.SetSeed(5465463);
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule (_perlin);
	heightMapBuilder.SetDestSize (size, size);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetBounds (2.0, 6.0, 1.0, 5.0);
	//heightMapBuilder.Build ();


	noise::utils::RendererImage renderer;
	noise::utils::Image image(size,size);
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	//image.GetValue()
	Image _img[6];
	uint32 * img = new uint32[size*size];
	float max,min = max = 0;
	for(int face = 0; face < 6; face++)
	{
		heightMapBuilder.Build(face);
		renderer.Render ();
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)	
		{
			noise::utils::Color a= image.GetValue(i,j);
			unsigned char* color = (unsigned char*)(&img[i*size+j]); 
			color[0] =  a.red; color[1] =  a.green; color[2] =a.blue;
			color[3] = 255;
			//img[i] = c+((c)<<8)+((c)<<16)+((255)<<24);
		}
	}
		_img[face] = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);
	}
	delete img;

	t.CreateFromImage(_img,PXF_A8R8G8B8);
}

const char* gradient ="Texture/gradient_mars.png";
const char* seed = NULL;

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
ShaderProgram sphereProgram;
ShaderProgram skyProgram;
ShaderProgram lightProgram;

Transform* sphereTransform = new Transform();
Transform* skyTransform = new Transform();
Transform* lightTransform = new Transform();
Planet* p;
vec3 pos ;
void App::OnInit()
{  
    pause = true;
    m_timer = 1000;
	printf("Loading...");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = false;
    DeferredRendering* mode = new DeferredRendering(getScreen());
    RenderingMode::SetRenderingMode(mode);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	
	
	if(gradient)
		color_gradiant.CreateFromFile(gradient,PXF_A8R8G8B8);
	else
		color_gradiant.CreateFromFile("Texture/gradient_terra_desat.png",PXF_A8R8G8B8);

	int _seed;
	if(seed)
		_seed = std::atoi(seed);
	else _seed = rand();


	generateNoise3d(t,256,_seed);
	ShaderPipeline* _default= ShaderPipeline::GetDefaultPipeline();
	ShaderPipeline * planetpipe = new ShaderPipeline(*_default);
	ShaderProgram diffuseShader;
	diffuseShader.LoadFromFile("Shader/planet/planet_rendering.glsl");
	planetpipe->setShader(diffuseShader,RENDERPASS_DIFFUSE);
	mat = new Material(planetpipe);
	mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)| (1<<RENDERPASS_DIFFUSE)));
	mat->SetTexture(color_gradiant,1,(TRenderPass)(1<<RENDERPASS_DEFERRED | (1<<RENDERPASS_DIFFUSE)));
	p = new Planet(mat);
	sphere = CreateSphere(1.0f,100,100,M_PI*2,"",PT_TRIANGLELIST);
	MeshNode* mnode = new MeshNode(sphere,sphereTransform);
    //m_Scene->AddNode(p->GetRoot());

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
	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),10.f);//m_MatProj3D,4.8f,8.8f,vec2(0,-7.55264f),9.87785f); //Follow Camera Theta(4.8) _phi(8.8) angles(0,-7.55264) distance(9.87785)
	cam2D = new FPCamera(m_MatProj2D);
	sphereProgram.LoadFromFile("shader/planet/ground_from_space.glsl");
	skyProgram.LoadFromFile("shader/planet/sky_from_space.glsl");
	lightProgram.LoadFromFile("shader/planet/light.glsl");
    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
	skyTransform->Scale(1.01,1.01,1.01);
	//skyTransform->Translate(2,0,0);
	skyTransform->Update(NULL);

	lightTransform->Translate(5,5,5);
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
	driver.Enable(TRenderParameter::RENDER_ZTEST,true);
	driver.Enable(TRenderParameter::RENDER_ZWRITE,true);
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,false);
	displayable.clear();
	p->GetRoot()->Update(NULL,true);
	p->GetRoot()->FindVisible(cam3D,displayable,l);

	/*if(displayable.size())
		displayable[0]->Render(RENDERPASS_DIFFUSE);*/
	if(!pause)
	for(int i = 0; i < displayable.size(); i++)
		displayable[i]->Render(RENDERPASS_DIFFUSE);
	vec3 campos = cam3D->GetPosition();
	//render sphere / planer
	cam3D->SetActive();
	driver.SetCullFace(2);
	
	

	driver.SetCurrentProgram(lightProgram.GetShaderProgram());
	sphere->Draw(lightTransform);
	driver.SetCurrentProgram(NULL);

	//if(pause)
		//return;

	


	driver.Enable(TRenderParameter::RENDER_ZWRITE,false);
	driver.Enable(TRenderParameter::RENDER_ALPHABLEND,true);
	driver.SetCullFace(1);
	driver.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
	driver.SetCurrentProgram(skyProgram.GetShaderProgram());

	
	skyProgram.SetParameter("v3CameraPos",campos);
	skyProgram.SetParameter("v3LightPos",normalize(vec3(5,5,5)));
	skyProgram.SetParameter("v3InvWavelength",vec3(1.0 / pow(0.650, 4.0), 1.0 / pow(0.570, 4.0), 1.0 / pow(0.475, 4.0)));

	skyProgram.SetParameter("fCameraHeight",length(campos));
	skyProgram.SetParameter("fCameraHeight2",length(campos)*length(campos));

	skyProgram.SetParameter("fInnerRadius",1.f);
	skyProgram.SetParameter("fInnerRadius2",1.f);
	skyProgram.SetParameter("fOuterRadius",1.025f);
	skyProgram.SetParameter("fOuterRadius2",1.025f*1.025f);
	skyProgram.SetParameter("fKrESun", 0.0025f * 15.0f);
	skyProgram.SetParameter("fKmESun", 0.0015f * 15.0f);
	skyProgram.SetParameter("fKr4PI",0.0025f * 4.0f * 3.141592653f);
	skyProgram.SetParameter("fKm4PI",0.0015f * 4.0f * 3.141592653f);
	skyProgram.SetParameter("fScale", 1.0f / (1.025f - 1));
	skyProgram.SetParameter("fScaleDepth",0.25f);
	skyProgram.SetParameter("fScaleOverScaleDepth", 4.0f / (1.025f - 1));
	skyProgram.SetParameter("g",-0.98f);
	skyProgram.SetParameter("g2",-0.98f*-0.98f);
	sphere->Draw(skyTransform);
	driver.SetCurrentProgram(NULL);
	driver.SetCullFace(2);
	mat->Enable(RENDERPASS_DEFERRED);
	driver.Enable(TRenderParameter::RENDER_ZTEST,false);
	driver.SetupAlphaBlending(BLEND_ONE, BLEND_SRCCOLOR);
	driver.SetCurrentProgram(sphereProgram.GetShaderProgram());
	sphereProgram.SetParameter("v3CameraPos",campos);
	sphereProgram.SetParameter("v3LightPos",normalize(vec3(5,5,5)));
	sphereProgram.SetParameter("v3InvWavelength",vec3(1.0 / pow(0.650, 4.0), 1.0 / pow(0.570, 4.0), 1.0 / pow(0.475, 4.0)));

	sphereProgram.SetParameter("fCameraHeight",length(campos));
	sphereProgram.SetParameter("fCameraHeight2",length(campos)*length(campos));

	sphereProgram.SetParameter("fInnerRadius",1.f);
	sphereProgram.SetParameter("fInnerRadius2",1.f);
	sphereProgram.SetParameter("fOuterRadius",1.025f);
	sphereProgram.SetParameter("fOuterRadius2",1.025f*1.025f);
	sphereProgram.SetParameter("fKrESun", 0.0025f * 15.0f);
	sphereProgram.SetParameter("fKmESun", 0.0015f * 15.0f);
	sphereProgram.SetParameter("fKr4PI",0.0025f * 4.0f * 3.141592653f);
	sphereProgram.SetParameter("fKm4PI",0.0015f * 4.0f * 3.141592653f);
	sphereProgram.SetParameter("fScale", 1.0f / (1.025f - 1));
	sphereProgram.SetParameter("fScaleDepth",0.25f);
	sphereProgram.SetParameter("fScaleOverScaleDepth", 4.0f / (1.025f - 1));
	sphereProgram.SetParameter("g",-0.98f);
	sphereProgram.SetParameter("g2",-0.98f*-0.98f);
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
    Driver& render = Driver::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer)("\n Speed : ")(timespeed	)("\n Octave : ")(octave)("\n frequency : ")(freq)("\n persistance : ")(persi);
    m_fps->Draw();

}
//103 100 104 101 105 102
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
		case 107:
			timespeed *=2.f;
			break;
		case 109:
			timespeed /=2.f;
			break;
		case 'C':
			//generateNoise(test,256,100*rand());
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 103:
			freq +=0.1f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 100:
			freq -=0.1f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 104:
			persi +=0.1f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 101:
			persi -=0.1f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 105:
			octave +=1.f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		case 102:
			octave -=1.f;
			generateNoise3d(t,256,rand());
			mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
			break;
		}


		
    }

    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

void App::OnClick( int click, vec2 pos )
{
	printf("click %i at pos (%f,%f)\n",click,pos.x,pos.y);
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

    /*Model* model = MediaManager::Instance().LoadMediaFromFile<Model>("Model/grid25.mesh");
	return model;
	Model::TVertex* vertex = NULL;
	Model::TIndex* index = NULL;
    int vc=0,ic=0;
    model->Export(vertex,index,vc,ic);
    for(int i = 0; i < vc; i++)
    {
        vertex[i].position = r*normalize(vertex[i].position);
        vertex[i].normal = vertex[i].position;
    }
    Model* result = new Model(vertex,vc,index,ic);
    delete[] vertex;
    delete[] index;
    return result;*/
}

Model* App::CreateTriangle(float size, TPrimitiveType type)
{
    std::vector<Model::TVertex> vertices;
    std::vector<Model::TIndex> index;

    for(int i = 0; i < 3; i++)
    {
        Model::TVertex vertex;
        vertex.color = -1;
        vertex.normal = vec3(0.0f,0.0f,1.0f);
        vertex.position = size*vec3(cos(2*M_PI/3*i),sin(2*M_PI/3*i),0.0f);
        vertex.texCoords = vec2(cos(2*M_PI/3*i),sin(2*M_PI/3*i));
        vertices.push_back(vertex);
        index.push_back(i);
    }


    return new Model(&vertices[0],vertices.size(),&index[0],index.size(),type);
}





vec2 intersect(vec4 d1, vec4 d2)
{
    /*
    | A B |   | t |  | d2.x-d1.x |
    | C D | * | s |= | d2.y-d1.y |
    */
    vec2 m3(d2.x-d1.x,d2.y-d1.y);
    mat2 m1(d1.z-d1.x,d1.y-d1.w,d2.z-d2.x,d2.y-d2.w);
    return m1._inverse()*m3;
}