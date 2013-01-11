#include <Core/RenderingMode/DeferredRendering.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Renderer.h>
#include <Core/SceneObject/Scene.h>

namespace Agmd
{
    DeferredRendering::DeferredRendering(int width, int height) :
    RenderingMode(width,height)
    {
        Init();
    }

    DeferredRendering::DeferredRendering(ivec2 screen) :
    RenderingMode(screen)
    {
        Init();
    }

    DeferredRendering::~DeferredRendering()
    {

    }

    void DeferredRendering::Init()
   {
        Renderer& render = Renderer::Get();
        m_framebuffer = render.CreateFrameBuffer();
        m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);
        m_colorbuffer = render.CreateRenderBuffer(m_screen, PXF_A8R8G8B8);
        m_normalbuffer = render.CreateRenderBuffer(m_screen, PXF_R16G16B16);
        m_positionbuffer = render.CreateRenderBuffer(m_screen, PXF_R32G32B32);

        m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D);
        m_textureBuffer[1].Create(m_screen, PXF_R16G16B16, TEXTURE_2D);
        m_textureBuffer[2].Create(m_screen, PXF_R32G32B32, TEXTURE_2D);

        m_framebuffer->setRender(m_depthbuffer, DEPTH_ATTACHMENT);
        m_framebuffer->setRender(m_colorbuffer, COLOR_ATTACHMENT);
        m_framebuffer->setRender(m_normalbuffer, COLOR_ATTACHMENT1);
        m_framebuffer->setRender(m_positionbuffer, COLOR_ATTACHMENT2);

        m_framebuffer->setTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        m_framebuffer->setTexture(m_textureBuffer[1], COLOR_ATTACHMENT1);
        m_framebuffer->setTexture(m_textureBuffer[2], COLOR_ATTACHMENT2);
        
    }

    void DeferredRendering::Compute()
    {
        Renderer& render = Renderer::Get();
        Scene* sc = render.GetActiveScene();
        Start();
       render.Enable(RENDER_ZWRITE,true);
        m_framebuffer->Clear(CLEAR_DEPTH);
        m_framebuffer->DrawBuffer(0);
        m_framebuffer->Bind();
        render.Enable(RENDER_ZTEST,true);
        render.SetupDepthTest(DEPTH_LESS);
        sc->Render(TRenderPass::RENDERPASS_ZBUFFER);

        uint32 buffer[] = {COLOR_ATTACHMENT, COLOR_ATTACHMENT1, COLOR_ATTACHMENT2};
        m_framebuffer->DrawBuffers(3, buffer);
        m_framebuffer->Clear(CLEAR_COLOR);
        m_framebuffer->Bind();
        render.SetupDepthTest(DEPTH_LEQUAL);
        render.Enable(RENDER_ZWRITE,false);
        sc->Render(TRenderPass::RENDERPASS_DEFERRED);
        m_framebuffer->UnBind();
        
        End();
    }

    void DeferredRendering::Start()
    {
        m_framebuffer->Clear();
        m_framebuffer->Bind();
    }

    void DeferredRendering::End()
    {
        m_framebuffer->UnBind();
    }

    Texture DeferredRendering::GetDiffuseTexture()
    {
        return m_textureBuffer[0];
    }

    Texture DeferredRendering::GetNormalTexture()
    {
        return m_textureBuffer[1];
    }

    Texture DeferredRendering::GetPositionTexture()
    {
        return m_textureBuffer[2];
    }

}