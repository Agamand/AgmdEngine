#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

using namespace Agmd;

#define MAX_FACE 4
#define MAX_LOD 15
#define CONST_DISTANCE 4.0f
class PlanetTreeNode : public MeshNode
{
public:
	enum Face
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};
	PlanetTreeNode(PlanetModel* model,Planet* controller,Transform* transform = NULL,int lod = 0);

	virtual void Update(Transform* transform, bool updateChildren)
	{
		DisplayNode::Update(transform,false);
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(face[i])
				face[i]->Update(m_transform,updateChildren);
		}
	}

	virtual void FindVisible(Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light);

private:
	int m_lod;
	int m_divisor;
	int x,y;
	PlanetTreeNode** face;
	Planet* m_controller;
};

#endif /* _QUADTREENODE_H_ */