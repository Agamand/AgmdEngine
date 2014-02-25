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

    SceneNode::SceneNode(NodeType type,Transform* transform) : m_type(type)
    {
		if(!m_transform)
			m_transform = new Transform();
	}

    SceneNode::~SceneNode()
    {}

    Transform& SceneNode::GetTransform() 
    { 
        return *m_transform;
    }
}

