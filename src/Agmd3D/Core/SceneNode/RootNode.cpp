#include <Core/SceneNode/RootNode.h>
#include <Core/Model/SceneMgr.h>
namespace Agmd
{
	void Agmd::RootNode::add( SceneNode* node)
	{
		if(m_sceneMgr)
			m_sceneMgr->__addNode(node);
	}

	void RootNode::remove( SceneNode* node)
	{
		if(m_sceneMgr)
			m_sceneMgr->__removeNode(node);
	}

}

