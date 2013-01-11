#include <Core/SceneObject/Scene.h>
#include <Core/SceneObject/Model.h>
#include <Core/SceneObject/Terrain.h>
#include <Core/SceneObject/Water.h>
#include <Core/SceneObject/Sky.h>
#include <Core/Renderer.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Tools/Fast2DSurface.h>
#define _USE_MATH_DEFINES
#include <math.h>
namespace Agmd
{
#define SHADOWMAP_SIZE 4096

    Scene::Scene() : 
    m_deltaTime(0),
    m_Sky(NULL)    
    {
        m_shadowmapping_fbo = Renderer::Get().CreateFrameBuffer();
        m_shadowMap.Create(ivec2(SHADOWMAP_SIZE),PXF_DEPTH,TEXTURE_2D, TEX_NOMIPMAP);
        m_debugMap.Create(ivec2(SHADOWMAP_SIZE),PXF_A8R8G8B8,TEXTURE_2D, TEX_NOMIPMAP);
        //m_shadowmapping_fbo->setTexture(m_debugMap,COLOR_ATTACHMENT);
        m_shadowmapping_fbo->setTexture(m_shadowMap,DEPTH_ATTACHMENT);
        m_shadowmapping_fbo->DrawBuffer(0);
        m_shadowShader.LoadFromFile("Shader/shadowmap.glsl");
        
        m_light_dir = vec3(0.5f,2,2);

        m_matShadow = glm::ortho<float>(-100,100,-100,100,-100,100);
        m_matShadow = m_matShadow*lookAt(m_light_dir,vec3(0),vec3(0,0,1));

        m_light_angle = 0.0f;

        m_renderBuffer = Renderer::Get().CreateFrameBuffer();
        RenderBuffer* depthBuffer = Renderer::Get().CreateRenderBuffer(Renderer::Get().GetScreen(),PXF_DEPTH);
        for(int i = 0; i < 4; i++)
            m_renderTexture[i].Create(Renderer::Get().GetScreen(),PXF_A8R8G8B8,TEXTURE_2D, TEX_NOMIPMAP);
        m_renderBuffer->setRender(depthBuffer, DEPTH_ATTACHMENT);
    }

    Scene::~Scene()
    {}
    void Scene::Prepare()
    {
        for(uint32 i = 0; i < m_vWaters.size(); i++)
            m_vWaters[i]->prepare();

        //GenerateShadowMap();
    }

    void Scene::GenerateShadowMap()
    {

    }

    void Scene::Render(TRenderPass pass) const
    {
        
        for(uint32 i = 0; i < m_vModels.size(); i++)
            m_vModels[i]->Render(pass);

        /*if(flag & SC_APPLY_LIGHTING)
            RenderLightingPass(flag & ~(SC_DRAW_SKY | SC_DRAW_WATER));

        if(flag & SC_APPLY_SHADOW)
            RenderShadowPass(flag & ~(SC_DRAW_SKY | SC_DRAW_WATER));

        //Renderer::Get().Enable(RENDER_ZWRITE, false);
        Texture::TextureRender(m_renderTexture[0]);
        //Renderer::Get().Enable(RENDER_ZWRITE, true);*/
    }

    void Scene::Draw() const
    {
        /*if(flag == SC_NOOPTION)
            return;

        if(flag & SC_DRAW_MODEL)
        {
            for(uint32 i = 0; i < m_vModels.size(); i++)
                m_vModels[i]->Draw();
        }

        if(flag & SC_DRAW_TERRAIN)
        {
            for(uint32 i = 0; i < m_vMaps.size(); i++)
                m_vMaps[i]->Draw();
        }

        if(flag & SC_DRAW_WATER)
        {
            for(uint32 i = 0; i < m_vWaters.size(); i++)
                m_vWaters[i]->Draw();
        }

        if(flag & SC_DRAW_SKY && m_Sky)
            m_Sky->Draw();
            */
    }

    void Scene::RenderDiffusePass(uint32 flag) const
    {
        /*m_renderBuffer->setTexture(m_renderTexture[0],COLOR_ATTACHMENT);
        m_renderBuffer->Clear();
        m_renderBuffer->Bind();
        for(uint32 i = 0; i < m_vModels.size(); i++)
            m_vModels[i]->Render();
        m_renderBuffer->UnBind();*/

    }

