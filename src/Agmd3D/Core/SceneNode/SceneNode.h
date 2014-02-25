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
#include <Utilities/SmartPtr.h>
#include <Transform.h>

#include <vector>
using namespace AgmdMaths;

namespace Agmd
{
	enum NodeType
	{
		DISPLAYABLE_NODE,
		LIGHT_NODE
	};

    class AGMD3D_EXPORT SceneNode
    {
    public :
        SceneNode(NodeType, Transform*);
        virtual ~SceneNode();
		virtual bool IsVisible(BoundingBox& bbox) = 0;
        Transform& GetTransform();
		void AddChild(SceneNode* node)	{ m_children.push_back(node);}
		NodeType GetType() const {return m_type;}
    protected:
		
        Transform* m_transform;
		NodeType m_type;
		std::vector<SceneNode*> m_children;
	};

}


#endif /* _SCENENODE_H_ */