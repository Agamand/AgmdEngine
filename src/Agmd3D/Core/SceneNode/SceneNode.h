/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SCENENODE_H_
#define _SCENENODE_H_

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Enums.h>
#include <Core/Camera/Camera.h>
#include <Utilities/SmartPtr.h>
#include <Transform.h>

#include <vector>
using namespace AgmdMaths;

namespace Agmd
{
	enum NodeType
	{
		DISPLAYABLE_NODE,
		LIGHT_NODE,
		ROOT_NODE
	};

	class DisplayNode;
    class AGMD3D_EXPORT SceneNode
    {
    public :
        SceneNode(NodeType, Transform*);
        virtual ~SceneNode();
		virtual bool IsVisible(BoundingBox& bbox) { return true;}
		virtual void FindVisible(Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light) {
			if(!m_children.empty())
				for(std::vector<SceneNode*>::iterator itr = m_children.begin(); itr != m_children.end(); itr++)
					(*itr)->FindVisible(cam,display,light);
		}

		virtual void Update(Transform* transform, bool updateChildren);
        Transform& GetTransform();
		void AddChild(SceneNode* node)	{ m_children.push_back(node); node->m_parent = this;}
		NodeType GetType() const {return m_type;}
		bool isEmpty();
		void clear();
	protected:
		

        Transform* m_transform;
		NodeType m_type;
		std::vector<SceneNode*> m_children;
		SceneNode* m_parent;
	};

}


#endif /* _SCENENODE_H_ */