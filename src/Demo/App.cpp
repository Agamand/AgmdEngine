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
#include <Agmd3D/Core/SceneObject/Light.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D/Core/RenderingMode/DeferredRendering.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>
#include <Agmd3D/Core/Camera/FPCamera.h>
#include <Agmd3D/Core/Camera/FollowCamera.h>
#include <AgmdNetwork\Client\Client.h>
#include <AgmdNetwork\Opcode\OpcodeMgr.h>
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
#include <Agmd3D/Core/SceneObject/Material.h>
#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "Loader/objLoader.h"
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


using namespace Agmd;
using namespace AgmdNetwork;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

BaseShaderProgram* default_program;

void generateNoise(uint32*& img,int size,int seed)
{
	img = new uint32[size*size];
	//PerlinNoise p(1,0.1,1,6,seed);
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(15.f);
	_perlin.SetFrequency(4.f);
	_perlin.SetPersistence(0.5f);
	_perlin.SetSeed(seed);
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)	
		{
			int c =  (int)(255*_perlin.GetValue((double)i*0.01,(double)j*0.01,0));//(0.5+glm::noise1(0.5f)+(1+glm::noise1(1.f))/2+(2+glm::noise1(2.f))/4)/3*255;
			unsigned char* color = (unsigned char*)(&img[i*size+j]); 
			color[0] =  c; color[1] = c; color[2] =c;
			color[3] = 255;
			//img[i] = c+((c)<<8)+((c)<<16)+((255)<<24);
		}
	}
}
void generateNoise3d(Texture& t,int size,int seed)
{
	//heightMapBuilder.SetBounds (-90.0, 90.0, -180.0, 180.0);

	//PerlinNoise p(1,0.1,1,6,seed);
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(8.f);
	_perlin.SetFrequency(4.f);
	_perlin.SetPersistence(0.5f);
	_perlin.SetSeed(seed);
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
	/*int iHSize = size/2 // half the size of the cube
	,aa = 123
	,bb = 231
	,cc = 321;
	
	for (int j=0;j<6;j++) {
		
		for (int i=0,l=size*size;i<l;i++) {
			int  x = i%size		// x position in image
			,y = (i/size);	// y position in image
			float a = -iHSize + x+.5	// x position on the cube plane, the added .5 is to get the center of the pixel
			,b = -iHSize + y+.5 // y position on the cube plane
			,c = -iHSize		// z position of the cube plane
			,fDistanceAB = sqrt(a*a+b*b) // to calculate the vectors length we use Pythagoras twice
			,fDistanceABC = sqrt(fDistanceAB*fDistanceAB+c*c)
			,fDrds = .5*fDistanceABC // adjust the distance a bit to get a better radius in the noise field
			,v = 1
			;
			a /= fDrds; // normalize the vector
			b /= fDrds; // normalize the vector
			c /= fDrds; // normalize the vector
			//
			// since we now know the spherical position for one plane we can derive the positions for the other five planes simply by switching the x, y and z values (the a, b and c variables)
			float aNoisePositions[][3]={
				{a,b,c}	// back
				,{-c,b,a}	// right
				,{-a,b,-c}	// front
				,{c,b,-a}	// left
				,{a,c,-b}	// top
				,{a,-c,b}	// bottom
			};
			v = _perlin.GetValue(
			aa + aNoisePositions[j][0]
			,bb + aNoisePositions[j][1]
			,cc + aNoisePositions[j][2]
			);
			int pos = (y*size+x); // the final position of the rgba pixel
			uint8 * color = (uint8 *)&img[pos];
			color[0] = color[1] = color[2] = (int)(v*255);
			color[3] = 255;
		}
		_img[j] = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);
		
	}*/
	
	
	
	/*Image _img[6];
	//Image __img[6];*/
	//SmartPtr<Image> __img  = MediaManager::Instance().LoadMediaFromFile<Image>("Texture/debug.png");
	/*for(int i = 0; i< 6; i++)
	{
		_img[i] = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);//*MediaManager::Instance().LoadMediaFromFile<Image>(File(StringBuilder("Texture/")(i)(".png")));/*Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);*/
	//}*/
	delete img;

	t.CreateFromImage(_img,PXF_A8R8G8B8);
//	t.Create(ivec2(1),PXF_A8R8G8B8,TEXTURE_CUBE);
}

const char* gradient ="Texture/gradient_mars.png";
const char* seed = NULL;

void test()
{
	for(int i = 0; i < 20;i++)
		for (int j = 0; j <20;j++)
		{
			float _alpha = M_PI*i/10.0f,_beta = -M_PI_2+j*M_PI/20.f;
			vec3 o = vec3(cosf(_alpha)*cosf(_beta),sinf(_alpha)*cosf(_beta),sinf(_beta));
			float b=asinf(o.z);
			float cosA = o.x/cosf(b), sinA = o.y/cosf(b);
			float a = atan2f(sinA,cosA);
			vec3 d = vec3(cosf(a)*cosf(b),sinf(a)*cosf(b),sinf(b));
			vec3 diff = o-d;
			float l = length(diff);
			if(l > 0.001f)
				printf("FAIL");
		}

}

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