    void Scene::RenderLightingPass(uint32 flag) const
    {
/*        Renderer& render = Renderer::Get();
        uint32 count = m_lights.size();
        m_renderBuffer->setTexture(m_renderTexture[1],COLOR_ATTACHMENT);
        m_renderBuffer->Clear();
        m_renderBuffer->setTexture(m_renderTexture[2],COLOR_ATTACHMENT);
        m_renderBuffer->Clear();
        for(uint32 i = 0; i < count; i++)
        {
            m_renderBuffer->Bind();
            m_lights[i]->Begin();
            Draw(flag);
            m_lights[i]->End();
            m_renderBuffer->UnBind();
            
            Texture::TextureAdd(m_renderTexture[1], m_renderTexture[1], m_renderTexture[2]);
        }*/
        //Texture::TextureProd(m_renderTexture[0],m_renderTexture[0],m_renderTexture[1]);
    }

    void Scene::RenderShadowPass(uint32 flag) const
    {

    }

    #define MODULO_FLOAT(a,x) ((a)-(x)*(int)((a)/(x)))
    void Scene::Update(uint64 t_diff)
    {
        m_deltaTime = t_diff;
        m_light_angle += (float)M_PI*2*(t_diff/10000.0f);
        m_light_angle = MODULO_FLOAT(m_light_angle,(float)M_PI*2);
        m_light_dir = normalize(vec3(cos(m_light_angle),sin(m_light_angle),0.5));

        mat4 bias(
            0.5, 0.0, 0.0, 0.0, 
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
        );
        m_matShadow = glm::ortho<float>(-100, 100, -100, 100, -100, 100);
        m_matShadow = m_matShadow*lookAt(m_light_dir*3.0F,vec3(0),vec3(0,0,1));
        mat4 bmvp = bias*m_matShadow;

        Renderer::Get().SetCurrentProgram(NULL);
        Renderer::Get().getPipeline()->SetParameter("light",m_light_dir);
        Renderer::Get().getPipeline()->SetParameter("depthMVP",bmvp);
        Renderer::Get().SetTexture(10,m_shadowMap.GetTexture());
    }

    void Scene::AddModel(Model* m)
    {
        m_vModels.push_back(m);
    }

    void Scene::AddTerrain(Terrain* t)
    {
        m_vMaps.push_back(t);
    }

    void Scene::AddWater(Water* w)
    {
        m_vWaters.push_back(w);
    }

    void Scene::AddLight(Light* l)
    {
        m_lights.push_back(l);
    }

    void Scene::SetSky(Sky* _Sky)
    {
        m_Sky = _Sky;
    }

    Sky* Scene::GetSky()
    {
        return m_Sky;
    }

    void Scene::RemoveModel(Model* m)
    {
        for(uint32 i = 0; i < m_vModels.size(); i++)
        {
            if(m_vModels[i] == m)
            {
                m_vModels.erase(m_vModels.begin()+i);
                break;
            }
        }
    }

    void Scene::RemoveTerrain(Terrain* t)
    {
        for(uint32 i = 0; i < m_vMaps.size(); i++)
        {
            if(m_vMaps[i] == t)
            {
                m_vMaps.erase(m_vMaps.begin()+i);
                break;
            }
        }
    }

    void Scene::RemoveWater(Water* w)
    {
        for(uint32 i = 0; i < m_vWaters.size(); i++)
        {
            if(m_vWaters[i] == w)
            {
                m_vWaters.erase(m_vWaters.begin()+i);
                break;
            }
        }
    }

    void Scene::RenderShadow() const
    {
        mat4 lightProjection, lightModelView;
        mat4 oldProjection, oldView;
        Renderer& render = Renderer::Get();

        oldProjection = render.GetMatProjection();
        oldView = render.GetMatView();

        render.SetViewPort(ivec2(0),ivec2(SHADOWMAP_SIZE));
        render.SetCullFace(2);
        m_shadowmapping_fbo->Clear();
        m_shadowmapping_fbo->Bind();
        render.SetCurrentProgram(m_shadowShader.GetShaderProgram());
        render.getPipeline()->SetParameter("depthMVP",m_matShadow);
        //Draw(SC_DRAW_MODEL);
        render.SetCurrentProgram(NULL);
        m_shadowmapping_fbo->UnBind();
        render.SetCullFace(1);
        render.SetMatProjection(oldProjection);
        render.SetMatView(oldView);
        Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
    }

    Texture    Scene::getShadowMap()
    {
        return m_renderTexture[0];
    }

    std::vector<Light*> Scene::GetLights()
    {
        return m_lights;
    }
}