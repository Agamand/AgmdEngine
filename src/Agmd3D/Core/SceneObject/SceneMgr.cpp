#include <Core/SceneObject/SceneMgr.h>
#include <Core/Driver.h>

namespace Agmd
{
	SceneMgr::SceneMgr() : m_skybox(NULL)
	{
		m_root = new SceneNode(ROOT_NODE,NULL);
	}

	void SceneMgr::Render( TRenderPass pass, RenderQueue::TRenderType type /*= TYPE_DIFFUSE*/ ) const
	{
		if(type < 0 || type >= MAX_TYPE)
			return;

		for(a_uint32 i = 0, len =m_renderQueue.m_displayable[type].size(); i < len;i++)
			m_renderQueue.m_displayable[type][i]->render(pass);
	}

	void SceneMgr::Draw( RenderQueue::TRenderType type /*= RenderQueue::TRenderType::TYPE_DIFFUSE*/ ) const
	{
		for(a_uint32 i = 0, len =m_renderQueue.m_displayable[type].size(); i < len;i++)
			m_renderQueue.m_displayable[type][i]->draw();
	}

	void SceneMgr::Compute()
	{
		a_vector<LightNode*> light;
		m_renderQueue.clear();
		
		FindVisible(m_renderQueue,light);
	}

	void SceneMgr::Update()
	{
		m_root->update(NULL,true,false);
	}

	void SceneMgr::FindVisible( RenderQueue& displayable,std::vector<LightNode*>& light)
	{
		m_root->findVisible(Camera::getCurrent(CAMERA_3D),displayable,light);
	}

	void SceneMgr::AddNode( SceneNode *node )
	{
		m_root->addChild(node);
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
