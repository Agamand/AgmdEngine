/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/SceneNode/SceneNode.h>
#include <Core/Model/Material.h>
#include <Core/Controller/Controller.h>

namespace Agmd
{

    SceneNode::SceneNode(NodeType type,Transform* transform) : m_type(type), m_parent(NULL),m_sceneController(NULL)
    {
		if(!transform)
			m_transform = new Transform();
		else m_transform = transform;
		update(NULL,0,TRANSFORM_CHANGED);
	}

    SceneNode::~SceneNode()
    {
		if(m_sceneController)
			m_sceneController->m_bindedNode = NULL;
	}

    Transform& SceneNode::getTransform() 
    { 
        return *m_transform;
    }

	bool SceneNode::update( Transform* transform, a_uint32 time, a_uint32 updateFlags )
	{
		
		if(m_transform->needUpdate())
			updateFlags |= TRANSFORM_CHANGED;
		if(updateFlags & TRANSFORM_CHANGED)
			m_transform->update(transform);
		if(updateFlags & UPDATE_CHILDREN && !m_children.empty())
		{
			for(a_uint32 i = 0,len = m_children.size(); i < len; i++)
				m_children[i]->update(m_transform,time,updateFlags);
		}
		if(m_sceneController)
			m_sceneController->update(time);
		return (bool)(updateFlags & TRANSFORM_CHANGED);
	}

	bool SceneNode::isEmpty()
	{
		return m_children.empty();
	}


	void SceneNode::clear()
	{
		m_children.clear();
	}

	void SceneNode::setController( Controller* controller )
	{
		if(m_sceneController)
			m_sceneController->m_bindedNode = NULL;
		m_sceneController=controller;
		m_sceneController->m_bindedNode = this;
	}

}

