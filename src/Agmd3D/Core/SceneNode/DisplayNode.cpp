
#include <Core/SceneNode/DisplayNode.h>
#include <Core/SceneObject/Material.h>
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

	bool DisplayNode::IsVisible( BoundingBox& bbox )
	{
		return true;
	}

	void DisplayNode::FindVisible(Camera*cam, a_vector<DisplayNode*>& display,a_vector<LightNode*>& light)
	{
		display.push_back(this);
		SceneNode::FindVisible(cam,display,light);
	}

}

