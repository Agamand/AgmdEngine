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
#include <Core/Driver.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Tools/Fast2DSurface.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{


    Scene::Scene() : 
    m_SkyBox(NULL)    
    {}

    Scene::~Scene()
    {}


    void Scene::Render(TRenderPass pass) const
    {
        Displayable* const* mesh = &m_vMesh[0];
        a_uint32 max = m_vMesh.size();
        for(a_uint32 i = 0; i < max; i++)
            mesh[i]->Render(pass);
    }

    void Scene::Draw() const
    {
        Displayable* const* mesh = &m_vMesh[0];
        a_uint32 max = m_vMesh.size();
        for(a_uint32 i = 0; i < max; i++)
            mesh[i]->Draw();
    }

    void Scene::Update(a_uint64 t_diff)
    {}

    void Scene::AddMesh(Displayable* m)
    {
        m_vMesh.push_back(m);
    }


    void Scene::AddLight(Light* l)
    {
        m_lights.push_back(l);
    }

    void Scene::SetSkyBox(SkyBox* _Sky)
    {
        m_SkyBox = _Sky;
    }

    SkyBox* Scene::GetSkyBox()
    {
        return m_SkyBox;
    }

    void Scene::RemoveMesh(Displayable* m)
    {
        for(a_uint32 i = 0; i < m_vMesh.size(); i++)
        {
            if(m_vMesh[i] == m)
            {
                m_vMesh.erase(m_vMesh.begin()+i);
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