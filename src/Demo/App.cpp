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
#include <Agmd3D\Core\Renderer.h>
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
#include <Agmd3D/Core/Shader/ShaderPipeline.h>
#include <Agmd3D/Core/Tools/Statistics.h>
#include <Agmd3D/Core/SceneObject/Material.h>
#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Renderer/OpenGL/GlRenderer.h>
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
	_perlin.SetFrequency(1.f);
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
	a_uint32* img = new uint32[size*size];
	//PerlinNoise p(1,0.1,1,6,seed);
	noise::module::Perlin _perlin;
	_perlin.SetOctaveCount(8.f);
	_perlin.SetFrequency(2.f);
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
	Image _img[6];
	//Image __img[6];
	_img[0].LoadFromFile(StringBuilder("Texture/debug.png"));
	for(int i = 0; i< 6; i++)
	{
		_img[i] = Image(ivec2(size),PXF_A8R8G8B8,(uint8*)img);
	}
	delete img;

	t.CreateFromImage(_img,PXF_A8R8G8B8);
//	t.Create(ivec2(1),PXF_A8R8G8B8,TEXTURE_CUBE);
}
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

#include "Planet/Planet.h"

void App::OnInit()
{  
    pause = true;
    m_timer = 1000;
	
	m_MatProj3D = glm::perspective(60.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);

    DeferredRendering* mode = new DeferredRendering(getScreen());
    RenderingMode::SetRenderingMode(mode);
    m_fxaa = new AntiAliasing();
    //PostEffectMgr::Instance().AddEffect(m_fxaa);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);
    m_Scene = new SceneMgr();
	Texture t;
	generateNoise3d(t,1024,rand());

	Material* mat = new Material();
	mat->SetTexture(t,0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)));
	//mat->SetTexture(t,0,RENDERPASS_ZBUFFER);
	Planet* p = new Planet(mat);
    Model* model = CreateMetaSphere(1.0f,0,0);
    MeshNode* mesh = new MeshNode(CreateSphere(1.f,20,20,2*M_PI,"",PT_TRIANGLELIST));
    m_Scene->AddNode(p->GetRoot());
	//uint32 *i = new uint32(256*256);

    //m_Scene->AddNode(mesh);
	model = CreatePlane(ivec2(20000),ivec2(1),"",PT_TRIANGLELIST);
    Renderer::Get().SetActiveScene(m_Scene);
    Renderer::Get().SetCullFace(2);

    m_light = new Light(vec3(0, 0 ,10),-normalize(vec3(0,0.2,-1)),LightType::LIGHT_DIR);//new Light(vec3(0,0,10),-normalize(vec3(0,0.5,-1)),LIGHT_SPOT);
    m_Scene->AddLight(m_light);
    m_light->SetRange(2000.0f);

	cam3D = new FollowCamera(m_MatProj3D);
	cam2D = new FPCamera(m_MatProj2D);
    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
}

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
    if(pause)
        return;
}
static const GLfloat vertices[] = 
{
	-0.8f, -0.8f, 0.0f,	// vertex bas-gauche
	0.8f, -0.8f, 0.0f,	// vertex bas-droit
	0.0f, 0.8f, 0.0f	// vertex haut
};
void App::OnRender3D()
{
    GLRenderer* renderer = reinterpret_cast<GLRenderer*>(&Renderer::Get());
    /*Renderer::Get().SetCullFace(0);
    default_program->Use(true);
    GLRenderer::glBindBuffer(gl_verte
    GLRenderer::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    GLRenderer::glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
    default_program->Use(false);*/
    //GLRenderer::glDisableVertexAttribArray(0);
 //   Renderer::Get().SetCurrentProgram(default_program);
 //   Renderer::Get().SetCurrentTransform(NULL);
 //   default_program->SetParameter("u_time",(float)m_timer/1000);
	//default_program->SetParameter("u_g",g);
	//default_program->SetParameter("u_l",l);
	//default_program->SetParameter("u_g",o);
	//default_program->SetParameter("u_l",(int)(seed+m_timer));
 //   Fast2DSurface::Instance().Draw();


}

void App::OnRender2D()
{
    Renderer& render = Renderer::Get();
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\nTimer : ")(m_timer);
    m_fps->Draw();
}

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_KEYDOWN)
    {
        switch(LOWORD(wParam))
        {
        case 'P':
            pause = !pause;
            break;
        case 'O':
            m_light->SetDirection(-normalize(cam3D->GetTarget() - cam3D->GetPosition()));
            break;
		}
    }

    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
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