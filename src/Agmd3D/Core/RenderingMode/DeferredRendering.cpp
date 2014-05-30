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
#include <Core/SceneObject/SceneMgr.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/Effects/PostEffectMgr.h>

namespace Agmd
{
    DeferredRendering::DeferredRendering(int width, int height) :
    RenderingMode(width,height)
    {
        Init();
    }

    DeferredRendering::DeferredRendering(ivec2& screen) :
    RenderingMode(screen)
    {
        Init();
    }

    DeferredRendering::~DeferredRendering()
    {
        if(bufferFlags)
            delete bufferFlags;
        delete m_shadowRender;
    }

    void DeferredRendering::Init()
   {
        Driver& render = Driver::Get();
        m_framebuffer = render.CreateFrameBuffer();
        m_depthbuffer = render.CreateRenderBuffer(m_screen, PXF_DEPTH);
        m_colorbuffer = render.CreateRenderBuffer(m_screen, PXF_A8R8G8B8);
        m_normalbuffer = render.CreateRenderBuffer(m_screen, PXF_R16G16B16);
        m_positionbuffer = render.CreateRenderBuffer(m_screen, PXF_R32G32B32);

        m_textureBuffer[0].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[1].Create(m_screen, PXF_R16G16B16, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[2].Create(m_screen, PXF_R32G32B32, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[3].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[4].Create(m_screen, PXF_A8R8G8B8, TEXTURE_2D, TEX_NOMIPMAP);
        m_textureBuffer[5].Create(m_screen,PXF_DEPTH,TEXTURE_2D,TEX_NOMIPMAP);
        //m_depthCubemap.Create(ivec2(1024),PXF_R32G32B32,TEXTURE_CUBE,TEX_NOMIPMAP,"depth_cubemap");
        m_framebuffer->SetRender(m_depthbuffer, DEPTH_ATTACHMENT);
        m_framebuffer->SetRender(m_colorbuffer, COLOR_ATTACHMENT);
        m_framebuffer->SetRender(m_normalbuffer, COLOR_ATTACHMENT+1);
        m_framebuffer->SetRender(m_positionbuffer, COLOR_ATTACHMENT+2);

        m_framebuffer->SetTexture(m_textureBuffer[0], COLOR_ATTACHMENT);
        m_framebuffer->SetTexture(m_textureBuffer[1], COLOR_ATTACHMENT+1);
        m_framebuffer->SetTexture(m_textureBuffer[2], COLOR_ATTACHMENT+2);
        m_framebuffer->SetTexture(m_textureBuffer[5],DEPTH_ATTACHMENT);
        a_uint32 buffer[] = {COLOR_ATTACHMENT, COLOR_ATTACHMENT+1, COLOR_ATTACHMENT+2};
        bufferFlags = m_framebuffer->GenerateBufferFlags(3,buffer);
        m_light_program[DIRECTIONNAL].LoadFromFile("Shader/RenderingShader/DeferredDirLightShader.glsl");
        m_light_program[SPOT].LoadFromFile("Shader/RenderingShader/DeferredSpotLightShader.glsl");
        m_light_program[DIRECTIONNAL_WITH_SHADOW].LoadFromFile("Shader/RenderingShader/DeferredDirLightShaderWS.glsl");
        m_light_program[SPOT_WITH_SHADOW].LoadFromFile("Shader/RenderingShader/DeferredSpotLightShaderWS.glsl");
        m_shadowRender = new ShadowMapRenderer(ivec2(2048));
    }


    void DeferredRendering::Compute()
    {
        Driver& render = Driver::Get();
		render.SetViewPort(ivec2(),render.GetScreen());
        SceneMgr* sc = render.GetActiveScene();
		
        const std::vector<Light*>& lights = sc->GetLights();

        const Light*const*  t = &lights[0];
        
        Light ** test = (Light**)((int)t);
        
        
        a_uint32 maxLights = lights.size();

        Start();
        render.SetRenderMode(m_mode);
		SkyBox* box = sc->GetSkyBox();
		render.SetCullFace(1);
		if(box)
		{
			render.Enable(RENDER_ZWRITE,false);
			box->Render();
		}
		sc->Update();
		sc->Compute();
		/*if(sc->isEmpty())
		{
			End();
			return;
		}*/
		render.SetCullFace(0);
        render.Enable(RENDER_ZWRITE,true);
        m_framebuffer->Clear(CLEAR_DEPTH);
        m_framebuffer->DrawBuffer(0);
        m_framebuffer->Bind();
        render.Enable(RENDER_ZTEST,true);
        render.SetupDepthTest(DEPTH_LESS);
        sc->Render(TRenderPass::RENDERPASS_ZBUFFER);

        m_framebuffer->DrawBuffers(3, bufferFlags);
        m_framebuffer->Clear(CLEAR_COLOR);
        m_framebuffer->Bind();
        render.SetupDepthTest(DEPTH_LEQUAL);
        render.Enable(RENDER_ZWRITE,false);
        sc->Render(TRenderPass::RENDERPASS_DEFERRED);
        m_framebuffer->UnBind();


        render.Enable(RENDER_ZTEST,false);
        
        render.SetRenderMode(MODE_FILL);
        //if(PostEffectMgr::Instance().HaveEffect())
        

        if(maxLights)
        {
            //render.Enable(RENDER_ALPHABLEND, true);
            //render.SetupAlphaBlending(BLEND_SRCCOLOR, BLEND_DESTCOLOR);
            for(a_uint32 i = 0; i < maxLights; i++)
            {
                render.SetCurrentProgram(m_light_program[lights[i]->GetType()].GetShaderProgram());
                if(false)//if shadow is enable
				{
					//Re-enable Z-Test for making shadow cast
					render.Enable(RENDER_ZTEST,true);
					render.Enable(RENDER_ZWRITE,true);
					render.SetupDepthTest(DEPTH_LESS);
					lights[i]->Bind();
					m_shadowRender->Reset();
					m_shadowRender->BeginLight(lights[i]);
					sc->Draw();
					m_shadowRender->EndLight();
				}
                //Disable Z-Test for light rendering
                render.SetupDepthTest(DEPTH_LEQUAL);
                render.Enable(RENDER_ZWRITE,false);
                render.Enable(RENDER_ZTEST,false);
                render.SetTexture(0,m_textureBuffer[0].GetTexture());
                render.SetTexture(1,m_textureBuffer[1].GetTexture());
                render.SetTexture(2,m_textureBuffer[2].GetTexture());
                render.SetCurrentProgram(m_light_program[lights[i]->GetType()/*+3 for use with SHADOW*/].GetShaderProgram());
                //m_shadowRender->SetupForRendering();
                Texture::BeginRenderToTexture(m_textureBuffer[3]);
                Fast2DSurface::Instance().Draw();
            }
            render.SetCurrentProgram(NULL);
            render.Enable(RENDER_ALPHABLEND, false);
            Texture::EndRenderToTexture();
        }else
        {
            Texture::TextureRender(m_textureBuffer[0]);
            End();
            return;
        }
        if(PostEffectMgr::Instance().HaveEffect())
        {
            PostEffectMgr::Instance().ApplyEffect(m_textureBuffer[3],m_textureBuffer[4]);
            Texture::TextureRender(m_textureBuffer[4]);
        }
        else
        {
           Texture::TextureRender(m_textureBuffer[3]);
        }
            

        End();
    }

    void DeferredRendering::Start()
    {}

    void DeferredRendering::End()
    {}

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

    ShadowMapRenderer* DeferredRendering::GetShadowRenderer()
    {
        return m_shadowRender;
    }


}