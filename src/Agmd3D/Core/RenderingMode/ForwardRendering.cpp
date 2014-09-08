/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderingMode/ForwardRendering.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Driver.h>
#include <Core/SceneObject/SceneMgr.h>
#include <Utilities/Timer.h>

namespace Agmd
{
    ForwardRendering::ForwardRendering(int width, int height) :
    RenderingMode(width,height)
    {
        init();
    }

    ForwardRendering::ForwardRendering(ivec2& screen) :
    RenderingMode(screen)
    {
        init();
    }

    ForwardRendering::~ForwardRendering()
    {
        if(bufferFlags[0])
            delete bufferFlags[0];

        if(bufferFlags[1])
            delete bufferFlags[1];
    }

    void ForwardRendering::init()
    {
        Driver& render = Driver::Get();
        m_framebuffer = render.CreateFrameBuffer();
        m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);

        m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        m_textureBuffer[1].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        m_textureBuffer[2].Create(m_screen, PXF_DEPTH, TEXTURE_2D,TEX_NOMIPMAP);

        m_framebuffer->SetRender(m_depthbuffer, DEPTH_ATTACHMENT);

        m_framebuffer->SetTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        m_framebuffer->SetTexture(m_textureBuffer[1], COLOR_ATTACHMENT+1);
        m_framebuffer->SetTexture(m_textureBuffer[2], DEPTH_ATTACHMENT);

        a_uint32 buffer[] = {COLOR_ATTACHMENT};
        bufferFlags[0] = m_framebuffer->GenerateBufferFlags(1,buffer);
        a_uint32 buffer2[] = {COLOR_ATTACHMENT+1};
        bufferFlags[1] = m_framebuffer->GenerateBufferFlags(1,buffer2);

    }

    void ForwardRendering::compute()
    {
        Driver& render = Driver::Get();
        start();
		render.SetViewPort(ivec2(),render.GetScreen());
        SceneMgr* sc = render.GetActiveScene();
		render.SetRenderMode(m_mode);
		sc->Update();
		sc->Compute();
        /*
           FirstPass, here is draw the ZBuffer(Only).
        */
        render.Enable(RENDER_ZWRITE,true);
		//render.clear(CLEAR_DEPTH);
        //m_framebuffer->Clear(CLEAR_DEPTH);
        //m_framebuffer->DrawBuffer(0);
        //m_framebuffer->Bind();
        render.Enable(RENDER_ZTEST,true);
        //render.SetupDepthTest(DEPTH_LESS);
        //sc->Render(RENDERPASS_ZBUFFER);
        //m_framebuffer->UnBind();
        /*
            <!> ZBUFFER MUST BE TO LESS OR EQUALS
            AND STOP WRITE IN Z BUFFER,
            ONLY READING <!>
        */

        /*
            Render diffuse to color_attachment0
        */

        //m_framebuffer->DrawBuffers(1,bufferFlags[0]);
        //m_framebuffer->Clear(CLEAR_COLOR);
        //m_framebuffer->Bind();
        //render.SetupDepthTest(DEPTH_LEQUAL);
        //render.Enable(RENDER_ZWRITE,false);
        sc->Render(RENDERPASS_DIFFUSE);
		render.Enable(RENDER_ALPHABLEND,true);
		sc->Render(RENDERPASS_DIFFUSE,RenderQueue::TRenderType::TYPE_BLEND);
		render.Enable(RENDER_ALPHABLEND,false);
        //m_framebuffer->UnBind();sqq

        /*
            Render lighting to color_attachment1
        */

        /*const std::vector<Light*>&  lights = sc->GetLights();
        uint32 maxLights = lights.size();
        if(maxLights)
        {
            m_framebuffer->DrawBuffers(1,bufferFlags[1]);
            m_framebuffer->Clear(CLEAR_COLOR);
            m_framebuffer->Bind();
            render.SetupDepthTest(DEPTH_LEQUAL);
            render.Enable(RENDER_ZWRITE, false);
            render.Enable(RENDER_ALPHABLEND, true);
            render.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_DESTALPHA);
        
            Light* const* _lights = &lights[0];
            for(uint32 i = 0; i < maxLights; i++)
            {
                _lights[i]->Bind();
                //sc->Render(RENDERPASS_LIGHTING);
            }
            m_framebuffer->UnBind();
            render.Enable(RENDER_ALPHABLEND, false);
        }*/
        /*
            Render to main framebuffer
        */
        render.Enable(RENDER_ZTEST,false);
        //Texture::TextureRender(m_textureBuffer[0]);

        /*if(maxLights)
        {
            render.Enable(RENDER_ALPHABLEND, true);
            render.SetupAlphaBlending(BLEND_DESTCOLOR, BLEND_ZERO);
            Texture::TextureRender(m_textureBuffer[1]);
            render.Enable(RENDER_ALPHABLEND, false);
        }*/
        end();
    }

    void ForwardRendering::start()
    {

    }

    void ForwardRendering::end()
    {
    }

    Texture ForwardRendering::getDiffuseTexture()
    {
        return m_textureBuffer[0];
    }

    Texture ForwardRendering::getLightingTexture()
    {
        return m_textureBuffer[1];
    }

    Texture ForwardRendering::getDepthTexture()
    {
        return m_textureBuffer[2];
    }

}