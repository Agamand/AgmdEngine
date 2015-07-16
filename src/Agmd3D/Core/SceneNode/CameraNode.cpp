
#include <Core/SceneNode/CameraNode.h>
#include <Core/Controller/InputController.h>

#include <Core/AgmdApplication.h>


namespace Agmd
{

    CameraNode::CameraNode(Camera* camera, InputController* c/*= NULL*/,Transform* t /*= NULL*/) : SceneNode(CAMERA_NODE,t),
        m_camera(camera)
    {
        setController(c);
        AgmdApplication::getApplication()->addInputListener(c);
        //m_camera->m_node = this;
    }

    bool CameraNode::isVisible( BoundingSphere& bounds )
    {
        //m_camera->m_node = NULL;
        return false;
    }

    void CameraNode::findVisible( Camera*cam, RenderQueue& display,a_vector<LightNode*>& light )
    {
        //do nothing;
    }

    bool CameraNode::update( Transform* transform, a_uint32 time, a_uint32 updateFlags )
    {
        //do nothing;
        bool update = SceneNode::update(transform,time,updateFlags);
        if(update)
            m_camera->updateBuffer(this->getTransform().modelMatrix()*m_camera->look());
        return update;
    }
}
