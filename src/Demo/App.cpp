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
#include <Agmd3D/Core/RenderObject/MeshRender.h>
#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/Shader/ShaderPipeline.h>
#include <Agmd3D/Core/Tools/Statistics.h>
#include <Agmd3D/Core/SceneObject/Material.h>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace Agmd;
using namespace AgmdNetwork;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);


class PathNode
{
public:
    PathNode(vec3 pos) : position(pos)
    {}

    void AddNode(PathNode* node);
private:
    vec3 position;
    std::vector<PathNode*> connected_node;
};

class Road;
class Path
{
public:
        friend class Road;
        Path(std::vector<PathNode*> list, PathNode* _begin) : all_node(list), begin(_begin)
        {}
private:
    std::vector<PathNode*> all_node;
    PathNode* begin;
};


class Road : public MeshRender
{
public:
    Road(std::vector<vec3> nodes ): MeshRender(NULL)
    {
        GenerateModelRoad(nodes);
        Texture t;
        t.CreateFromFile("Texture/roadV3.png",PXF_A8R8G8B8);
        m_material->SetTexture(t,0,TRenderPass::RENDERPASS_DEFERRED);
    }

    void GenerateModelRoad(const std::vector<vec3>& nodes)
    {
        if(nodes.size() < 2)
            return;
        
        vec3 prev,n, dir, refnormal = vec3(0.0f,0.0f,1.0f);
        std::vector<Model::TVertex> _vertex;
        std::vector<Model::TIndex> _index;
        Model::TVertex vertex;
        for(int i = 0, len=nodes.size()-1;i < len;i++)
        {
            dir = nodes[i+1] - nodes[i];
            dir = normalize(dir);
            n = cross(dir,refnormal);
            if(i != 0)
            {
                vec3 tmp = n;
                n = n+prev;//normalize(n+prev);
                prev = tmp;
            }else prev = n;
            vertex.position = nodes[i]+n*3.0f;
            vertex.texCoords = vec2(0.5,0);
            vertex.normal = refnormal;
            _vertex.push_back(vertex);
            
            vertex.position = nodes[i]-n*3.0f;
            vertex.texCoords = vec2(0.5,1);
            _vertex.push_back(vertex);

            _index.push_back(1+i*2);
            _index.push_back(0+i*2);
            _index.push_back(3+i*2);

            _index.push_back(0+i*2);
            _index.push_back(2+i*2);
            _index.push_back(3+i*2);

        }
        vertex.position = nodes[nodes.size()-1]+prev*3.0f;
        vertex.texCoords = vec2(0.5,0);
        _vertex.push_back(vertex);
        vertex.position = nodes[nodes.size()-1]-prev*3.0f;
        vertex.texCoords = vec2(0.5,1);
        _vertex.push_back(vertex);
        m_baseModel = new Model(&(_vertex[0]), _vertex.size(),&(_index[0]),_index.size());
    }


private:
    Path* path;

};


void App::Run(int argc, char** argv)
{
    if(argc > 0)
        MediaManager::Instance().AddSearchPath(File(argv[0]).Path());

    AgmdApp::Run();
}

#define TO_PHYS(a) *((PhysicsTransfo*)&a)

