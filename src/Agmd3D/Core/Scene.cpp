#include <Core/Scene.h>
#include <Core/Model.h>
#include <Core/Terrain.h>
#include <Core/Water.h>
#include <Core/Sky.h>

namespace Agmd
{

	Scene::Scene() : 
	m_fTime(0.0f),
	m_Sky(NULL)	
	{}

	Scene::~Scene()
	{}

	void Scene::Draw(uint32 flag) const
	{
		if(flag == SC_NODRAWING)
			return;

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
}