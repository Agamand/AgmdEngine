#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

using namespace Agmd;

#define MAX_FACE 4
#define MAX_LOD 10
#define CONST_DISTANCE 4.0f

class Planet;
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
	PlanetTreeNode(PlanetModel* model,Planet* controller,int face,const mat4& matrix = mat4(1),Transform* transform = NULL,int lod = 0);

	virtual void Update(Transform* transform, bool updateChildren)
	{
		DisplayNode::Update(transform,false);
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(m_faces[i])
				m_faces[i]->Update(m_transform,updateChildren);
		}
	}
	virtual void Render(TRenderPass pass) const;
	virtual void FindVisible(Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light);

private:
	int m_lod;
	int m_divisor;
	int x,y;
	PlanetTreeNode** m_faces;
	Planet* m_controller;
	Texture m_texture;
	mat4 m_positionMatrix;
	int m_face;
};

#endif /* _QUADTREENODE_H_ */