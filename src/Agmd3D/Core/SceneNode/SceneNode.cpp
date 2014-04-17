/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneObject/Material.h>


namespace Agmd
{

    SceneNode::SceneNode(NodeType type,Transform* transform) : m_type(type), m_parent(NULL)
    {
		if(!transform)
			m_transform = new Transform();
		else m_transform = transform;
	}

    SceneNode::~SceneNode()
    {}

    Transform& SceneNode::GetTransform() 
    { 
        return *m_transform;
    }

	void SceneNode::Update(Transform* transform, bool updateChildren )
	{
		m_transform->Update(transform);
		if(updateChildren && !m_children.empty())
		{
			for(std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); itr++)
				(*itr)->Update(m_transform,updateChildren);
		}
	}

	bool SceneNode::isEmpty()
	{
		return m_children.empty();
	}


}

