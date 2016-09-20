#include "App.h"
#include <Agmd3D/Core/MediaManager.h>
#include <Agmd3D/Core/Driver.h>
#include <Agmd3D/Core/Enums.h>
#include <Agmd3D/Core/Declaration.h>
#include <Agmd3D/Core/DeclarationElement.h>
#include <Agmd3D/Core/ResourceManager.h>
#include <Agmd3D/Core/Model/GeometryFactory.h>

#include <Agmd3D/Core/Buffer/FrameBuffer.h>

#include <Agmd3D/Core/RenderObject/GraphicString.h>

#include <Agmd3D/Core/Model/Scene.h>
#include <Agmd3D/Core/Model/Water.h>
#include <Agmd3D/Core/Model/SkyBox.h>
#include <Agmd3D/Core/Model/Light.h>
#include <Agmd3D/Core/Model/Material.h>

#include <Agmd3D/Core/SceneNode/MeshNode.h>
#include <Agmd3D/Core/SceneNode/CameraNode.h>

#include <Agmd3D/Core/RenderingMode/DeferredRendering.h>
#include <Agmd3D/Core/RenderingMode/ForwardRendering.h>

#include <Agmd3D/Core/Camera/FPCamera.h>
#include <Agmd3D/Core/Camera/FollowCamera.h>

#include <AgmdUtilities/Utilities/Color.h>

#include <Agmd3D/Core/Effects/PostEffectMgr.h>
#include <Agmd3D/Core/Effects/AntiAliasing.h>

#include <Agmd3D/Core/RenderObject/MeshRender.h>

#include <Agmd3D/Core/GUI/GUIMgr.h>
#include <Agmd3D/Core/GUI/ASlider.h>
#include <Agmd3D/Core/GUI/AWindow.h>

#include <Agmd3D/Core/Shader/ShaderPreCompiler.h>
#include <Agmd3D/Core/Controller/FirstPersonController.h>


#include <Agmd3D/Core/Tools/Statistics.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Agmd3D/Core/Tools/Fast2DSurface.h>
#include <glm/ext.hpp>
#include <libnoise/noise.h>

#include <Agmd3D/Loaders/AssetLoader.h>
#include <Agmd3D/Loaders/FBXLoader.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <Core/Shader/ShaderPipeline.h>


using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);


void App::Run(int argc, char** argv)
{
    if (argc > 0)
    {
        File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
        ShaderPreCompiler::Instance().AddSearchPath(main.Path() + "/Shader");
    }
    wxEntryStart(argc, argv);
    AgmdApplication::Run(argc, argv);
}


void App::MakeWindow()
{
    //wxApp::SetInstance(m_wxApplication);
}

void App::init()
{
    m_MatProj3D = glm::perspective(35.0f, (float)getScreen().x / (float)getScreen().y, 0.01f, 1000.f);
    m_MatProj2D = ortho(0.0f, (float)getScreen().x, 0.0f, (float)getScreen().y);
    ForwardRendering* mode = new ForwardRendering(getScreen());
    //DeferredRendering* mode = new DeferredRendering(getScreen());
    RenderingMode::setRenderingMode(mode);
    m_fps = new GraphicString(ivec2(0, getScreen().y - 15), "", Color::black, "Arial", 20);
    m_Scene = new SceneMgr();
    AssetLoader assetLoader;
    FBXLoader fbxLoader;


    //
    //SceneNode* ironMan = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\ironman\\ironman.fbx");
    //Model* model = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\im\\im.fbx");
    //Model* model = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\cube01.fbx");
    //SceneNode* ironMan = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\Peacock\\6ft_Peacock.fbx");
    //Model* model = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\TheWitcher\\watcher.FBX");
    //

    SceneNode* triss = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\Triss\\triss.FBX");
    m_Scene->AddNode(triss);

    SceneNode* geralt = fbxLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\TheWitcher2\\witcher.FBX");
    geralt->getTransform().translate(-5.0f, 0, 0);
    m_Scene->AddNode(geralt);

    //D:\projet Annuel\OGL_Thematique\OPENGL\Data\TheWitcher
    //SceneNode* dragon = assetLoader.LoadFromFile("D:\\projet Annuel\\agmdengine\\bin\\Debug_Win32\\model\\dragon.obj");
    //    SceneNode* ironMan = assetLoader.LoadFromFile("D:\\projet Annuel\\OGL_Thematique\\OPENGL\\Data\\ironman\\ironman.fbx");


    GUIMgr& guimgr = GUIMgr::Instance();

    Driver::Get().SetActiveScene(m_Scene);
    Driver::Get().SetCullFace(2);
    cam3D = new Camera(PROJECTION_PERSPECTIVE, ProjectionOption(vec2(getScreen()), 60.0f, 0));
    InputController* controller = new FirstPersonController();
    camNode = new CameraNode(cam3D, controller);
    camNode->setController(controller);
    m_Scene->AddNode(camNode);
    cam2D = new Camera(PROJECTION_ORTHO, ProjectionOption(vec4(0, 100.0f, 0, 100.0f)));
    Camera::setCurrent(cam3D, CAMERA_3D);
    Camera::setCurrent(cam2D, CAMERA_2D);
}

float _time = 0;

void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
    _time += time_diff / 10000.0f;
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
    AgmdApplication::OnKey(key, up);
}