void App::OnInit()
{
    ShaderPipeline* test =  MediaManager::Instance().LoadMediaFromFile<ShaderPipeline>("Shader/BuiltinShader/BumpMap.shader");
    pause = true;
    noise = 0.005;
    m_timer = 1000;
    MediaManager::Instance().RegisterLoader(new M2Loader(),"m2");

    m_MatProj3D = glm::perspective(60.0f, (float)getScreen().x / (float)getScreen().y, 0.1f, 10000.f); // glm::perspectiveFov(60.0f, (float)getScreen().x, (float)getScreen().y, 0.1f, 100.0f);

    m_MatProj2D = ortho(0.0f,(float)getScreen().x,0.0f,(float)getScreen().y);

    shader2D = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/classic_pipeline_2D.glsl");

    //ForwardRendering* mode = new ForwardRendering(getScreen());
    DeferredRendering* mode = new DeferredRendering(getScreen());
    drend = mode;
    RenderingMode::SetRenderingMode(mode);


    m_motioneffect = NULL;
    m_effect = NULL;

    m_motioneffect = new BlurMotionEffect(getScreen());
    m_effect = new BlurEffect(Texture());
    //PostEffectMgr::Instance().AddEffect(m_effect);

    cam3D = new TPCamera(m_MatProj3D);
    cam2D = new FPCamera(m_MatProj2D);
    Camera::SetCurrent(cam3D);
    m_fps = new GraphicString(ivec2(0,getScreen().y-15),"",Color::black);

    m_Scene = new Scene();
    std::vector<vec3> nodes;
    for(int i = 0; i < 1000; i++)
    {
        nodes.push_back(vec3(10*cos(i/200.0f*M_PI),50.0f-i/10.0f,10.0f));
    }
    /*nodes.push_back(vec3(50.0f,0.0f,10.0f));
    nodes.push_back(vec3(100.0f,0.0f,10.0f));
    nodes.push_back(vec3(100.0f,100.0f,10.0f));
    nodes.push_back(vec3(0.0f,100.0f,10.0f));
    nodes.push_back(vec3(0.0f,0.0f,10.0f));
    nodes.push_back(vec3(50.0f,0.0f,10.0f));*/

    Road* r = new Road(nodes);
    //m_Scene->AddMesh(r);

	Model* model = CreateBox(vec3(1),"",PT_TRIANGLELIST);
    MeshRender* mesh = new MeshRender(model);
    plane = mesh;
    mesh->GetTransform().Rotate(90.0f, vec3(1,0,0));
    mesh->GetTransform().Rotate(90.0f, vec3(0,-1,0));
    mesh->GetTransform().Translate(0,0,10);
    m_Scene->AddMesh(mesh);
    sphere = mesh;
    model = CreatePlane(ivec2(20000),ivec2(1),"",PT_TRIANGLELIST);
    m_Scene->AddMesh(new MeshRender(model));

    model = CreatePlane(ivec2(20000),ivec2(1),"",PT_TRIANGLELIST);
    MeshRender* me = new MeshRender(model);
    me->GetTransform().Translate(1000,0,0);
    me->GetTransform().Rotate(-90,vec3(0,1,0));
    m_Scene->AddMesh(me);
    

    AWindow* diffuseW = new AWindow();
    //diffuseW->SetFont(mode->GetDiffuseTexture());
    AWindow* depthW = new AWindow();
    depthW->SetFont(mode->GetShadowRenderer()->GetShadowDepth());
    AWindow* lightW = new AWindow();
    //lightW->SetFont(mode->GetLightingTexture());
    //GUIMgr::Instance().AddWidget(diffuseW);
    GUIMgr::Instance().AddWidget(depthW);
    //GUIMgr::Instance().AddWidget(lightW);   
    Renderer::Get().SetActiveScene(m_Scene);
    Renderer::Get().SetCullFace(2);

    m_light = new Light(vec3(0,0,10),-normalize(vec3(0,0.2,-1)),LIGHT_SPOT);
    m_Scene->AddLight(m_light);
    m_timer = 10000;

    m_light->SetRange(2000.0f);

    Camera::SetCurrent(cam3D, CAMERA_3D);
    Camera::SetCurrent(cam2D, CAMERA_2D);
}

void App::OnUpdate(uint64 time_diff/*in ms*/)
{
    m_Scene->Update(time_diff);
    if(m_timer <= time_diff)
    { 
        m_timer = 10000;
    }else m_timer -= time_diff;
    vec3 position = vec3(100*cos(m_timer/5000.0f*M_PI),100*sin(m_timer/5000.0f*M_PI),20.0f);
    //plane->GetTransform().SetPosition(position);
    //plane->GetTransform().SetRotation(quat(90.0f,vec3(1,0,0))*quat(-90.0f+180*m_timer/5000.0f,vec3(0,1,0)));
    
    //m_light->SetDirection(normalize(position));
}

void App::OnRender3D()
{


}

void App::OnRender2D()
{
    Renderer& render = Renderer::Get();


    // 2D RENDER BEGIN
    //Texture::TextureRender(tex);
    
    //render.SetCurrentProgram(shader2D);
    //int fps = getFps();
    //m_fps->m_Text = StringBuilder(fps)(", ")(fps ? (int)(1000/fps) : 999999999)(" ms ")(cam3D->GetPosition().x)(" ")(cam3D->GetPosition().y)(" ")(cam3D->GetPosition().z)(" shadow offset : ")(noise);//(" fps,")(fps ? (int)(1000/(float)fps) : 999999999)(" ms");
    *(m_fps) = render.GetStatistics().ToString();
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
        }
    }

    return AgmdApp::WindowProc(hwnd,message,wParam,lParam);
}

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

Model* App::CreateSphere(float r,float stack, float slice,float angle, std::string texture, TPrimitiveType type, uint32 color)
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

    for(uint32 i = 0; i < 6; i++)
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

void makeFace(std::vector<Model::TVertex>& vertex, std::vector<Model::TIndex>& index, int k)
{
    
}

/*Model* App::CreateMetaSphere(float r, int stack, int slice)
{
    std::vector<Model::TVertex> vertices;
    std::vector<Model::TIndex> index;
    vec3 face[] = {vec3(1,1,0),vec3(-1,-1,0),vec3()};

    for(int k = 0; k < 6; k++)
    {

    }
    
    for(int i = 0; i < stack; i++)
    {
        for(int j = 0; j < slice; j++)
        {
            Model::TVertex v;
            v = {vec3(r*cos(-M_PI/4+M_PI*i),r*sin(-M_PI/4+M_PI*i),r*cos(-M_PI/4+M_PI*j)),vec3(0,0,1),-1,vec2(1,0)};
        }
    }

}*/

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
