
#include <Core/SceneNode/DisplayNode.h>
#include <Core/Model/Material.h>
#include <Core/ResourceManager.h>

namespace Agmd
{

    DisplayNode::DisplayNode( Transform* t,Material*mat ) : SceneNode(DISPLAYABLE_NODE,t)
    {
        if(!mat)
            m_material = ResourceManager::Instance().Get<Material>("DEFAULT_MATERIAL");
        else
            m_material = mat;
        
    }    

    bool DisplayNode::isVisible( BoundingSphere& bbox )
    {
        return true;
    }

    void DisplayNode::findVisible( Camera*cam, RenderQueue& display, a_vector<LightNode*>& light )
    {
        if(cam->isInFrustrum(m_globalBounds))
            display.push_back(this,m_material->GetRenderQueue());

        SceneNode::findVisible(cam,display,light);
    }

    bool DisplayNode::update( Transform* transform, a_uint32 time, a_uint32 updateFlags )
    {
        bool transformUpdate = SceneNode::update(transform,time,updateFlags);
        
        if(transformUpdate) // need implement : m_baseBbox = modelbbox + (all children bbox), actually is only m_baseBbox = modelbbox
        {
            m_localBounds = m_baseBounds.GetTransformedBounding(m_transform->localModelMatrix());
            m_globalBounds = m_baseBounds.GetTransformedBounding(m_transform->modelMatrix());
//             m_localBounds.mult( m_transform->localModelMatrix(),m_baseBounds);
//             m_globalBounds.mult( m_transform->modelMatrix(),m_baseBounds);
        }
        return transformUpdate;
    }

}

