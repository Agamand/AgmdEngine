/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

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


    Scene::Scene() : 
    m_deltaTime(0),
    m_Sky(NULL)    
    {}

    Scene::~Scene()
    {}
    void Scene::Prepare()
    {
        // <!> unused <!>
        /*for(uint32 i = 0; i < m_vWaters.size(); i++)
            m_vWaters[i]->prepare();

        */
    }


    void Scene::Render(TRenderPass pass) const
    {
        Model* const* models = &m_vModels[0];
        uint32 max = m_vModels.size();
        for(uint32 i = 0; i < max; i++)
            models[i]->Render(pass);
    }

    void Scene::Draw() const
    {}

    void Scene::Update(uint64 t_diff)
    {}

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

    /*
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
        render.GetCurrentProgram()->SetParameter("depthMVP",m_matShadow);
        //Draw(SC_DRAW_MODEL);
        render.SetCurrentProgram(NULL);
        m_shadowmapping_fbo->UnBind();
        render.SetCullFace(1);
        render.SetMatProjection(oldProjection);
        render.SetMatView(oldView);
        Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
       
    }
    */

    const std::vector<Light*>& Scene::GetLights()
    {
        return m_lights;
    }
}