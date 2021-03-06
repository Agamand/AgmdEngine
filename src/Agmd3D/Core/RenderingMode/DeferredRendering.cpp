/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

/*
    Status : In dev !
*/

#include <Core/RenderingMode/DeferredRendering.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Driver.h>
#include <Core/Model/SceneMgr.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/Effects/PostEffectMgr.h>

namespace Agmd
{
    DeferredRendering::DeferredRendering(int width, int height) :
        RenderingMode(width, height),
        m_framebuffer(NULL),
        m_shadowRender(NULL)
    {
        init();
    }

    DeferredRendering::DeferredRendering(ivec2& screen) :
        RenderingMode(screen),
        m_framebuffer(NULL),
        m_shadowRender(NULL)
    {
        init();
    }

    DeferredRendering::~DeferredRendering()
    {
        if (m_bufferFlags)
            delete m_bufferFlags;
        delete m_shadowRender;
    }

    void DeferredRendering::init()
    {
        Driver& render = Driver::Get();
        if (!m_framebuffer)
            m_framebuffer = render.CreateFrameBuffer();

        m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[1].Create(m_screen, PXF_R16G16B16, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[2].Create(m_screen, PXF_R32G32B32, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[3].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[4].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[5].Create(m_screen, PXF_DEPTH, TEXTURE_2D, TEX_NOMIPMAP);

        m_framebuffer->SetTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        m_framebuffer->SetTexture(m_textureBuffer[1], COLOR_ATTACHMENT + 1);
        m_framebuffer->SetTexture(m_textureBuffer[2], COLOR_ATTACHMENT + 2);
        m_framebuffer->SetTexture(m_textureBuffer[5], DEPTH_ATTACHMENT);
        a_uint32 buffer[] = {COLOR_ATTACHMENT, COLOR_ATTACHMENT + 1, COLOR_ATTACHMENT + 2};
        m_bufferFlags = m_framebuffer->GenerateBufferFlags(3, buffer);
        m_light_program[DIRECTIONNAL].LoadFromFile("Shader/RenderingShader/DeferredDirLightShader.glsl");
        m_light_program[SPOT].LoadFromFile("Shader/RenderingShader/DeferredSpotLightShader.glsl");
        m_light_program[DIRECTIONNAL_WITH_SHADOW].LoadFromFile("Shader/RenderingShader/DeferredDirLightShaderWS.glsl");
        m_light_program[SPOT_WITH_SHADOW].LoadFromFile("Shader/RenderingShader/DeferredSpotLightShaderWS.glsl");
        if (!m_shadowRender)
            m_shadowRender = new ShadowMapRenderer(ivec2(2048));
    }


    void DeferredRendering::compute(ARenderQueue& queue)
    {
        //         Driver& render = Driver::Get();
        //         render.SetViewPort(ivec2(),render.GetScreen());
        //         SceneMgr* sc = render.GetActiveScene();
        //         vec3 cameraPosition = Camera::getCurrent(CAMERA_3D)->getNode()->getTransform().getPosition();
        //         const a_vector<Light*>& lights = sc->GetLights();
        // 
        //         
        //         a_uint32 maxLights = lights.size();
        // 
        //         start();
        //         render.SetRenderMode(m_mode);
        //         SkyBox* box = sc->GetSkyBox();
        //         render.SetCullFace(1);
        //         if(box)
        //         {
        //             render.Enable(RENDER_ZWRITE,false);
        //             box->Render();
        //         }
        //         sc->Update();
        //         sc->Compute();
        //         /*if(sc->isEmpty())
        //         {
        //             End();
        //             return;
        //         }*/
        //         render.SetCullFace(0);
        //         render.Enable(RENDER_ZWRITE,true);
        //         m_framebuffer->Clear(CLEAR_DEPTH);
        //         m_framebuffer->DrawBuffer(0);
        //         m_framebuffer->Bind();
        //         render.Enable(RENDER_ZTEST,true);
        //         render.SetupDepthTest(DEPTH_LESS);
        //         sc->Render(TRenderPass::RENDERPASS_ZBUFFER);
        // 
        //         m_framebuffer->DrawBuffers(3, m_bufferFlags);
        //         m_framebuffer->Clear(CLEAR_COLOR);
        //         m_framebuffer->Bind();
        //         render.SetupDepthTest(DEPTH_LEQUAL);
        //         render.Enable(RENDER_ZWRITE,false);
        //         sc->Render(TRenderPass::RENDERPASS_DEFERRED);
        //         m_framebuffer->UnBind();
        // 
        // 
        //         render.Enable(RENDER_ZTEST,false);
        //         
        //         render.SetRenderMode(MODE_FILL);
        //         //if(PostEffectMgr::Instance().HaveEffect())
        //         
        //         bool shadow = true;
        //         if(maxLights)
        //         {
        //             //render.Enable(RENDER_ALPHABLEND, true);
        //             //render.SetupAlphaBlending(BLEND_SRCCOLOR, BLEND_DESTCOLOR);
        //             for(a_uint32 i = 0; i < maxLights; i++)
        //             {
        //                 render.SetCurrentProgram(m_light_program[lights[i]->GetType()].GetShaderProgram());
        //                 if(shadow)//if shadow is enable
        //                 {
        //                     //Re-enable Z-Test for making shadow cast
        //                     render.Enable(RENDER_ZTEST,true);
        //                     render.Enable(RENDER_ZWRITE,true);
        //                     render.SetupDepthTest(DEPTH_LESS);
        //                     lights[i]->Bind();
        //                     m_shadowRender->Reset();
        //                     m_shadowRender->BeginLight(lights[i]);
        //                     sc->Draw();
        //                     m_shadowRender->EndLight();
        //                 }
        //                 //Disable Z-Test for light rendering
        //                 render.SetupDepthTest(DEPTH_LEQUAL);
        //                 render.Enable(RENDER_ZWRITE,false);
        //                 render.Enable(RENDER_ZTEST,false);
        //                 render.SetTexture(0,m_textureBuffer[0].GetTexture());
        //                 render.SetTexture(1,m_textureBuffer[1].GetTexture());
        //                 render.SetTexture(2,m_textureBuffer[2].GetTexture());
        //                 render.SetCurrentProgram(m_light_program[lights[i]->GetType()+(shadow? 3: 0)/*+3 for use with SHADOW*/].GetShaderProgram());
        //                 render.GetCurrentProgram()->SetParameter("u_cameraPosition",cameraPosition);
        //                 if(shadow)
        //                     m_shadowRender->SetupForRendering();
        //                 Texture::BeginRenderToTexture(m_textureBuffer[3]);
        //                 Fast2DSurface::Instance().Draw();
        //             }
        //             render.SetCurrentProgram(NULL);
        //             render.Enable(RENDER_ALPHABLEND, false);
        //             Texture::EndRenderToTexture();
        //         }else
        //         {
        //             Texture::TextureRender(m_textureBuffer[0],ivec2(0),m_screen);
        //             end();
        //             return;
        //         }
        //         if(PostEffectMgr::Instance().HaveEffect())
        //         {
        //             PostEffectMgr::Instance().ApplyEffect(m_textureBuffer[3],m_textureBuffer[4]);
        //             Texture::TextureRender(m_textureBuffer[4],ivec2(0),m_screen);
        //         }
        //         else
        //         {
        //            Texture::TextureRender(m_textureBuffer[3],ivec2(0),m_screen);
        //         }
        //             

        //   end();
    }

    void DeferredRendering::start()
    {
    }

    void DeferredRendering::end()
    {
    }

    Texture DeferredRendering::getDiffuseTexture()
    {
        return m_textureBuffer[0];
    }

    Texture DeferredRendering::getNormalTexture()
    {
        return m_textureBuffer[1];
    }

    Texture DeferredRendering::getPositionTexture()
    {
        return m_textureBuffer[2];
    }

    ShadowMapRenderer* DeferredRendering::getShadowRenderer()
    {
        return m_shadowRender;
    }
}
