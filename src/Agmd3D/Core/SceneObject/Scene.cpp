#include <Core/SceneObject/Scene.h>
#include <Core/SceneObject/Model.h>
#include <Core/SceneObject/Terrain.h>
#include <Core/SceneObject/Water.h>
#include <Core/SceneObject/Sky.h>
#include <Core/Renderer.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <regex>
#define _USE_MATH_DEFINES
#include <math.h>
namespace Agmd
{
#define SHADOWMAP_SIZE 1024

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
		Renderer::Get().SetTexture(10,m_shadowMap.GetTexture());
		m_light_angle = 0.0f;
	}

	Scene::~Scene()
	{}
	void Scene::Prepare()
	{
		for(uint32 i = 0; i < m_vWaters.size(); i++)
			m_vWaters[i]->prepare();
	}

	void Scene::Render(uint32 flag) const
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

	void Scene::Draw(uint32 flag) const
	{
		if(flag == SC_NODRAWING)
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

	}
	#define MODULO_FLOAT(a,x) ((a)-(x)*(int)((a)/(x)))
	void Scene::Update(uint64 t_diff)
	{
		m_deltaTime = t_diff;
		m_light_angle += (float)M_PI*2*(t_diff/10000.0f);
		m_light_angle = MODULO_FLOAT(m_light_angle,(float)M_PI*2);
		m_light_dir = normalize(vec3(cos(m_light_angle),sin(m_light_angle),1));
		m_matShadow = glm::ortho<float>(-10,10,-10,10,-10,20);
		m_matShadow = m_matShadow*lookAt(normalize(m_light_dir),vec3(0),vec3(0,0,1));
		Renderer::Get().SetCurrentProgram(NULL);
		Renderer::Get().getPipeline()->SetParameter("light",m_light_dir);
		Renderer::Get().getPipeline()->SetParameter("depthMVP",m_matShadow);
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

		render.SetViewPort(ivec2(0),ivec2(SHADOWMAP_SIZE));
		mat4 depthMVP = glm::ortho<float>(-10,10,-10,10,-10,20);//perspective(45.0f, 1.0f, 0.125f, 512.0f);
		depthMVP *= lookAt(-normalize(m_light_dir),vec3(0),vec3(0,0,1));
		render.SetCullFace(1);
		m_shadowmapping_fbo->Clear();
		m_shadowmapping_fbo->Bind();
		render.SetCurrentProgram(m_shadowShader.GetShaderProgram());
		render.getPipeline()->SetParameter("depthMVP",depthMVP);
		Draw(SC_DRAW_MODEL);
		render.SetCurrentProgram(NULL);
		m_shadowmapping_fbo->UnBind();
		render.SetCullFace(1);
		render.SetMatProjection(oldProjection);
		render.SetMatView(oldView);
		Renderer::Get().SetViewPort(ivec2(0),Renderer::Get().GetScreen());
	}

	Texture	Scene::getShadowMap()
	{
		return m_shadowMap;
	}
}