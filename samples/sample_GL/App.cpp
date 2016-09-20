/*
============================================================================
DX TEST - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/


#include "App.h"
#include <Agmd3D/Core/MediaManager.h>
#include <Core/Driver.h>
#include <Core/Shader/ShaderPreCompiler.h>
#include <Core/Model/Material.h>
#include <Agmd3D/Core/SceneNode/CameraNode.h>
#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Agmd3D/Core/Model/IcosahedronModel.h>
#include <Agmd3D/Core/Controller/FirstPersonController.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>
#include <Agmd3D/Core/ResourceManager.h>

#include <Agmd3D/Core/SceneMgr/ASceneMgr.h>


#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#pragma warning(disable:4496)
using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

BaseShaderProgram* default_program;

void App::Run(int argc, char** argv)
{
    if (argc > 0)
    {
        File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
        ShaderPreCompiler::Instance().AddSearchPath(main.Path() + "/Shader/DX/");
        ShaderPreCompiler::Instance().AddSearchPath(main.Path() + "/Shader/GL/");
    }
    AgmdApplication::Run();
}


struct TVertex
{
    vec3 position;
    a_uint32 color;
};

DeclarationPtr declaration;
Buffer<TVertex> vertex;
Buffer<a_uint16> index;
ShaderProgram sprogram;
MeshNode* node;

struct TestBuffer
{
    mat4 m1;
    mat4 m2;
};

void App::init()
{
    printf("Loading end");

    ForwardRendering* mode = new ForwardRendering(getScreen());
    RenderingMode::setRenderingMode(mode);
    m_Scene = new SceneMgr();
    cam3D = new Camera(PROJECTION_PERSPECTIVE, ProjectionOption(vec2((float)getScreen().x, (float)getScreen().y), 35.0f));
    cam2D = new Camera(PROJECTION_ORTHO, ProjectionOption(vec4(0, 100.0f, 0, 100.0f)));
    InputController* controller = new FirstPersonController();
    ASceneMgr* scene = new ASceneMgr();
    ANode* node = scene->AddNode(NULL,NULL);
    node->SetController(controller);
    AgmdApplication::getApplication()->addInputListener(controller);
    node->m_camera = cam3D;
    cam3D->m_node = node;
    Driver::Get().SetActiveScene(scene);
    Model* model = new Icosahedron(3);
    Material* mat = ResourceManager::Instance().Get<Material>("DEFAULT_MATERIAL");
    for (a_uint32 i = 0; i < 10; i++)
    {
        for (a_uint32 j = 0; j < 10; j++)
        {
            for (a_uint32 k = 0; k < 10; k++)
            {
                node = scene->AddNode(model, mat);
                node->GetTransform().translate((i) * 4, k * 4, (j) * 4);
            }
        }
    }
    Camera::setCurrent(cam3D, CAMERA_3D);
    Camera::setCurrent(cam2D, CAMERA_2D);
}

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
}

void App::OnRender3D()
{
}

void App::OnRender2D()
{
}

void App::OnClick(int click, vec2 pos, bool up)
{
    AgmdApplication::OnClick(click, pos, up);
}

void App::OnMove(vec2 pos)
{
    AgmdApplication::OnMove(pos);
}

void App::OnKey(a_char key, bool up)
{
    if (up)
    {
        if (key == 'F')
        {
            Camera::getCurrent()->FreezeFrustrum(true);
        }
        else if (key == 'U')
        {
            Camera::getCurrent()->FreezeFrustrum(false);
        }
    }
    AgmdApplication::OnKey(key, up);
}
