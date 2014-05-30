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
#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Core/Shader/ShaderPreCompiler.h>
#include <Core/RenderingMode/DeferredRendering.h>
#include <Core/SceneObject/SceneMgr.h>
#include <Core/SceneObject/Model.h>
#include <Core/SceneNode/MeshNode.h>
#include <Core/SceneObject/Light.h>
#include <Core/SceneObject/Material.h>
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
SceneMgr* scene;
void App::OnInit()
{  
	pause = true;
	printf("Loading...");
	m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
	m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);
	pause = false;
	m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
	Driver::Get().SetCullFace(2);
	DeferredRendering* _renderer = new DeferredRendering(getScreen());
	RenderingMode::SetRenderingMode(_renderer);
	/*
	Bezier
	*/
	scene = new SceneMgr();
	scene->AddLight(new Light(vec3(0,0,0),vec3(0,0,-1),LIGHT_DIR));
	Driver::Get().SetActiveScene(scene);
	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(),10.f);
	cam2D = new FPCamera(m_MatProj2D);

	m_plane = new DrawablePlane(getScreen(),vec2(100,100));
	vec2 points[] = {vec2(-150,-50), vec2(-50,50), vec2(50,-50),vec2(50,50),vec2(50,50),vec2(50,50),vec2(50,50)};
	BaseSpline* spline = new BaseSpline(points,3);
	Bezier* bezier = new Bezier(points,7);
	BSpline* bspline = new BSpline(points,7,3);
	LineRenderer* renderer = new LineRenderer(bspline);
	m_plane->addSpline(renderer);
	addInputListener(m_plane);
	ASlider* slider = new ASlider(NULL);
	slider->setLabel(std::string("degree"));
	GUIMgr::Instance().AddWidget(slider);
	slider->SetPosition(1300,800);
	slider->SetSize(200,20);
	slider->setValue(&m_plane->degree,1,5);

	Camera::SetCurrent(cam3D, CAMERA_3D);
	Camera::SetCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
}
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{

}

void App::OnRender3D()
{
	if(pause)
		m_plane->render();
	Texture::TextureRender(m_plane->getTexture());
}

void App::OnRender2D()
{
	Driver& render = Driver::Get();
	*(m_fps) = StringBuilder(render.GetStatistics().ToString())("\n")("Spline degree : ")(floor(m_plane->degree));
	m_fps->Draw();

}

void _CreatePlane(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index);

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message == WM_KEYDOWN)
	{
		char c = LOWORD(wParam);
		std::vector<LineRenderer*> render = m_plane->getRender();
		std::vector<Model::TVertex> vertices;
		std::vector<Model::TIndex> index;
		Texture tex;
		Model* m;
		MeshNode* p;
		switch(c)
		{
		case 'I':
			if(render.size() < 2)
				break;
			_CreatePlane(render[0]->getSpline(),render[1]->getSpline(),vertices,index);
			m= new Model(&vertices[0],vertices.size(),&index[0],index.size());
			//tex.CreateFromFile("Texture/debug.png",PXF_A8R8G8B8);

			p = new MeshNode(m);
			//p->GetMaterial().SetTexture(tex,0,(TRenderPass)((1<<RENDERPASS_DEFERRED)));
			p->GetTransform().Scale(0.1f,0.1f,0.1f);
			scene->AddNode(p);

			//m->Generate(G_NORMAL,);
			break;
		case 'P':
			pause = !pause;
			break;
		case 'X':
			scene->clear();
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

void _CreatePlane(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
{



	float x_2 = 1;
	float y_2 = 1;
	vec3 o = -vec3(0.5f,0.5f,0);
	std::vector<vec2> _p1 = p1->getComputedPoints();
	std::vector<vec2> _p2 = p2->getComputedPoints();
	//vec3 ori(_p1[0].x,_p2[0].x,_p1[0].y+_p2[0].y);
	vec3 ori;//(_p1[0].x,_p1[0].y+_p2[0].x,_p2[0].y);
	vec3 k = vec3(0,0,1);
	vec3 normal = vec3(0);
	vec2 last = vec2(0);
	vec2 _T = normalize(_p2[1]-_p2[0]);
	for(int i = 0; i < _p1.size(); i++)
	{
		for(int j = 0; j < _p2.size(); j++)
		{



			if(i == 0)
				_T = normalize(_p2[1]-_p2[0]);
			else if(length(last))
				_T = normalize(_p2[j]-last);
			vec3 tb = vec3(_T.x,_T.y,0);
			vec3 p = cross(tb,vec3(0,0,1));

			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = vec3(0,0,1);
			vertex.position = vec3(_p2[j].x,_p2[j].y,0)+vec3(_p1[i].x*p.x,_p1[i].y*p.y,_p1[i].y)-ori;
			if(!length(ori))
			{
				ori  = vertex.position;
				vertex.position -= ori;
			}
			vertex.texCoords = vec2(i/(float)(_p1.size()-1),j/(float)(_p2.size()-1));
			vertices.push_back(vertex);

			last = _p2[j];
		}

	}
	/*for(int i = 0; i < _p1.size(); i++)
	{

	for(int j = 0; j < _p2.size(); j++)
	{
	Model::TVertex vertex;
	vertex.color = -1;
	vertex.normal = vec3(0,0,1);
	vertex.position = vec3(_p1[i].x,0,_p1[i].y)+vec3(0,_p2[j].x,_p2[j].y)-ori;
	vertex.texCoords = vec2(i/(float)(_p1.size()-1),j/(float)(_p2.size()-1));
	vertices.push_back(vertex);
	}
	}*/


	int count = _p2.size()-1;
	for(int i = 0; i < _p1.size()-1;i++)
	{
		for(int j = 0; j < _p2.size()-1; j++)
		{
			int _i = SELECT(i+1, _p1.size()), _j = SELECT(j+1, _p2.size());
			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);

			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);
			index.push_back(i*(count+1)+_j);
		}
	}
}
