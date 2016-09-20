#include <Core/AgmdApplication.h>
#include <Editor/EditorFrame.h>
#include <Core/Model/SceneMgr.h>
#include <Core/Driver.h>


namespace Agmd
{
    SceneMgr::SceneMgr() : m_skybox(NULL)
    {
        
#if defined(USE_WX) && defined(USE_EDITOR)

        m_frame = AgmdApplication::getApplication()->getWxFrame();
#endif    
        m_root = new RootNode(this);
    }

    void SceneMgr::Render( TRenderPass pass, TRenderType type /*= TYPE_DIFFUSE*/ ) const
    {
        if(type < 0 || type >= MAX_TYPE)
            return;

        for(a_uint32 i = 0, len =m_renderQueue.m_displayable[type].size(); i < len;i++)
            m_renderQueue.m_displayable[type][i]->render(pass);
    }

    void SceneMgr::Draw( TRenderType type /*= RenderQueue::TRenderType::TYPE_DIFFUSE*/ ) const
    {
        for(a_uint32 i = 0, len =m_renderQueue.m_displayable[type].size(); i < len;i++)
            m_renderQueue.m_displayable[type][i]->draw();
    }

    void SceneMgr::Compute()
    {
        m_lights.clear();
        m_renderQueue.clear();
        
        FindVisible(m_renderQueue,m_lights);

        for(auto i = 0; i <m_lights.size() && i < MAX_LIGHT; ++i)
        {
            m_lights[i]->GetLightModel()->FillBuffer(m_lightBuffer+i);
        }
    }

    void SceneMgr::Update()
    {
        a_uint32 time = AgmdApplication::getApplication()->getDeltaTime();
        m_root->update(NULL,time,UPDATE_CHILDREN);
    }

    void SceneMgr::FindVisible( RenderQueue& displayable,std::vector<LightNode*>& light)
    {
        m_root->findVisible(Camera::getCurrent(CAMERA_3D),displayable,light);
    }

    void SceneMgr::AddNode( SceneNode *node )
    {
        m_root->addChild(node);
    }

	void SceneMgr::RemoveNode(SceneNode *node)
	{
		m_root->removeChild(node);
	}

    const a_vector<Light*>& SceneMgr::GetLights()
    {
        return m_light;
    }

    void SceneMgr::AddLight( Light* l )
    {
       // m_light.push_back(l);
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

    void SceneMgr::__addNode( SceneNode* node)
    {
#if defined(USE_WX) && defined(USE_EDITOR)

        EditorFrame* frame =  (EditorFrame*)m_frame;
        frame->__addNode(node);
#endif    
    }

    void SceneMgr::__removeNode( SceneNode* node)
    {
#if defined(USE_WX) && defined(USE_EDITOR)

        EditorFrame* frame =  (EditorFrame*)m_frame;
        frame->__removeNode(node);
#endif    
    }

    Light::LightBuffer* SceneMgr::GetLightBuffer()
    {
        return m_lightBuffer;
    }

    const a_vector<LightNode*>& SceneMgr::GetLightNodes()
    {
        return m_lights;
    }

}
