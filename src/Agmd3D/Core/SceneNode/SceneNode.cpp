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
    SceneNode::SceneNode(Transform* transform) : 
    m_material(NULL),
    m_transform(transform)
    {}

    SceneNode::~SceneNode()
    {}

    Transform& SceneNode::GetTransform() 
    { 
        return *m_transform;
    }
}

