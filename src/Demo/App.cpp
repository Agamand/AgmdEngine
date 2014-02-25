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
#include <Agmd3D/Core/Camera/TPCamera.h>
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
#include <Renderer/OpenGL/GlRenderer.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "Loader/objLoader.h"
#include <Demo/Loader/MeshLoader.h>
#include <glm/ext.hpp>
#include "PerlinNoise.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Core/Shader/ShaderPreCompiler.h>


using namespace Agmd;
using namespace AgmdNetwork;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

BaseShaderProgram* default_program;

void generateNoise(uint32*& img,int size,int seed)
{
	img = new uint32[size*size];
	PerlinNoise p(1,0.1,1,6,seed);
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)	
		{
			int c =  (int)(255*p.GetHeight((double)i*0.01,(double)j*0.01));//(0.5+glm::noise1(0.5f)+(1+glm::noise1(1.f))/2+(2+glm::noise1(2.f))/4)/3*255;
			unsigned char* color = (unsigned char*)(&img[i*size+j]); 
			color[0] =  c; color[1] = c; color[2] =c;
			color[3] = 255;
			//img[i] = c+((c)<<8)+((c)<<16)+((255)<<24);
	}
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
    AgmdApp::Run();
}

void App::OnInit()
{
    fxaa = true;
    default_program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/default_shader.glsl");
    ShaderPipeline* test =  MediaManager::Instance().LoadMediaFromFile<ShaderPipeline>("Shader/BuiltinShader/BumpMap.shader");
    
    pause = true;
    count = 1;
    noise = 0.005;
    bias = -0.005f;
    m_timer = 1000;
    MediaManager::Instance().RegisterLoader(new M2Loader(),"m2");
	MediaManager::Instance().RegisterLoader(new MeshLoader(),"mesh");
    m_MatProj3D = glm::perspective(60.0f, (float)getScreen().x / (float)getScreen().y, 0.1f, 10000.f);
    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);

    shader2D = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/classic_pipeline_2D.glsl");
	default_program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/noise_test.glsl");
    //ForwardRendering* mode = new ForwardRendering(getScreen());
    DeferredRendering* mode = new DeferredRendering(getScreen());
    drend = mode;
    //RenderingMode::SetRenderingMode(mode);
	string file = "/RenderingShader/DeferredDirLightShader.glsl";
	string shader = ShaderPreCompiler::Instance().LoadAndCompileShader(file,NULL);

	g = 1;
	l = 0.1;
	o = 6;
	seed = clock();

    m_motioneffect = NULL;
    m_effect = NULL;

    m_motioneffect = new BlurMotionEffect(getScreen());
    //PostEffectMgr::Instance().AddEffect(m_motioneffect);
    asci = new AsciEffect();
    //PostEffectMgr::Instance().AddEffect(asci);
    m_effect = new BlurEffect(Texture());
    //PostEffectMgr::Instance().AddEffect(m_effect);
    m_fxaa = new AntiAliasing();
    PostEffectMgr::Instance().AddEffect(m_fxaa);
    cam3D = new TPCamera(m_MatProj3D);
    cam2D = new FPCamera(m_MatProj2D);
    Camera::SetCurrent(cam3D);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);

    m_Scene = new SceneOld();
    /*nodes.push_back(vec3(50.0f,0.0f,10.0f));
    nodes.push_back(vec3(100.0f,0.0f,10.0f));
    nodes.push_back(vec3(100.0f,100.0f,10.0f));
    nodes.push_back(vec3(0.0f,100.0f,10.0f));
    nodes.push_back(vec3(0.0f,0.0f,10.0f));
    nodes.push_back(vec3(50.0f,0.0f,10.0f));*/

    //m_Scene->AddMesh(r);
	
    Model* model = /*CreatePlane(ivec2(5),ivec2(1),"",TPrimitiveType::PT_TRIANGLELIST);*/CreateMetaSphere(1.0f,0,0);//CreateSphere(1.0f,20,20,2*M_PI,"",TPrimitiveType::PT_TRIANGLELIST);//CreateBox(vec3(1),"",PT_TRIANGLELIST);
    MeshRender* mesh = new MeshRender(model);
	Texture tex;
	uint32 *img;
/*	generateNoise(img,1024,(uint32)8716);
	tex.CreateFromImage(Agmd::Image(ivec2(1024),PXF_A8R8G8B8,(const unsigned char*)img),PXF_A8R8G8B8);
	delete[] img;	
	tex.CreateFromFile("/Texture/heightmap.png",PXF_A8R8G8B8);
	Material* m = new Material(ShaderPipeline::GetDefaultPipeline());
	m->SetTexture(tex,0,TRenderPass::RENDERPASS_DEFERRED);
	mesh->SetMaterial(m);*/
	//mesh->SetTexture(tex,0,TRenderPass::RENDERPASS_DIFFUSE);
    plane = mesh;
    mesh->GetTransform().Translate(0,0,0);
    m_Scene->AddMesh(mesh);
    sphere = mesh;
    model = CreatePlane(ivec2(20000),ivec2(1),"",PT_TRIANGLELIST);
    //m_Scene->AddMesh(new MeshRender(model));
		
    MeshRender* me = new MeshRender(model);
    me->GetTransform().Translate(1000,0,0);
    me->GetTransform().Rotate(-90,vec3(0,1,0));
