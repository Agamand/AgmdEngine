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

ASlider * debugSlider;
float debug_value = 0;
float scalemin = 1;
float scalemax = 1;
float height = 1;
Model* m = NULL;
Material* surface_mat;
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
	surface_mat = new Material();
	
	Texture surface_texture;
	surface_texture.CreateFromFile("Texture/debug.png",PXF_A8R8G8B8);
	surface_mat->SetTexture(surface_texture,0, (TRenderPass)(1<<RENDERPASS_DEFERRED));
	/*
	Bezier
	*/
	scene = new SceneMgr();
	scene->AddLight(new Light(vec3(0,0,0),vec3(0,0,-1),LIGHT_DIR));
	Driver::Get().SetActiveScene(scene);
	cam3D = new FollowCamera(m_MatProj3D,0,0,vec2(),10.f);
	cam2D = new FPCamera(m_MatProj2D);
	float xy = getScreen().x/(float)getScreen().y;
	m_plane = new DrawablePlane(getScreen(),vec2(100*xy,100));
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
	debugSlider = new ASlider(NULL);
	debugSlider->setLabel(std::string("DEBUG"));
	debugSlider->setValue(&debug_value,0,10000);
	debugSlider->SetSize(200,20);
	debugSlider->SetPosition(1300,850);
	GUIMgr::Instance().AddWidget(debugSlider);

	slider = new ASlider(NULL);
	slider->setLabel(std::string("scale min"));
	GUIMgr::Instance().AddWidget(slider);
	slider->SetPosition(1300,750);
	slider->SetSize(200,20);
	slider->setValue(&scalemin,0,10);

	slider = new ASlider(NULL);
	slider->setLabel(std::string("scale max"));
	GUIMgr::Instance().AddWidget(slider);
	slider->SetPosition(1300,700);
	slider->SetSize(200,20);
	slider->setValue(&scalemax,0,10);
	slider = new ASlider(NULL);

	slider->setLabel(std::string("height"));
	GUIMgr::Instance().AddWidget(slider);
	slider->SetPosition(1300,650);
	slider->SetSize(200,20);
	slider->setValue(&height,0.1,1000);

	Camera::SetCurrent(cam3D, CAMERA_3D);
	Camera::SetCurrent(cam2D, CAMERA_2D);
	printf("Loading end");
}
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{

	if(m)
		m->setMaxDraw((int)debug_value*3);
}

void App::OnRender3D()
{
	if(pause)
		m_plane->render();
	Texture::TextureRender(m_plane->getTexture());
}

vec2 screenPos;
void App::OnRender2D()
{
	Driver& render = Driver::Get();
	*(m_fps) = StringBuilder(render.GetStatistics().ToString())("\n")("Spline degree : ")(floor(m_plane->degree))("\n Position : ")(screenPos.x)(" ")(screenPos.y);
	m_fps->Draw();

}

void _CreatePlane(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index);
void lathe(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,int splice);
void simpleExtrusion( BaseSpline* p1, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index, int slice, float scalemin, float scalemax,float height);
void generalizedExtrusion(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index);
void generalizedExtrusionOLD(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index);

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message == WM_KEYDOWN)
	{
		char c = LOWORD(wParam);
		std::vector<LineRenderer*> render = m_plane->getRender();
		std::vector<Model::TVertex> vertices;
		std::vector<Model::TIndex> index;
		std::vector<Model::TVertex> vertices2;
		std::vector<Model::TIndex> index2;
		Texture tex;
		Model* mo;
		MeshNode* p;
		switch(c)
		{
		case 'I':
			if(render.size() < 2)
				break;
			_CreatePlane(render[0]->getSpline(),render[1]->getSpline(),vertices,index);
			mo= new Model(&vertices[0],vertices.size(),&index[0],index.size());
			//tex.CreateFromFile("Texture/debug.png",PXF_A8R8G8B8);

			p = new MeshNode(mo);
			//p->GetMaterial().SetTexture(tex,0,(TRenderPass)((1<<RENDERPASS_DEFERRED)));
			p->GetTransform().Scale(0.1f,0.1f,0.1f);
			scene->AddNode(p);

			//m->Generate(G_NORMAL,);
			break;
		case 'P':
			pause = !pause;
			break;
		case 'a':
			if(render.size() < 2)
				break;
			lathe(render[0]->getSpline(),render[1]->getSpline(),vertices,index,60);
			mo= new Model(&vertices[0],vertices.size(),&index[0],index.size());
			p = new MeshNode(mo);
			p->setMaterial(surface_mat);
			p->GetTransform().Scale(0.1f,0.1f,0.1f);
			scene->AddNode(p);
			break;
		case 'b':
			if(render.size() < 1)
				break;
			simpleExtrusion(render[0]->getSpline(),vertices,index,60,scalemin,scalemax,height);
			mo= new Model(&vertices[0],vertices.size(),&index[0],index.size());
			p = new MeshNode(mo);
			p->setMaterial(surface_mat);
			p->GetTransform().Scale(0.1f,0.1f,0.1f);
			scene->AddNode(p);
			m = mo;
			break;
		case 'c':
			if(render.size() < 2)
				break;
			generalizedExtrusion(render[0]->getSpline(),render[1]->getSpline(),vertices,index);
			mo= new Model(&vertices[0],vertices.size(),&index[0],index.size());
			p = new MeshNode(mo);
			p->setMaterial(surface_mat);
			p->GetTransform().Scale(0.1f,0.1f,0.1f);
			scene->AddNode(p);
			m = mo;
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
	screenPos = m_plane->getPositionFromScreenSpace(pos);
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



void lathe(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,int splice)
{
	std::vector<vec2> _p1 = p1->getComputedPoints();
	std::vector<vec2> _p2 = p2->getComputedPoints();
	vec3 center = vec3(_p2[0],0),
		dir = vec3(_p2[1]-_p2[0],0);

	float offset = 1.f/splice;
	for(int i = 0; i <= splice; i++)
	{
		quat rot = rotate(quat(),360*i*offset,dir);
		for(int j = 0; j < _p1.size(); j++)
		{
			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = vec3(0,0,1);
			vertex.position = rot*(vec3(_p1[j],0)-center);

			vertex.texCoords = vec2(i/(float)(splice),j/(float)(_p2.size()-1));
			vertices.push_back(vertex);
		}
	}
	int count = _p1.size()-1;
	for(int i = 0; i < splice;i++)
	{
		for(int j = 0; j < _p1.size()-1; j++)
		{
			int _i = SELECT(i+1, splice+1), _j = SELECT(j+1, _p1.size());
			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);

			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);
			index.push_back(i*(count+1)+_j);
		}
	}
}


