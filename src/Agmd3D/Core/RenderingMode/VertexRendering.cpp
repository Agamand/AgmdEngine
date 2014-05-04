/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderingMode/VertexRendering.h>
#include <Core/Driver.h>
#include <Core/SceneObject/SceneMgr.h>

namespace Agmd
{

    
    VertexRendering::VertexRendering(int width, int height) :
    RenderingMode(width,height)
    {
    }

    VertexRendering::VertexRendering(ivec2& screen) :
    RenderingMode(screen)
    {
    }

    VertexRendering::~VertexRendering()
    {
    }

    void VertexRendering::Compute()
    {
        Driver& render = Driver::Get();
        SceneMgr* sc = render.GetActiveScene();
        Start();

        sc->Render(TRenderPass::RENDERPASS_ZBUFFER);

        sc->Render(TRenderPass::RENDERPASS_DIFFUSE);
        End();
    }

    void VertexRendering::Start()
    {

    }

    void VertexRendering::End()
    {
    }
}