#include <Core/RenderingMode/ForwardRendering.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Renderer.h>
#include <Core/SceneObject/Scene.h>
#include <Utilities/Timer.h>
namespace Agmd
{
    ForwardRendering::ForwardRendering(int width, int height) :
    RenderingMode(width,height)
    {
        Init();
    }

    ForwardRendering::ForwardRendering(ivec2 screen) :
    RenderingMode(screen)
    {
        Init();
    }

    ForwardRendering::~ForwardRendering()
    {
    }

    void ForwardRendering::Init()
    {
        Renderer& render = Renderer::Get();
        m_framebuffer = render.CreateFrameBuffer();
        m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);

        m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        m_textureBuffer[1].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        m_textureBuffer[2].Create(m_screen, PXF_DEPTH, TEXTURE_2D,TEX_NOMIPMAP);

        m_framebuffer->setRender(m_depthbuffer, DEPTH_ATTACHMENT);

        m_framebuffer->setTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        m_framebuffer->setTexture(m_textureBuffer[1], COLOR_ATTACHMENT1);
        m_framebuffer->setTexture(m_textureBuffer[2], DEPTH_ATTACHMENT);
    }

    void ForwardRendering::Compute()
    {
        Renderer& render = Renderer::Get();
        Scene* sc = render.GetActiveScene();
        Start();

        /*
           FirstPass, on g�n�re ici uniquement le Buffer de profondeur (Zbuffer).
        */
#ifdef PROFILING_TIME
        Timer timer;
        timer.start();  
#endif 
        render.Enable(RENDER_ZWRITE,true);
        m_framebuffer->Clear(CLEAR_DEPTH);
        m_framebuffer->DrawBuffer(0);
        m_framebuffer->Bind();
        render.Enable(RENDER_ZTEST,true);
        render.SetupDepthTest(DEPTH_LESS);
        sc->Render(RENDERPASS_ZBUFFER);
        m_framebuffer->UnBind();
        /*
            <!> ZBUFFER MUST BE TO LESS OR EQUALS
            AND STOP WRITE IN Z BUFFER,
            ONLY READING <!>
        */

        /*
            Render diffuse to color_attachment0
        */
        uint32 buffer[] = {COLOR_ATTACHMENT};
        m_framebuffer->DrawBuffers(1,buffer);
        m_framebuffer->Clear(CLEAR_COLOR);
        m_framebuffer->Bind();
        render.SetupDepthTest(DEPTH_LEQUAL);
        render.Enable(RENDER_ZWRITE,false);
        sc->Render(RENDERPASS_DIFFUSE);
        m_framebuffer->UnBind();

        /*
            Render lighting to color_attachment1
        */
        std::vector<Light*> lights = sc->GetLights();
        uint32 maxLights = lights.size();
        //maxLights = 0;
        if(maxLights)
        {
            uint32 buffer2[] = {COLOR_ATTACHMENT1};
            m_framebuffer->DrawBuffers(1,buffer2);
            m_framebuffer->Clear(CLEAR_COLOR);
            m_framebuffer->Bind();
            render.SetupDepthTest(DEPTH_LEQUAL);
            render.Enable(RENDER_ZWRITE, false);
            render.Enable(RENDER_ALPHABLEND, true);
            render.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_DESTALPHA);
        
        
            for(uint32 i = 0; i < maxLights; i++)
            {
                lights[i]->Bind();
                sc->Render(RENDERPASS_LIGHTING);
            }
            m_framebuffer->UnBind();
            render.Enable(RENDER_ALPHABLEND, false);
        }
        /*
            Render to main framebuffer
        */
        render.Enable(RENDER_ZTEST,false);
        Texture::TextureRender(m_textureBuffer[0]);

        if(maxLights)
        {
            render.Enable(RENDER_ALPHABLEND, true);
            render.SetupAlphaBlending(BLEND_DESTCOLOR, BLEND_ZERO);
            Texture::TextureRender(m_textureBuffer[1]);
            render.Enable(RENDER_ALPHABLEND, false);
        }
#ifdef PROFILING_TIME
        timer.stop();
        double _timer = timer.getElapsedTimeInMicroSec();
        printf("Rendering function : %f us\n",_timer);
#endif
        End();
    }

    void ForwardRendering::Start()
    {

    }

    void ForwardRendering::End()
    {
    }

    Texture ForwardRendering::GetDiffuseTexture()
    {
        return m_textureBuffer[0];
    }

    Texture ForwardRendering::GetLightingTexture()
    {
        return m_textureBuffer[1];
    }

    Texture ForwardRendering::GetDepthTexture()
    {
        return m_textureBuffer[2];
    }

}