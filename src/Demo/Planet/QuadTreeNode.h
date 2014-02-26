#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

using namespace Agmd;

#define MAX_FACE 4
#define MAX_LOD 14
#define CONST_DISTANCE 4.0f
class QuadTreeNode : public MeshNode
{
public:
	enum Face
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};
	QuadTreeNode(PlanetModel* model,Transform* transform = NULL,int lod = 0) : MeshNode(model,transform), m_lod(lod)
	{
		face = new QuadTreeNode*[4];
		std::memset(face,0,16);
		m_divisor = 1;
		for(int i = 0; i < lod; i++)
			m_divisor *=2;
	}

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
	QuadTreeNode** face;
};

#endif /* _QUADTREENODE_H_ */