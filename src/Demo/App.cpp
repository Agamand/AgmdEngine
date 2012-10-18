#include "App.h"
#include "M2Model.h"
#include "M2Loader.h"
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Renderer.h>
#include <Agmd3D\Core\Enums.h>
#include <Agmd3D\Core\Declaration.h>
#include <Agmd3D\Core\DeclarationElement.h>
#include <Agmd3D\Core\ResourceManager.h>
#include <Agmd3D\Core\Terrain.h>
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D\Core\GraphicString.h>
#include <Agmd3D\Core\Scene.h>
#include <Agmd3D\Core\Water.h>
#include <Agmd3D\Core\SkyBox.h>
#include <Agmd3D\Core\GUI\GUIMgr.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <AgmdNetwork\Client\Client.h>
#include <AgmdNetwork\Opcode\OpcodeMgr.h>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace Agmd;
using namespace AgmdNetwork;

SINGLETON_IMPL(App)

#define EARTH_MOON_R 3.661786780f
#define KM_MOON 0.0005760f


enum Opcode
{
	MSG_NULL_ACTION = 0x0,
	CMSG_SEND_MESSAGE = 0x1,
	SMSG_SEND_MESSAGE = 0x2
};

class OpClientMgr : public AgmdNetwork::OpcodeMgr<OpClientMgr>
{

public:
	friend class App;
	void BuildMessagePacket(std::string message, AgmdNetwork::Packet& packet)
	{
		packet.SetOpcode(SMSG_SEND_MESSAGE);
		packet << message;
	}
	
	void HandleMessage(AgmdNetwork::Packet& packet);


	void Handle_NULL(AgmdNetwork::Packet& packet) {}
};

AgmdNetwork::OpcodeHandler<OpClientMgr> _opcode[] = 
{
	{"MSG_NULL_ACTION",&OpClientMgr::Handle_NULL},
	{"CMSG_SEND_MESSAGE",&OpClientMgr::Handle_NULL},
	{"SMSG_SEND_MESSAGE",&OpClientMgr::HandleMessage},
};

class AgmdClient : public AgmdNetwork::Client
{
public:

	AgmdClient(std::string ip, uint32 port) :
	Client(ip,port)
	{}

	virtual void RecvPacket(AgmdNetwork::Packet& packet);

};

void App::Run(int argc, char** argv)
{
	if(argc > 0)
		MediaManager::Instance().AddSearchPath(File(argv[0]).Path());

	AgmdApp::Run();
}

