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
	
	Terrain* ground = new Terrain(ivec2(100,100),ivec2(100,100),"","");
	tex.CreateFromFile("Texture/heightmap_1.png",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,5);
	tex.CreateFromFile("Texture/heightmap_1_Normal.png",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,4);
	tex.CreateFromFile("Texture/herbe.32932.png",PXF_A8R8G8B8);
	ground->SetTextureUnit(tex,0);
	ground->MoveTo(0.0f,0.0f,-3.0f);
	Water* water = new Water(ivec2(100,100),ivec2(100,100));
	m_Scene->AddTerrain(ground);
	
	m_Scene->AddWater(water);
	water->SetScene(m_Scene);

	m_light_dir = vec3(1.0f,0.0,0.0f);
	m_light_angle = 0.0f;

	/**/

	fbo[0] = Renderer::Get().CreateFrameBuffer();
	fbo[1] = Renderer::Get().CreateFrameBuffer();
	ivec2 size = Renderer::Get().GetScreen();
	m_RefractionMap = Renderer::Get().CreateTexture(size,PXF_A8R8G8B8);
	m_ReflectionMap = Renderer::Get().CreateTexture(size,PXF_A8R8G8B8);
	fbo[0]->setTexture(m_RefractionMap,COLOR_ATTACHMENT);
	fbo[1]->setTexture(m_ReflectionMap,COLOR_ATTACHMENT);


	AWidget* testwindow = new AWindow(m_RefractionMap);
	testwindow->SetSize(200,200);
	testwindow->SetPosition(200,150);

	

	GUIMgr::Instance().AddWidget(testwindow);


	testwindow = new AWindow(m_ReflectionMap);
	testwindow->SetSize(200,200);
	testwindow->SetPosition(200,150);

	GUIMgr::Instance().AddWidget(testwindow);
}

#define MODULO_FLOAT(a,x) ((a)-(x)*(int)((a)/(x)))

void App::OnUpdate(uint64 time_diff/*in ms*/)
{
	m_MatView3D = camera.look();
	m_MatNormal = mat3(m_MatView3D);

	m_light_angle += M_PI*2*(time_diff/60000.0f);
	m_light_angle = MODULO_FLOAT(m_light_angle,M_PI);
	m_light_dir = vec3(cos(m_light_angle),0.0,sin(m_light_angle));
}

void App::OnRender()
{
	// 3D RENDER BEGIN

	Renderer::Get().SetMatView(m_MatView3D);
	Renderer::Get().SetMatProjection(m_MatProj3D);
	Renderer::Get().getPipeline()->SetParameter("light",m_light_dir);
	m_Scene->Draw(SC_DRAW_ALL);

	// 3D RENDER END

	// POST EFFECT 3D BEGIN

	// POST EFFECT 3D END

	// 2D RENDER BEGIN

	Renderer::Get().SetCurrentProgram(shader2D);

	Renderer::Get().SetMatView(m_MatView2D);
	Renderer::Get().SetMatProjection(m_MatProj2D);

	m_fps->Text = StringBuilder("fps : ")(getFps());
	m_fps->Draw();
	m_text->Draw();

	Renderer::Get().SetCurrentProgram(NULL);

//	GUIMgr::Instance().DrawGUI();
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
	Model* m = new Model(&vertices[0],vertices.size(),&index[0],index.size());
	Texture tex;
	if(texture.length() != 0)
		tex.CreateFromFile(texture,PXF_A8R8G8B8);
	if(tex.GetTexture())
		m->SetTextureUnit(tex,0);

	return m;
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










