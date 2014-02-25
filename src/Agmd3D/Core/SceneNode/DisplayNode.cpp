
#include <Core/SceneNode/DisplayNode.h>
#include <Core/ResourceManager.h>
namespace Agmd
{

	DisplayNode::DisplayNode( Transform* t,Material*mat ) : SceneNode(DISPLAYABLE_NODE,t)
	{
		if(!mat)
			m_material = ResourceManager::Instance().Get<Material>("DEFAULT_MATERIAL");
	}	
}

