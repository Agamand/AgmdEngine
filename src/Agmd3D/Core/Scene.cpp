#include <Core/Scene.h>
#include <Core/Model.h>
#include <Core/Terrain.h>
#include <Core/Water.h>
#include <Core/Sky.h>
#include <Core/Renderer.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>

namespace Agmd
{
#define SHADOWMAP_SIZE 1024

	Scene::Scene() : 
	m_fTime(0.0f),
	m_Sky(NULL)	
	{
		m_shadowmapping_fbo = Renderer::Get().CreateFrameBuffer();
		m_depth_rbo = Renderer::Get().CreateRenderBuffer(ivec2(SHADOWMAP_SIZE),PXF_DEPTH);
		m_shadowMap.Create(ivec2(SHADOWMAP_SIZE),PXF_DEPTH,TEXTURE_2D, TEX_NOMIPMAP);
		m_debugMap.Create(ivec2(SHADOWMAP_SIZE),PXF_A8R8G8B8,TEXTURE_2D, TEX_NOMIPMAP);
		m_shadowmapping_fbo->setTexture(m_shadowMap,DEPTH_ATTACHMENT);
		m_shadowmapping_fbo->setTexture(m_debugMap,COLOR_ATTACHMENT);
		m_shadowmapping_fbo->setRender(m_depth_rbo,DEPTH_ATTACHMENT);
	}

	Scene::~Scene()
	{}

	void Scene::Draw(uint32 flag) const
	{
		if(flag == SC_NODRAWING)
			return;

		if(flag & SC_DRAW_SHADOW)
			RenderShadow();

		if(flag & SC_DRAW_MODEL)
		{
			for(uint32 i = 0; i < m_vModels.size(); i++)
				m_vModels[i]->Render();
		}

		if(flag & SC_DRAW_TERRAIN)
		{
			for(uint32 i = 0; i < m_vMaps.size(); i++)
				m_vMaps[i]->Render();
		}

		if(flag & SC_DRAW_WATER)
		{
			for(uint32 i = 0; i < m_vWaters.size(); i++)
				m_vWaters[i]->Render();
		}

		if(flag & SC_DRAW_SKY && m_Sky)
			m_Sky->Render();

	}

	void Scene::Update(uint64 t_diff)
	{
		m_fTime += t_diff/1000.0f;
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

		render.SetViewPort(ivec2(0),ivec2(1024));
		lightProjection = perspective(45.0f, 1.0f, 0.125f, 512.0f);
		lightModelView = lookAt(vec3(1),vec3(0),vec3(0,0,1));
	
		//render.SetMatProjection(lightProjection);
		//render.SetMatView(lightModelView);

		//render.SetCullFace(1);
		m_shadowmapping_fbo->Clear();
		m_shadowmapping_fbo->Bind();
		Draw(SC_DRAW_MODEL);
		m_shadowmapping_fbo->UnBind();
		//render.SetCullFace(0);
		render.SetMatProjection(oldProjection);
		render.SetMatView(oldView);
		Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
	}
}