void simpleExtrusion( BaseSpline* p1, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index, int slice, float scalemin, float scalemax,float height)
{
	float x_2 = 1;
	float y_2 = 1;
	vec3 o = -vec3(0.5f,0.5f,0);
	std::vector<vec2> _p1 = p1->getComputedPoints();
	vec3 k = vec3(0,0,1);
	vec3 normal = vec3(0);
	bool p1close = p1->isClosed();
	int sizep1 = _p1.size() - (p1close ? 1 : 0);
	float offset = (scalemax-scalemin)/slice;
	float hoffset = (height)/slice;
	for(int i = 0; i <= slice; i++)
	{
		for(int j = 0; j < sizep1; j++)
		{
			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = vec3(0,0,1);
			vertex.position = vec3(_p1[j].x,0,_p1[j].y)*(scalemin+offset*i);
			vertex.position.y = i*hoffset;
			vertex.texCoords = vec2(j/(float)(_p1.size()-1),i/(float)(slice));
			vertices.push_back(vertex);
		}
	}

	int count = sizep1-1;
	for(int i = 0; i < slice; i++)
	{
		for(int j = 0; j<  (_p1.size()-1);j++)
		{
			int _i = SELECT(i+1, slice+1), _j = SELECT(j+1, sizep1);
			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);

			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);
			index.push_back(i*(count+1)+_j);
		}
	}

}

void generalizedExtrusion(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
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
	vec2 _T = normalize(_p2[1]-_p2[0]);
	bool p1close = p1->isClosed();
	bool p2close = p2->isClosed();
	int sizep1 = _p1.size() - (p1close ? 1 : 0),sizep2 = _p2.size()- (p2close ? 1 : 0);
	for(int i = 0; i < sizep2; i++)
	{
		if(i == 0 && !p2close)
			_T = normalize(_p2[1]-_p2[0]);
		else if(i == 0 && p2close)
			_T = normalize(_p2[0]-_p2[_p2.size()-2]);
		else
			_T = normalize(_p2[i]-_p2[i-1]);
		for(int j = 0; j < sizep1; j++)
		{
			
			vec3 tb = vec3(_T.x,_T.y,0);
			vec3 p = cross(tb,vec3(0,0,1));

			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = vec3(0,0,1);
			vertex.position = vec3(_p2[i].x,_p2[i].y,0)+vec3(_p1[j].x*p.x,_p1[j].x*p.y,_p1[j].y)-vec3(_p2[0].x,_p2[0].y,0);
			vertex.texCoords = vec2(j/(float)(_p1.size()-1),i/(float)(_p2.size()-1));
			vertices.push_back(vertex);

			
		}
	}

	int count = sizep1-1;
	for(int i = 0; i < (_p2.size()-1); i++)
	{
		for(int j = 0; j<  (_p1.size()-1);j++)
		{
			int _i = SELECT(i+1, sizep2), _j = SELECT(j+1, sizep1);
			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);

			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);
			index.push_back(i*(count+1)+_j);
		}
	}

}


void generalizedExtrusionOLD(BaseSpline* p1,BaseSpline* p2, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
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
	for(int i = 0; i < _p2.size(); i++)
	{
		if(i == 0)
			_T = normalize(_p2[1]-_p2[0]);
		else
			_T = normalize(_p2[i]-_p2[i-1]);
		for(int j = 0; j < _p1.size(); j++)
		{

			vec3 tb = vec3(_T.x,_T.y,0);
			vec3 p = cross(tb,vec3(0,0,1));

			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = vec3(0,0,1);
			vertex.position = vec3(_p2[i].x,_p2[i].y,0)+vec3(_p1[j].x*p.x,_p1[j].x*p.y,_p1[j].y)-vec3(_p2[0].x,_p2[0].y,0);
			vertex.texCoords = vec2(j/(float)(_p1.size()-1),i/(float)(_p2.size()-1));
			vertices.push_back(vertex);



		}
		last = _p2[i];
	}

	int count = _p1.size()-1;
	for(int i = 0; i < _p2.size()-1; i++)
	{
		for(int j = 0; j< _p1.size()-1;j++)
		{

			int _i = SELECT(i+1, _p2.size()), _j = SELECT(j+1, _p1.size());
			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);

			index.push_back(i*(count+1)+j);
			index.push_back(_i*(count+1)+_j);
			index.push_back(i*(count+1)+_j);
		}
	}

}

