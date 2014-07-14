#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

using namespace Agmd;

#define MAX_FACE 4
#define MAX_LOD 6
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
	~PlanetTreeNode();
	virtual void Update(Transform* transform, bool updateChildren,bool transformUpdate);

	virtual void Render(TRenderPass pass) const;
	virtual void FindVisible(Camera*cam, a_vector<DisplayNode*>& display,a_vector<LightNode*>& light);
	void generateTexture();
private:
	int m_lod;
	int m_divisor;
	int x,y;
	PlanetTreeNode* m_faces[MAX_FACE];
	Planet* m_controller;
	Texture m_heightTexture;
	Texture m_normalTexture;
	mat4 m_positionMatrix;
	int m_face;
	bool m_textureInit;
	bool m_needGenerate;
};

#endif /* _QUADTREENODE_H_ */