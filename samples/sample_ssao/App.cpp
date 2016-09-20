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
#include <Agmd3D\Core\MediaManager.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D\Core\RenderObject\GraphicString.h>
#include <Agmd3D/Core/SceneNode/CameraNode.h>
#include <Agmd3D/Core/Controller/FirstPersonController.h>
#include <Agmd3D/Core/Model/Light.h>
#include <Agmd3D\Core\Buffer\FrameBuffer.h>
#include <Agmd3D/Core/RenderingMode/RenderingMode.h>
#include <Agmd3D/Core/RenderingMode/DeferredRendering.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>
#include <AgmdUtilities/Utilities/Color.h>
#include <AgmdUtilities/Debug/Profiler.h>
#include <Agmd3D/Core/Effects/PostEffectMgr.h>
#include <Agmd3D/Core/RenderObject/MeshRender.h>
#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <Agmd3D/Core/Shader/ShaderPipeline.h>
#include <Agmd3D/Core/Tools/Statistics.h>
#include <Agmd3D/Core/Model/Material.h>
#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include <Core/Shader/ShaderPreCompiler.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

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
        ShaderPreCompiler::Instance().AddSearchPath(main.Path() + "/Shader");
    }

    AgmdApplication::Run();
}

Texture tvelocity;
Texture tmass;
ShaderProgram velocity_program;
ShaderProgram mass_program;
Texture tex[2];


#include <random>
#include <iostream>

#define MAX_KERNEL_SIZE 128
#define PI 3.14159265

int kernelSize = 30;
vec3 kernel[MAX_KERNEL_SIZE];
const int noiseSize = 16;
vec3 noise[noiseSize];

// float random(float a, float b) {
//     return ( rand()/(double)RAND_MAX ) * (b-a) + a;
// }
// 
// float lerp(float a, float b, float value) {
//     return value / (b - a) + a;
// }
// 
// void initKernel(vec3* kernel, int kernelSize,) {
// 
//     if (useHemisphere) {
//         for (int i = 0; i < kernelSize; ++i) {
//             kernel[i] = vec3(
//                 random(-1.0f, 1.0f),
//                 random(-1.0f, 1.0f),
//                 random(0.1f, 1.0f)
//                 );
//             //clamp to unit hemisphere
//             kernel[i] = normalize(kernel[i]);
// 
//             //What we actually want is for the distance from the origin to falloff as we generate more points
//             float scale = float(i) / float(kernelSize);
//             scale = lerp(0.1, 1.1, scale * scale);
//             kernel[i] = kernel[i] * scale;
//         }
//     } else {
// 
//         for (int i = 0; i < MAX_KERNEL_SIZE; ++i) {
//             kernel[i] = vec3(
//                 random(-1.0f, 1.0f),
//                 random(-1.0f, 1.0f),
//                 random(-1.0f, 1.0f)
//                 );
//             //clamp to unit hemisphere
//             kernel[i] = normalize(kernel[i]);
// 
//             //What we actually want is for the distance from the origin to falloff as we generate more points
//             float scale = float(i) / float(kernelSize);
//             scale = lerp(0.1, 1.1, scale * scale);
//             kernel[i] = kernel[i] * scale;
//         }
//     }
// }
// 
// void initNoiseTexture(vec3* noise,int size) {
//     for (int i = 0; i < size; ++i) {
//         noise[i] = vec3(
//             random(0.0f, 1.0f),
//             random(0.0f, 1.0f),
//             0.0
//             );
// 
//         noise[i] = normalize(noise[i]);
// 
//         //std::cout << noise[i].x << ", " << noise[i].y << ", " << noise[i].z << std::endl;
//     }
// }
// 
// Texture createTexture(int w, int h, bool isDepth = false)
// {
// //     unsigned int textureId;
// //     glGenTextures(1, &textureId);
// //     glBindTexture(GL_TEXTURE_2D, textureId);
// //     glTexImage2D(GL_TEXTURE_2D, 0, isDepth ? GL_DEPTH_COMPONENT : GL_RGBA8, w, h, 0, isDepth ? GL_DEPTH_COMPONENT : GL_RGBA, GL_FLOAT, NULL);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// // 
// //     int i = glGetError();
// //     if(i != 0) {
// //         std::cout << "Error happened while loading the texture: " << i << std::endl;
// //     }
// // 
// //     glBindTexture(GL_TEXTURE_2D, 0);
// 
// 
//     Texture tex;
//     tex.Create(ivec2(w,h),isDepth ? PXF_DEPTH : PXF_A8R8G8B8,TEXTURE_2D);
//     return tex;
// }


void App::init()
{
    printf("Loading...");
    m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 100.f);
    m_MatProj2D = ortho(0.0f, (float)getScreen().x, 0.0f, (float)getScreen().y);
    DeferredRendering* mode = new DeferredRendering(getScreen());
    RenderingMode::setRenderingMode(mode);
    tex[0].Create(getScreen(), PXF_A8R8G8B8, TEXTURE_2D);
    tex[1].Create(getScreen(), PXF_A8R8G8B8, TEXTURE_2D);

    m_fps = new GraphicString(ivec2(0, getScreen().y - 15), "", Color::black);
    m_Scene = new SceneMgr();
    Texture t;
    Texture color_gradiant;

    Material* mat = new Material();
    mat->SetTexture(t, 0, (TRenderPass)((1 << RENDERPASS_DEFERRED) | (1 << RENDERPASS_ZBUFFER)));
    mat->SetTexture(color_gradiant, 1, (TRenderPass)(1 << RENDERPASS_DEFERRED));
    Driver::Get().SetActiveScene(m_Scene);
    Driver::Get().SetCullFace(2);

    //m_light = new Light(vec3(0, 0 ,10),-normalize(vec3(0,0.2,-1)),LightType::LIGHT_DIR);//new Light(vec3(0,0,10),-normalize(vec3(0,0.5,-1)),LIGHT_SPOT);
    //m_Scene->AddLight(m_light);
    //m_light->SetRange(2000.0f);

    //box->SetTexture(tex_cubemap);
    cam3D = new Camera(PROJECTION_PERSPECTIVE, ProjectionOption(vec2(getScreen()), 60.0f, 0));

    InputController* controller = new FirstPersonController();
    CameraNode* camNode = new CameraNode(cam3D, controller);
    camNode->setController(controller);
    m_Scene->AddNode(camNode);
    cam2D = new Camera(PROJECTION_ORTHO, ProjectionOption(vec4(0, 100.0f, 0, 100.0f)));

    velocity_program.LoadFromFile("Shader/particle_velocity_render.glsl");
    mass_program.LoadFromFile("Shader/particle_mass_render.glsl");
    tmass.Create(getScreen(), PXF_A8R8G8B8, TEXTURE_2D);
    tvelocity.Create(getScreen(), PXF_A8R8G8B8, TEXTURE_2D);


    Camera::setCurrent(cam3D, CAMERA_3D);
    Camera::setCurrent(cam2D, CAMERA_2D);

    printf("Loading end");
}

float timespeed = 1.0f;

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
}

void App::OnRender3D()
{
}

void App::OnRender2D()
{
}

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return 0;
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
    AgmdApplication::OnKey(key, up);
}