//    m_Scene->AddMesh(me);


    AWindow* diffuseW = new AWindow();
    diffuseW->SetBackground(mode->GetDiffuseTexture());
    AWindow* depthW = new AWindow();
    depthW->SetBackground(mode->GetDepthTexture());//GetShadowRenderer()->GetShadowDepth());
    AWindow* lightW = new AWindow();
    lightW->SetBackground(mode->GetNormalTexture());
    AWindow* posW =  new AWindow();
    posW->SetBackground(mode->GetPositionTexture());
    GUIMgr::Instance().AddWidget(diffuseW);
    GUIMgr::Instance().AddWidget(depthW);
    GUIMgr::Instance().AddWidget(lightW);   
    GUIMgr::Instance().AddWidget(posW);
    Renderer::Get().SetActiveScene(m_Scene);
    Renderer::Get().SetCullFace(2);

    m_light = new Light(vec3(0, 0 ,10),-normalize(vec3(0,0.2,-1)),LightType::LIGHT_SPOT);//new Light(vec3(0,0,10),-normalize(vec3(0,0.5,-1)),LIGHT_SPOT);
    m_Scene->AddLight(m_light);
    m_timer = 10000;

    m_light->SetRange(2000.0f);

    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
}

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
    if(pause)
        return;
    m_Scene->Update(time_diff);
    asci->Update(time_diff);/*
    if(m_timer <= time_diff)
    { 
        m_timer = 1000;
    }else m_timer -= time_diff;*/
	m_timer++;
    vec3 position = vec3(2*cos(m_timer/500.0f*M_PI),2*sin(m_timer/500.0f*M_PI),2.0f);
	m_light->SetDirection(-normalize(vec3(2*cos(m_timer/500.0f*M_PI),2*sin(m_timer/500.0f*M_PI),-1)));
    //plane->GetTransform().SetPosition(position);
    //plane->GetTransform().SetRotation(quat(90.0f,vec3(1,0,0))*quat(-90.0f+180*m_timer/5000.0f,vec3(0,1,0)));
    sphere->GetTransform().SetPosition(position);
    //m_light->SetDirection(normalize(position));
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
    Renderer::Get().SetCurrentProgram(default_program);
    Renderer::Get().SetCurrentTransform(NULL);
    default_program->SetParameter("u_time",(float)m_timer/1000);
	default_program->SetParameter("u_g",g);
	default_program->SetParameter("u_l",l);
	default_program->SetParameter("u_g",o);
	default_program->SetParameter("u_l",(int)(seed+m_timer));
    Fast2DSurface::Instance().Draw();


}

void App::OnRender2D()
{
    Renderer& render = Renderer::Get();

    // 2D RENDER BEGIN
    //Texture::TextureRender(tex);

    //render.SetCurrentProgram(shader2D);
    //int fps = getFps();
    //m_fps->m_Text = StringBuilder(fps)(", ")(fps ? (int)(1000/fps) : 999999999)(" ms ")(cam3D->GetPosition().x)(" ")(cam3D->GetPosition().y)(" ")(cam3D->GetPosition().z)(" shadow offset : ")(noise);//(" fps,")(fps ? (int)(1000/(float)fps) : 999999999)(" ms");
    *(m_fps) = StringBuilder(render.GetStatistics().ToString())("\n bias : ")(bias)("\nTimer : ")(m_timer)("\nSample Count : ")(count)("\nnoise\n persistence : ")(g)("\n frequency : ")(l)
	("\n octave : ")(o)("\n seed : ")(seed+m_timer);
    m_fps->Draw();
    /*m_text->Text = StringBuilder("Mouse coord (x : ")(last_mouse_pos.x)(", y :")(last_mouse_pos.y)(")");
    m_text->Draw();*/
    //render.SetCurrentProgram(NULL);



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
        case VK_ADD:
            noise += 0.1f;
            if(m_motioneffect)
                m_motioneffect->SetIntensity(noise);
            if(m_effect)
                m_effect->SetNoiseOffset(noise);
            drend->GetShadowRenderer()->SetOffset(noise);
            break;
        case VK_SUBTRACT:
            noise -= 0.1f;
            if(m_motioneffect)
                m_motioneffect->SetIntensity(noise);
            if(m_effect)
                m_effect->SetNoiseOffset(noise);
            drend->GetShadowRenderer()->SetOffset(noise);
            break;
        case 'O':
            m_light->SetDirection(-normalize(cam3D->GetTarget() - cam3D->GetPosition()));
            break;

        case VK_NUMPAD8:
            sphere->GetTransform().Translate(0,0,0.1f);
            break;
        case VK_NUMPAD2:
            sphere->GetTransform().Translate(0,0,-0.1f);
            break;
        case VK_NUMPAD6:
            sphere->GetTransform().Translate(-0.1f,0,0);
            break;
        case VK_NUMPAD4:
            sphere->GetTransform().Translate(0.1f,0,0);
            break;
        case VK_NUMPAD7:
            sphere->GetTransform().Translate(0,-0.1f,0);
            break;
        case VK_NUMPAD9:
            sphere->GetTransform().Translate(0,0.1f,0);
            break;
        case VK_MULTIPLY:
            bias += 0.001f; 
            drend->GetShadowRenderer()->SetBias(bias);
            break;
        case VK_DIVIDE:
            bias -= 0.001f; 
            drend->GetShadowRenderer()->SetBias(bias);
            break;
        case 'K':
            m_fxaa->SetEnable(fxaa = !fxaa);
            break;
        case 'L':
            m_fxaa->SetItrCount(++count);
            break;
        case 'M':
            m_fxaa->SetItrCount(--count);
            break;
		case 'T':
			g+=0.1;
			break;
		case 'G':
			g-=0.1;
			break;
		case 'Y':
			l+=0.1;
			break;
		case 'H':
			l-=0.1;
			break;
		case 'R':
			o+=1;
			break;
		case 'F':
			o-=1;
			break;
		case 'E':
			seed = clock();
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