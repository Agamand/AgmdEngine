#include "App.h"
#include <Core\Renderer.h>
#include <Core\Enums.h>
#include <Core\Declaration.h>
#include <Core\DeclarationElement.h>
#include <Core\ResourceManager.h>
#include <Core\Terrain.h>
#include <Core\MediaManager.h>
#include <Core\FrameBuffer.h>
#include <Core\GraphicString.h>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace Agmd;
SINGLETON_IMPL(App)

#define EARTH_MOON_R 3.661786780f
#define KM_MOON 0.0005760f
#define GRAVITY_ACCELERATION (6.67420f*(std::pow(10.0,-11.0))) // 10^-11
#define P_10_22 (std::pow(10,22))

void App::OnInit()
{
	camera.setPosition(-3.0,0.0,0.0);
	m_MatProj3D = glm::perspectiveFov(60.0f, (float)getScreen().x, (float)getScreen().y, 0.1f, 10000.0f);
	m_MatView3D = camera.look();

	m_MatView2D = mat4(1.0f); // m4 identity
	m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);

	tang = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("shownormal.glsl");
	shader2D = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("classic_pipeline_2D.glsl");
	tex_shadow = Renderer::Get().CreateTexture(ivec2(512,512),PXF_DEPTH);
	//rbo_shadow = Renderer::Get().CreateRenderBuffer(ivec2(512,512),TPixelFormat::PXF_A8R8G8B8);
	fbo_shadow = Renderer::Get().CreateFrameBuffer();
	fbo_shadow->setTexture(tex_shadow,DEPTH_ATTACHMENT);
	//fbo_shadow->setRender(rbo_shadow,COLOR_ATTACHMENT);


    Model::TVertex Vertices[] =
    {
		{vec3(0.000f,  0.000f,  1.000f), vec3(0,0,0), 0xFFFFFFFF, vec2(0,0)},
        {vec3(0.894f,  0.000f,  0.447f), vec3(0,0,0), 0xFF0000FF, vec2(0,0)},
        {vec3(0.276f,  0.851f,  0.447f), vec3(0,0,0), 0xFF00FF00, vec2(0,0)},
        {vec3(-0.724f,  0.526f,  0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},

		{vec3(-0.724f, -0.526f,  0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(0.276f, -0.851f,  0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(0.724f,  0.526f, -0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(-0.276f,  0.851f, -0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(-0.894f,  0.000f, -0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(-0.276f, -0.851f, -0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(0.724f, -0.526f, -0.447f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)},
		{vec3(0.000f,  0.000f, -1.000f), vec3(0,0,0), 0xFFFF0000, vec2(0,0)}
    };
	
	Model::TVertex Ground[] =
	{
		{vec3(20.0f,20.0f,0.0f),vec3(0,0,1), 0xFFFFFFFF, vec2(0,0)},
		{vec3(-20.0f,20.0f,0.0f),vec3(0,0,1), 0xFFFFFFFF, vec2(0,0)},
		{vec3(-20.0f,-20.0f,0.0f),vec3(0,0,1), 0xFFFFFFFF, vec2(0,0)},
		{vec3(20.0f,-20.0f,0.0f),vec3(0,0,1), 0xFFFFFFFF, vec2(0,0)}
	};

	Model::TVertex Repere[] =
	{
		{vec3(0,0,0),vec3(0,0,1), 0xFFFF0000, vec2(0,0)},
		{vec3(1.0f,0.0f,0.0f),vec3(0,0,1), 0xFFFF0000, vec2(0,0)},
		{vec3(0,0,0),vec3(0,0,1), 0xFF00FF00, vec2(0,0)},
		{vec3(0.0f,1.0f,0.0f),vec3(0,0,1), 0xFF00FF00, vec2(0,0)},
		{vec3(0,0,0),vec3(0,0,1), 0xFF0000FF, vec2(0,0)},
		{vec3(0.0f,0.0f,1.0f),vec3(0,0,1), 0xFF0000FF, vec2(0,0)},

	};

	/*
    Model::TVertex Vertices2[] =
    {
		{vec3(1,-1,-1), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(1,1,-1), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(1,1,1), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(1,-1,1), vec3(0,0,0), 0x0, vec2(0,0)},
    };
    Model::TVertex Vertices3[] =
    {
		{vec3(1,1,2), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(1,-1,2), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(-1,-1,2), vec3(0,0,0), 0x0, vec2(0,0)},
        {vec3(-1,1,2), vec3(0,0,0), 0x0, vec2(0,0)},
    };
    Model::TVertex Vertices4[] =
    {
		{vec3(1,1,3), vec3(0,0,0), 0xFF0000FF, vec2(0,0)},
        {vec3(1,-1,3), vec3(0,0,0), 0x0000FF, vec2(0,0)},
        {vec3(-1,-1,3), vec3(0,0,0), 0x000000FF, vec2(0,0)},
        {vec3(-1,1,3), vec3(0,0,0), 0xFF0000FF, vec2(0,0)},
    };*/

	Model::TIndex Indices[] = 
	{
        2, 1, 0,
        3, 2, 0,
        4, 3, 0,
        5, 4, 0,
        1, 5, 0,

        11, 6,  7,
        11, 7,  8,
        11, 8,  9,
        11, 9,  10,
        11, 10, 6,

        1, 2, 6,
        2, 3, 7,
        3, 4, 8,
        4, 5, 9,
        5, 1, 10,

        2,  7, 6,
        3,  8, 7,
        4,  9, 8,
        5, 10, 9,
        1, 6, 10
	};



	Model::TIndex GroundIndices[] = 
	{
		0,1,2,
		1,2,3
	};

	Model::TIndex RepereIndices[] = 
	{
		0,1,
		2,3,
		4,5
	};

	//m_modelVector.push_back(new Model(Vertices,sizeof(Vertices)/sizeof(Model::TVertex),Indices,sizeof(Indices)/sizeof(Model::TIndex),""));
	/*m_modelVector.push_back(MediaManager::Instance().LoadMediaFromFile<Agmd::Model>("amarr.obj"));
	m_modelVector.push_back(new Model(Ground,sizeof(Ground)/sizeof(Model::TVertex),GroundIndices,sizeof(GroundIndices)/sizeof(Model::TIndex),""));
	m_modelVector.push_back(new Model(Repere,sizeof(Repere)/sizeof(Model::TVertex),RepereIndices,sizeof(RepereIndices)/sizeof(Model::TIndex),"",PT_LINELIST));
	m_modelVector[0]->Rotate(90,vec3(1,0,0));*/

	//m_modelVector.push_back( new Terrain(ivec2(100,100),ivec2(200,200),"","L.png") );
	moon_n.CreateFromFile("moon_n.png",PXF_A8R8G8B8);
	moon_h.CreateFromFile("moon_h.png",PXF_A8R8G8B8);
	earth_n.CreateFromFile("earth_n.png",PXF_A8R8G8B8);
	earth_h.CreateFromFile("earth_h.png",PXF_A8R8G8B8);
	m_modelVector.push_back( CreateSphere(100.0f,250.0f,250.0f, (float)2*M_PI ,"earth_d.png"));
	m_modelVector.push_back( CreateSphere(100.0f,250.0f,250.0f, (float)2*M_PI ,"moon_d.png"));

	m_modelVector[1]->Move(300.0f,0.0f,0.0f);

	planete_array[0].model = m_modelVector[0];
	planete_array[0].mass = 597.360f;
	planete_array[0].size = EARTH_MOON_R;
	planete_array[0].velocity = dvec3(0.0f);

	planete_array[1].model = m_modelVector[1];
	planete_array[1].mass = 7.34770f;
	planete_array[1].size = 1.0f;
	planete_array[1].velocity = dvec3(0.0f,1.022*KM_MOON*std::pow(10.0,3.0),0.0f);

	m_fps = new GraphicString(ivec2(200,200),"",Color::black);

}


void update_POS(planete_info* info, double time)
{
	time *=3600*24/(double)SECONDS_IN_MS;
	dvec3 pos_e = dvec3(info[0].model->getTranslate()*vec4(0.0f,0.0f,0.0f,1.0f)), pos_m = dvec3(info[1].model->getTranslate()*vec4(0.0f,0.0f,0.0f,1.0f));
	dvec3 u21 = pos_e - pos_m; // m -> E
	double range = length(u21)/KM_MOON*std::pow(10.0,3.0);
	u21 = normalize(u21);
	double d2 = range*range;
	dvec3 f12 = GRAVITY_ACCELERATION/d2*info[0].mass*info[1].mass*u21;
	dvec3 f21 = -GRAVITY_ACCELERATION/d2*info[0].mass*info[1].mass*u21;

	dvec3 aE = 1.0*f21/info[0].mass;
	dvec3 aM = 1.0*f12/info[1].mass;

	dvec3 vE = aE*(double)time + info[0].velocity;
	dvec3 vM = aM*(double)time + info[1].velocity;

	dvec3 pE = aE*(double)time*(double)time/2.0  + info[0].velocity*(double)time + pos_e/(double)KM_MOON*std::pow(10.0,3.0);
	dvec3 pM = aM*(double)time*(double)time/2.0  + info[1].velocity*(double)time + pos_m/(double)KM_MOON*std::pow(10.0,3.0);

	info[0].velocity = vE;
	info[1].velocity = vM;

	info[0].model->MoveTo(vec3(pE*(double)KM_MOON*std::pow(10.0,-3.0)));
	info[1].model->MoveTo(vec3(pM*(double)KM_MOON*std::pow(10.0,-3.0)));

}

void App::OnUpdate(uint64 time_diff)
{
	m_MatView3D = camera.look();
	m_MatNormal = mat3(m_MatView3D);
	m_modelVector[0]->Rotate(time_diff/1000.0f,vec3(0,0,1));
	/*for(int i = 0; i < 16; i++) 
		update_POS(planete_array,(double)time_diff);*/
}

void App::OnRender()
{
	// 3D RENDER BEGIN
	Renderer::Get().LoadMatrix(MAT_VIEW, m_MatView3D);
	Renderer::Get().LoadMatrix(MAT_PROJECTION, m_MatProj3D);
	//Renderer::Get().LoadMatrix(MAT_NORMAL, m_MatNormal);


	if(moon_h.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE5,true);
		Renderer::Get().SetTexture(5, moon_h.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE5,false);

	if(moon_n.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE4,true);
		Renderer::Get().SetTexture(4, moon_n.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE4,false);

	m_modelVector[1]->Render();

	if(earth_h.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE5,true);
		Renderer::Get().SetTexture(5, earth_h.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE5,false);

	if(earth_n.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE4,true);
		Renderer::Get().SetTexture(4, earth_n.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE4,false);

	m_modelVector[0]->Render();
	/*for(uint32 i = 0; i < m_modelVector.size(); i++)
		m_modelVector[i]->Render();*/

	// 3D RENDER END

	// POST EFFECT 3D BEGIN

	// POST EFFECT 3D END

	//	 DEBUG SHOW NORMAL WITH GEOMETRY SHADER

	/*Renderer::Get().SetCurrentProgram(tang);

	Renderer::Get().LoadMatrix(MAT_VIEW, m_MatView3D);
	Renderer::Get().LoadMatrix(MAT_PROJECTION, m_MatProj3D);

	if(tex.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE5,true);
		Renderer::Get().SetTexture(5, tex.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE5,false);

	if(tex_n.GetTexture())
	{
		Renderer::Get().Enable(RENDER_TEXTURE4,true);
		Renderer::Get().SetTexture(4, tex_n.GetTexture());
	}else Renderer::Get().Enable(RENDER_TEXTURE4,false);

	for(uint32 i = 0; i < m_modelVector.size(); i++)
		m_modelVector[i]->Render();

	Renderer::Get().SetCurrentProgram(NULL);*/

	// 2D RENDER BEGIN

	Renderer::Get().SetCurrentProgram(shader2D);

	Renderer::Get().LoadMatrix(MAT_VIEW, m_MatView2D);
	Renderer::Get().LoadMatrix(MAT_PROJECTION, m_MatProj2D);

	m_fps->Text = StringBuilder("fps : ")(getFps());
	m_fps->Draw();

	Renderer::Get().SetCurrentProgram(NULL);

	// 2D RENDER END




	

}


LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

Model* App::CreateSphere(float r,float stack, float slice,float angle, std::string texture)
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
			vertex.color = -1;
			vertex.normal = vec3(cos(i*angle/stack)*sin(j*M_PI/slice),sin(i*angle/stack)*sin(j*M_PI/slice), cos(j*M_PI/slice));
			vertex.position = vec3(r*cos(i*angle/stack)*sin(j*M_PI/slice),r*sin(i*angle/stack)*sin(j*M_PI/slice), r*cos(j*M_PI/slice));
			vertex.texCoords = vec2(i/stack,j/slice);
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

			index.push_back(i*((int)slice+1)+j);
			index.push_back(_i*((int)slice+1)+j);
			index.push_back(_i*((int)slice+1)+_j);

			index.push_back(i*((int)slice+1)+j);
			index.push_back(_i*((int)slice+1)+_j);
			index.push_back(i*((int)slice+1)+_j);
		}
	}


	return new Model(&vertices[0],vertices.size(),&index[0],index.size(), texture);
}
