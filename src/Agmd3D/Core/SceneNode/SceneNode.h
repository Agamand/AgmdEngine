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
#include <Core/Tools/RenderQueue.h>
#include <Container/Vector.h>
using namespace AgmdMaths;

namespace Agmd
{
	enum NodeType
	{
		ROOT_NODE,
		DISPLAYABLE_NODE,
		LIGHT_NODE,
		CAMERA_NODE
	};

	enum UpdateFlags
	{
		UPDATE_CHILDREN = 0x01,
		TRANSFORM_CHANGED = 0x02
	};

	class DisplayNode;
    class AGMD3D_EXPORT SceneNode
    {
    public :
        SceneNode(NodeType, Transform*);
        virtual ~SceneNode();
		virtual bool isVisible(BoundingBox& bbox) { return true;}
		virtual void findVisible(Camera*cam, RenderQueue& display,a_vector<LightNode*>& light) {
			if(!m_children.empty())
				for(a_uint32 i = 0,len = m_children.size(); i < len; i++)
					m_children[i]->findVisible(cam,display,light);
		}

		virtual bool update(Transform* transform, a_uint32 time, a_uint32 updateFlags);
        Transform& getTransform();
		void addChild(SceneNode* node)	{ m_children.push_back(node); node->m_parent = this; node->update(m_transform,0,TRANSFORM_CHANGED|UPDATE_CHILDREN);}
		NodeType getType() const {return m_type;}
		bool isEmpty();
		void clear();
		void setController( Controller* controller );
		Controller* getController() const {return m_sceneController;}
	protected:
		

        Transform* m_transform;
		NodeType m_type;
		a_vector<SceneNode*> m_children;
		SceneNode* m_parent;
		Controller* m_sceneController;
	};

}


#endif /* _SCENENODE_H_ */