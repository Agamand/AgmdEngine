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
#include <Core/SceneNode/RootNode.h>

namespace Agmd
{

    SceneNode::SceneNode(NodeType type,Transform* transform) : m_type(type), m_parent(NULL),m_sceneController(NULL),m_root(NULL)
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
		if(m_parent)
			m_parent->removeChild(this);	
		clear();
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
		return (updateFlags & TRANSFORM_CHANGED) != 0;
	}

	bool SceneNode::isEmpty()
	{
		return m_children.empty();
	}

	void SceneNode::removeChild( SceneNode* node )
	{
		for(a_uint32 i = 0,len = m_children.size(); i < len; i++)
		{
			if(m_children[i] == node)
			{
				if(node->m_root)
					node->m_root->remove(node);
				node->m_parent = node->m_root = NULL;
			}
		}	
	}

	void SceneNode::clear()
	{
		for(a_uint32 i = 0,len = m_children.size(); i < len; i++)
		{
			if(m_children[i]->m_root)
				m_children[i]->m_root->remove(m_children[i]);
			m_children[i]->m_parent = m_children[i]->m_root = NULL;
		}
		m_children.clear();
	}

	void SceneNode::setController( Controller* controller )
	{
		if(m_sceneController)
			m_sceneController->m_bindedNode = NULL;
		m_sceneController=controller;
		m_sceneController->m_bindedNode = this;
	}

	void SceneNode::addChild( SceneNode* node )
	{
		m_children.push_back(node); 
		node->m_parent = this;
		
		node->m_root = this->m_type == ROOT_NODE ? (RootNode*)this : this->m_root;
		if(this->m_type == ROOT_NODE)
			((RootNode*)this)->add(node);
		else if(m_root) m_root->add(node);
		node->update(m_transform,0,TRANSFORM_CHANGED|UPDATE_CHILDREN);
	}

	Agmd::SceneNode* SceneNode::getParent()
	{
		return m_parent;
	}

}

