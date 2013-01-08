#include <Core/RenderingMode/VertexRendering.h>
#include <Core/Renderer.h>
#include <Core/SceneObject/Scene.h>

namespace Agmd
{

    
    VertexRendering::VertexRendering(int width, int height) :
    RenderingMode(width,height)
    {
    }

    VertexRendering::VertexRendering(ivec2 screen) :
    RenderingMode(screen)
    {
    }

    VertexRendering::~VertexRendering()
    {
    }

    void VertexRendering::Compute()
    {
        Renderer& render = Renderer::Get();
        Scene* sc = render.GetActiveScene();
        Start();

        /*
           FirstPass, on génére ici uniquement le Buffer de profondeur (Zbuffer).
        */

        sc->Render(TRenderPass::RENDERPASS_ZBUFFER);
        
        /*
            ZBUFFER TO EQUALS
        */
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