Texture tvelocity;
Texture tmass;
ShaderProgram velocity_program;
ShaderProgram mass_program;

void App::OnInit()
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
    m_fxaa = new AntiAliasing();
    //PostEffectMgr::Instance().AddEffect(m_fxaa);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	Texture t;
	Texture color_gradiant;
	if(gradient)
		color_gradiant.CreateFromFile(gradient,PXF_A8R8G8B8);
	else
		color_gradiant.CreateFromFile("Texture/gradient2.png",PXF_A8R8G8B8);

	int _seed;
	if(seed)
		_seed = std::atoi(seed);
	else _seed = rand();


	generateNoise3d(t,512,_seed);

	Material* mat = new Material();
	mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
	mat->SetTexture(color_gradiant,1,(TRenderPass)(1<<RENDERPASS_DEFERRED));
	Planet* p = new Planet(mat);
    //m_Scene->AddNode(p->GetRoot());
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
	life->SetBackground(mouse_emitter->extra_buffer[0]);
	GUIMgr::Instance().AddWidget(position);
	GUIMgr::Instance().AddWidget(velocity);
//	GUIMgr::Instance().AddWidget(life);
	SkyBox* box = new SkyBox();
	//box->SetTexture(tex_cubemap);
	//m_Scene->SetSkybox(box);
	boox = box;
	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(-65.7063446,0),10.f);//m_MatProj3D,4.8f,8.8f,vec2(0,-7.55264f),9.87785f); //Follow Camera Theta(4.8) _phi(8.8) angles(0,-7.55264) distance(9.87785)
	cam2D = new FPCamera(m_MatProj2D);

	velocity_program.LoadFromFile("Shader/particle_velocity_render.glsl");
	mass_program.LoadFromFile("Shader/particle_mass_render.glsl");
	tmass.Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
	tvelocity.Create(getScreen(),PXF_A8R8G8B8,TEXTURE_2D);
	position->SetBackground(tmass);
	velocity->SetBackground(tvelocity);
	/*
		Bezier
	*/
	Model* model = MediaManager::Instance().LoadMediaFromFile<Model>("Model/suzanne.obj");
	m_plane = new DrawablePlane(getScreen(),vec2(100,100));
	vec2 points[] = {vec2(-50,-50), vec2(-50,50), vec2(50,50)};
	BaseSpline* spline = new BaseSpline(points,3);
	Bezier* bezier = new Bezier(points,3);
	LineRenderer* renderer = new LineRenderer(bezier);
	MeshNode* node = new MeshNode(model);
	//node->GetTransform().Rotate(90,vec3(1,0,1));
	//m_Scene->AddNode(node);
	m_plane->addSpline(renderer);
	//addInputListener(m_plane);

    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
}
float timespeed= 1.0f;
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
	
	if(pause)
		return;

	for(int i = 0; i < m_particles.size(); i++)
		m_particles[i]->Update(time_diff*timespeed);

	if(drawMouse)
		mouse_emitter->Update(time_diff);

	FollowCamera* cam = static_cast<FollowCamera*>(cam3D);
    const vec2& angles = cam->GetAngles();
	//cam->SetAngles(vec2(angles.x,angles.y+0.001f*time_diff));
	//printf(Camera::GetCurrent(CAMERA_3D)->ToString().c_str());
}

void App::OnRender3D()
{
	if(drawMouse)
		mouse_emitter->Draw();
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->Draw();
		
	}
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
	}
}

void App::OnRender2D()
{
    Driver& render = Driver::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer)("\n Speed : ")(timespeed	);
    m_fps->Draw();

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

    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

void App::OnClick( int click, vec2 pos )
{
	printf("click %i at pos (%f,%f)\n",click,pos.x,pos.y);
	float f = Driver::Get().GetAspectRatio();
	if(!draw)
		return;
	if(click == 1)
	{
		m_particles.push_back(new ParticlesEmitter(std::string("shader/particle_4.glsl"),6000,new Transform(vec3((pos.x-0.5f)*f,pos.y-0.5f,0)*30.f)));
	}
	if(click == 2)
	{
		m_particles.push_back(new ParticlesEmitter(std::string("shader/particle_2.glsl"),250,new Transform(vec3((pos.x-0.5f)*f,pos.y-0.5f,0)*30.f)));
	}
}

void App::OnMove(vec2 pos)
{

	float f = Driver::Get().GetAspectRatio();
	mouse_emitter->GetTransform()->SetPosition(vec3((pos.x-0.5f)*f,pos.y-0.5f,0)*30.f);
	mouse_emitter->GetTransform()->Update(NULL);
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