
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
		if(!cam->isInFrustrum(m_globalBbox))
			return;
		display.push_back(this);
		
		SceneNode::FindVisible(cam,display,light);
	}

	bool DisplayNode::Update( Transform* transform, bool updateChildren, bool transformChanged )
	{
		bool transformUpdate = SceneNode::Update(transform,updateChildren,transformChanged);
		
		if(transformUpdate) // need implement : m_baseBbox = modelbbox + (all children bbox), actually is only m_baseBbox = modelbbox
		{
			m_localBBox.mult( m_transform->LocalModelMatrix(),m_baseBbox);
			m_globalBbox.mult( m_transform->ModelMatrix(),m_baseBbox);
		}
		return transformUpdate;
	}

}

