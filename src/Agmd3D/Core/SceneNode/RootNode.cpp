#include <Core/SceneNode/RootNode.h>
#include <Core/Model/SceneMgr.h>
namespace Agmd
{
    void Agmd::RootNode::add( SceneNode* node)
    {
        #ifdef USE_EDITOR
        if(m_sceneMgr)
            m_sceneMgr->__addNode(node);
#endif
    }

    void RootNode::remove( SceneNode* node)
    {
#ifdef USE_EDITOR
        if(m_sceneMgr)
            m_sceneMgr->__removeNode(node);
#endif
    }

}

