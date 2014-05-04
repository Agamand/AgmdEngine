#include <Core/ShadowMapRenderer.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
    mat4 ShadowMapRenderer::bias = mat4(
                                        0.5, 0.0, 0.0, 0.0,
                                        0.0, 0.5, 0.0, 0.0,
                                        0.0, 0.0, 0.5, 0.0,
                                        0.5, 0.5, 0.5, 1.0
                                        );

    mat4 ShadowMapRenderer::s_lookupMatrix[] = {
    lookAt(vec3(0,0,0),vec3(1,0,0),vec3(0,0,1)),
    lookAt(vec3(0,0,0),vec3(-1,0,0),vec3(0,0,1)),
    lookAt(vec3(0,0,0),vec3(0,1,0),vec3(0,0,1)),
    lookAt(vec3(0,0,0),vec3(0,-1,0),vec3(0,0,1)),
    lookAt(vec3(0,0,0),vec3(0,0,1),vec3(-1,0,0)),
    lookAt(vec3(0,0,0),vec3(0,0,-1),vec3(1,0,0))};
    ShadowMapRenderer::ShadowMapRenderer(const ivec2& size) :
    m_currentDepth(0),
    m_shadowSize(size),
    m_currentLight(NULL),
    m_offset(0.05f),
    m_bias(-0.005f)
    {
        for(int i = 0; i < 6; i++)
            m_depth[i].Create(m_shadowSize,PXF_DEPTH,TEXTURE_2D,TEX_NOMIPMAP);
        m_framebuffer = Driver::Get().CreateFrameBuffer();
        RenderBuffer* color_test = Driver::Get().CreateRenderBuffer(m_shadowSize,PXF_R16G16B16);
        m_framebuffer->SetTexture(m_depth[0],DEPTH_ATTACHMENT);
        m_framebuffer->SetRender(color_test,COLOR_ATTACHMENT);
        //m_framebuffer->DrawBuffer(0);
        m_shadowcast.LoadFromFile("Shader/RenderingShader/ShadowCastShader.glsl");
    }

    ShadowMapRenderer::~ShadowMapRenderer()
    {
        delete m_framebuffer;
    }

    void ShadowMapRenderer::Reset()
    {
        m_framebuffer->Clear(CLEAR_DEPTH);
    }

    void ShadowMapRenderer::BeginLight(Light* l)
    {
        Driver::Get().SetCurrentProgram(m_shadowcast.GetShaderProgram());
        m_currentLightType = l->GetType();
        if(m_currentDepth)
            SetDepth(0);
        m_framebuffer->Bind();
        Driver::Get().SetViewPort(ivec2(0),ivec2(m_shadowSize));
        if(m_currentLightType == LightType::LIGHT_DIR)
        {
            mat4 proj = ortho<float>(-1000,1000,-1000,1000,-100,5000);
            m_shadow_matrix[0] = proj*lookAt(l->GetDirection()*1000.0f,vec3(0),vec3(0,0,1));
        

        }else if(m_currentLightType == LightType::LIGHT_POINT)
        {
            ivec2 screen = Driver::Get().GetScreen();
            float aspect = screen.x/((float)screen.y);
            mat4 proj = perspective(90.0f,aspect,1.0f,l->GetRange());
            m_shadow_matrix[0] = proj*lookAt(l->GetPosition(),vec3(1,0,0),vec3(0,0,1));

        }else
        {
            ivec2 screen = Driver::Get().GetScreen();
            float aspect = screen.x/((float)screen.y);
            mat4 proj = perspective(acos(l->GetOuterAngle())*180.0f/(float)M_PI*2.0f,aspect,1.0f,l->GetRange());
            m_shadow_matrix[0] = proj*lookAt(l->GetPosition(),l->GetPosition()-l->GetDirection(),vec3(0,0,1));
        }
        Driver::Get().GetCurrentProgram()->SetParameter("depthMVP",m_shadow_matrix[0]);
        //Renderer::Get().SetCullFace(1);
    }


    /*
    ONLY for Omni directionnal light like point light
    */

    void ShadowMapRenderer::SetDepth(int face)
    {
        if(face < 0 || face > 5)
            return;

        m_currentDepth = face;
        m_framebuffer->SetTexture(m_depth[face],DEPTH_ATTACHMENT);
        m_framebuffer->Bind();
        ivec2 screen = Driver::Get().GetScreen();
        float aspect = screen.x/((float)screen.y);
        mat4 proj = perspective(90.0f,aspect,1.0f,m_currentLight->GetRange());
    }

    void ShadowMapRenderer::EndLight()
    {
        Driver::Get().SetViewPort(ivec2(0),Driver::Get().GetScreen());
        Driver::Get().SetCurrentProgram(NULL);
        m_framebuffer->UnBind();
        //Renderer::Get().SetCullFace(2);
    }

    void ShadowMapRenderer::SetupForRendering()
    {
        
        if(m_currentLightType == LightType::LIGHT_POINT)
        {
            mat4 VPB[6];
            for(int i = 0; i < 6; i++)
            {
                VPB[i] = bias*m_shadow_matrix[i];
                Driver::Get().SetTexture(3+i,m_depth[i].GetTexture());
            }
            Driver::Get().GetCurrentProgram()->SetParameter("depthVPBias",VPB,6);

        }else
        {
            mat4 VPB = bias*m_shadow_matrix[0];
            Driver::Get().GetCurrentProgram()->SetParameter("depthVPBias",VPB);
            Driver::Get().SetTexture(3,m_depth[0].GetTexture());
        }
        Driver::Get().GetCurrentProgram()->SetParameter("u_offset", m_offset);
        Driver::Get().GetCurrentProgram()->SetParameter("u_bias", m_bias);
    }

    void ShadowMapRenderer::SetOffset(float offset)
    {
        m_offset = offset;
    }

    void ShadowMapRenderer::SetBias(float bias)
    {
        m_bias = bias;
    }

    Texture& ShadowMapRenderer::GetShadowDepth()
    {
        return m_depth[0];
    }
}