void App::OnInit()
{
	MediaManager::Instance().RegisterLoader(new M2Loader(),"m2");

	//camera.setTarget(vec3(150.82265,167.96919,19.525068));
	//camera.setPosition(178.62114,-178.86295,22.452559);
	

	m_MatProj3D = glm::perspectiveFov(60.0f, (float)getScreen().x, (float)getScreen().y, 0.1f, 10000.0f);
	m_MatView3D = camera.look();

	m_MatView2D = mat4(1.0f); // m4 identity
	m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);

	shader2D = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/classic_pipeline_2D.glsl");

	m_fps = new GraphicString(ivec2(200,200),"",Color::black);
	m_text = new GraphicString(ivec2(200,250),"",Color::black);

	AgmdClient* cl = new AgmdClient("192.168.0.5",4015);
	cl->Init();
	cl->Start();

	OpClientMgr::Instance().SetReader(_opcode);



	m_Scene = new Scene();
	Texture tex;
	
	Terrain* ground = new Terrain(ivec2(200,100),ivec2(200,100),"","");
	tex.CreateFromFile("Texture/gc_h.tga",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,5);
	tex.CreateFromFile("Texture/gc_n.tga",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,4);
	tex.CreateFromFile("Texture/gc_d.tga",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,0);
	ground->MoveTo(0.0f,0.0,-3.0f);
	m_Scene->AddTerrain(ground);

	SkyBox* sky = new SkyBox(200);
	tex.CreateFromFile("Texture/water_pos_y.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,0);
	tex.CreateFromFile("Texture/water_neg_y.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,1);
	tex.CreateFromFile("Texture/water_neg_x.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,2);
	tex.CreateFromFile("Texture/water_pos_z.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,3);
	tex.CreateFromFile("Texture/water_pos_x.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,4);
	tex.CreateFromFile("Texture/water_neg_z.tga",PXF_A8R8G8B8);
	sky->SetTexture(tex,5);
	m_Scene->SetSky(sky);

	Water* water = new Water(ivec2(200,100),ivec2(200,100));
	m_Scene->AddWater(water);
	water->SetScene(m_Scene);

	m_light_dir = vec3(1.0f,0.0,0.0f);
	m_light_angle = 0.0f;
	m_tesslationInner = 1;
	m_tesslationOuter = 1;
	height = 0.0f;

	/**/

	fbo[0] = Renderer::Get().CreateFrameBuffer();
	fbo[1] = Renderer::Get().CreateFrameBuffer();
	ivec2 size = Renderer::Get().GetScreen();
	buffer[0] = Renderer::Get().CreateTexture(size,PXF_A8R8G8B8, TEXTURE_2D);
	buffer[1] = Renderer::Get().CreateTexture(size,PXF_A8R8G8B8, TEXTURE_2D);


	use_buffer = buffer[1];
	use_fbo = fbo[1];


	testwindow = new AWindow();
	testwindow->SetSize(200,200);
	testwindow->SetPosition(200,150);

	GUIMgr::Instance().AddWidget(testwindow);

	sphere[0] = CreatePlane(ivec2(200,100),ivec2(200,100),"",PT_PATCHLIST);//CreateSphere(1.0f,6.0f,6.0f,2*M_PI,"", PT_PATCHLIST);
	sphere[1] = CreatePlane(ivec2(10),ivec2(10),"",PT_TRIANGLELIST);//CreateSphere(1.0f,6.0f,6.0f,2*M_PI,"", PT_TRIANGLELIST);
	sphere[0]->Move(0.0,52.0f,0.0f);
	Texture t;
	t.CreateFromFile("Texture/heightmap2.png",PXF_A8R8G8B8);
	sphere[0]->SetTextureUnit(t,0);

	
	t.CreateFromFile("Texture/heightmap2.png",PXF_A8R8G8B8);

	sphere[0]->SetTextureUnit(t,5);
	//sphere[1]->SetTextureUnit(t,5);
	//sphere[1]->Move(1.0f,0.0f,0.0f);


	//tesselation_shader = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/terrain_with_tessellation.glsl");
	//simple_shader = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/simple.glsl");



}

#define MODULO_FLOAT(a,x) ((a)-(x)*(int)((a)/(x)))

void App::OnUpdate(uint64 time_diff/*in ms*/)
{
	m_MatView3D = camera.look();
	m_MatNormal = mat3(m_MatView3D);

	m_light_angle += M_PI*2*(time_diff/60000.0f);
	m_light_angle = MODULO_FLOAT(m_light_angle,M_PI);
	m_light_dir = vec3(cos(m_light_angle),0.0,sin(m_light_angle));
	m_Scene->Update(time_diff);
}

void App::OnRender()
{
	// 3D RENDER BEGIN

	Renderer::Get().SetMatView(m_MatView3D);
	Renderer::Get().SetMatProjection(m_MatProj3D);
	Renderer::Get().getPipeline()->SetParameter("light",m_light_dir);
	Renderer::Get().getPipeline()->SetParameter("du",height);
	
	m_Scene->Draw(SC_DRAW_ALL);

	/*Renderer::Get().SetCurrentProgram(tesselation_shader);
	tesselation_shader->SetParameter("TessLevelInner",m_tesslationInner);
	tesselation_shader->SetParameter("TessLevelOuter",m_tesslationInner);
	tesselation_shader->SetParameter("du",height);
	
	sphere[0]->Render();

	Renderer::Get().SetCurrentProgram(NULL);*/

	//Renderer::Get().SetCurrentProgram(simple_shader);
	//sphere[1]->Render();

	//Renderer::Get().SetCurrentProgram(NULL);


	// 3D RENDER END

	// POST EFFECT 3D BEGIN

	// POST EFFECT 3D END

	// 2D RENDER BEGIN

	Renderer::Get().SetCurrentProgram(shader2D);

	Renderer::Get().SetMatView(m_MatView2D);
	Renderer::Get().SetMatProjection(m_MatProj2D);

	m_fps->Text = StringBuilder("fps : ")(getFps());
	m_fps->Draw();

	Renderer::Get().SetCurrentProgram(NULL);
	
	//GUIMgr::Instance().DrawGUI();
	// 2D RENDER END





	

}


LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if(message == WM_KEYDOWN)
	{
		switch(LOWORD(wParam))
		{
		case VK_ADD:
			m_tesslationInner++;
			break;
		case VK_SUBTRACT:
			if(m_tesslationInner > 1)
				m_tesslationInner--;
			else m_tesslationInner = 1;
			break;
		case VK_MULTIPLY:
			m_tesslationOuter++;
			break;
		case VK_DIVIDE:
			if(m_tesslationOuter > 1)
				m_tesslationOuter--;
			else m_tesslationOuter = 1;
			break;
		case VK_NUMPAD8:
			height +=0.5f;
			break;
		case VK_NUMPAD2:
			height -=0.5f;
			break;
		}
	}

	return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

Model* App::CreateSphere(float r,float stack, float slice,float angle, std::string texture, TPrimitiveType type)
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
			vertex.boneCount = 0;
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
	Model* m = new Model(&vertices[0],vertices.size(),&index[0],index.size(),NULL,0,type);
	Texture tex;
	if(texture.length() != 0)
		tex.CreateFromFile(texture,PXF_A8R8G8B8);
	if(tex.GetTexture())
		m->SetTextureUnit(tex,0);

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
			vertex.boneCount = 0;
			vertices.push_back(vertex);
		}
	}

	uint32 npoly = n_poly.x*n_poly.y;


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

	Model* m = new Model(&vertices[0],vertices.size(),&index[0],index.size(),NULL,0,type);
	Texture tex;
	if(texture.length() != 0)
		tex.CreateFromFile(texture,PXF_A8R8G8B8);
	if(tex.GetTexture())
		m->SetTextureUnit(tex,0);

	return m;
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
		vertex.boneCount = 0;
		vertices.push_back(vertex);
		index.push_back(i);
	}


	return new Model(&vertices[0],vertices.size(),&index[0],index.size(),NULL,0,type);
}

void AgmdClient::RecvPacket(Packet& packet)
{
	OpClientMgr::Instance().RecvPacket(packet);
}

void OpClientMgr::HandleMessage(Packet& packet)
{
	std::string message = "";
	packet >> message;
	App::Instance().m_text->Text += message;
}










