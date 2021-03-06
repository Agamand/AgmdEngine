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
#include <Core/Model/SceneMgr.h>
#include <Core/Model/Material.h>
#include <Core/Model/Model.h>
#include <Utilities/Timer.h>

namespace Agmd
{
    ForwardRendering::ForwardRendering(int width, int height) :
        RenderingMode(width, height),
        m_framebuffer(NULL),
        m_depthbuffer(NULL)
    {
        init();
    }

    ForwardRendering::ForwardRendering(ivec2& screen) :
        RenderingMode(screen),
        m_framebuffer(NULL),
        m_depthbuffer(NULL)
    {
        init();
    }

    ForwardRendering::~ForwardRendering()
    {
        if (bufferFlags[0])
            delete bufferFlags[0];

        if (bufferFlags[1])
            delete bufferFlags[1];
    }

    void ForwardRendering::init()
    {
        Driver& render = Driver::Get();

        //         if(!m_framebuffer)
        //             m_framebuffer = render.CreateFrameBuffer();
        //         if(m_depthbuffer)
        //         {
        //             delete m_depthbuffer;
        //             m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);
        //         }else m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);
        // 
        //         m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        //         m_textureBuffer[1].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D,TEX_NOMIPMAP);
        //         m_textureBuffer[2].Create(m_screen, PXF_DEPTH, TEXTURE_2D,TEX_NOMIPMAP);

        //         m_framebuffer->SetRender(m_depthbuffer, DEPTH_ATTACHMENT);
        // 
        //         m_framebuffer->SetTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        //         m_framebuffer->SetTexture(m_textureBuffer[1], COLOR_ATTACHMENT+1);
        //         m_framebuffer->SetTexture(m_textureBuffer[2], DEPTH_ATTACHMENT);

        //         a_uint32 buffer[] = {COLOR_ATTACHMENT};
        //         bufferFlags[0] = m_framebuffer->GenerateBufferFlags(1,buffer);
        //         a_uint32 buffer2[] = {COLOR_ATTACHMENT+1};
        //         bufferFlags[1] = m_framebuffer->GenerateBufferFlags(1,buffer2);
    }

    void ForwardRendering::compute(ARenderQueue& queue)
    {
        //
        Driver& render = Driver::Get();
        start();


        a_vector<Drawable> drawable = queue.GetDrawable(TRenderType::TYPE_DIFFUSE);
        render.SetViewPort(ivec2(), render.GetScreen());
        Material* mat = NULL;
        for (a_uint32 i = 0; i < drawable.size(); i++)
        {
            Drawable& d = drawable[i];
            if (mat != d.mat)
            {
                mat = d.mat;
                mat->Enable(RENDERPASS_DIFFUSE);
            }
            d.model->Draw(&d.transform);
        }


        end();
        //         
        //         SceneMgr* sc = NULL;// render.GetActiveScene();
        //         SkyBox* box = sc->GetSkyBox();
        //         render.SetCullFace(1);
        //         if(box)
        //         {
        //             render.Enable(RENDER_ZWRITE,false);
        //             box->Render();
        //         }
        //         render.SetRenderMode(m_mode);
        //         render.SetCullFace(0);
        //sc->Update();
        //sc->Compute();
        /*
           FirstPass, here is draw the ZBuffer(Only).
        */
        //render.Enable(RENDER_ZWRITE,true);
        //render.clear(CLEAR_DEPTH);
        //m_framebuffer->Clear(CLEAR_DEPTH);
        //m_framebuffer->DrawBuffer(0);
        //m_framebuffer->Bind();
        //render.Enable(RENDER_ZTEST,true);
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
        //         sc->Render(RENDERPASS_DIFFUSE);
        //         render.Enable(RENDER_ALPHABLEND,true);
        //         render.SetupDepthTest(DEPTH_LEQUAL);
        //         render.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
        //         sc->Render(RENDERPASS_DIFFUSE,TRenderType::TYPE_BLEND);
        //         render.Enable(RENDER_ALPHABLEND,false);

        //m_framebuffer->UnBind();

        /*
            MultiPass lighting system
            Render lighting to color_attachment1
        */

        //         const a_vector<LightNode*>&  lights = sc->GetLightNodes();
        //         a_uint32 maxLights = lights.size();
        //         if(maxLights)
        //         {
        //             m_framebuffer->DrawBuffers(1,bufferFlags[1]);
        //             m_framebuffer->Clear(CLEAR_COLOR);
        //             m_framebuffer->Bind();
        //             render.SetupDepthTest(DEPTH_LEQUAL);
        //             render.Enable(RENDER_ZWRITE, false);
        //             render.Enable(RENDER_ALPHABLEND, true);
        //             render.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_DESTALPHA);
        //         
        //             LightNode*const* _lights = &lights[0];
        //             for(a_uint32 i = 0; i < maxLights; i++)
        //             {
        //                 LightNode* l = _lights[i];
        //                 l->GetLightModel()->Bind();
        //                 //sc->Render(RENDERPASS_FORWARD_LIGHTING);
        //             }
        //             m_framebuffer->UnBind();
        //             render.Enable(RENDER_ALPHABLEND, false);
        //         }
        /*
            Render to main framebuffer
        */
        //render.Enable(RENDER_ZTEST,false);
        //Texture::TextureRender(m_textureBuffer[0]);

        /*if(maxLights)
        {
            render.Enable(RENDER_ALPHABLEND, true);
            render.SetupAlphaBlending(BLEND_DESTCOLOR, BLEND_ZERO);
            Texture::TextureRender(m_textureBuffer[1]);
            render.Enable(RENDER_ALPHABLEND, false);
        }*/
        //end();
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
