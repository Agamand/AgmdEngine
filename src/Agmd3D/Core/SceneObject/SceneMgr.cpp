#include <Core/SceneObject/SceneMgr.h>
#include <Core/Driver.h>

namespace Agmd
{
	SceneMgr::SceneMgr() : m_skybox(NULL)
	{
		m_root = new SceneNode(ROOT_NODE,NULL);
	}

	void SceneMgr::Render( TRenderPass pass ) const
	{
		for(std::vector<DisplayNode*>::const_iterator itr= m_displayable.begin(); itr != m_displayable.end(); itr++)
		{
			(*itr)->Render(pass);
		}
		for(a_uint32 i = 0, len =m_displayable.size(); i < len;i++)
			m_displayable[i]->Render(pass);
	}

	void SceneMgr::Draw() const
	{
		for(a_uint32 i = 0, len =m_displayable.size(); i < len;i++)
			m_displayable[i]->Draw();
	}

	void SceneMgr::Compute()
	{
		a_vector<LightNode*> light;
		m_displayable.clear();
		
		FindVisible(m_displayable,light);
	}

	void SceneMgr::Update()
	{
		m_root->Update(NULL,true,false);
	}

	void SceneMgr::FindVisible( a_vector<DisplayNode*>& displayable,std::vector<LightNode*>& light)
	{
		m_root->FindVisible(Camera::GetCurrent(CAMERA_3D),displayable,light);
	}

	void SceneMgr::AddNode( SceneNode *node )
	{
		m_root->AddChild(node);
	}

	const a_vector<Light*>& SceneMgr::GetLights()
	{
		return m_light;
	}

	void SceneMgr::AddLight( Light* l )
	{
		m_light.push_back(l);
	}

	void SceneMgr::SetSkybox( SkyBox* skybox )
	{
		m_skybox = skybox;
	}

	SkyBox* SceneMgr::GetSkyBox()
	{
		return m_skybox;
	}

	void SceneMgr::clear()
	{
		m_root->clear();
	}

}
