#ifndef _QUADTREENODE_H_
#define _QUADTREENODE_H_

#include <Core/SceneNode/MeshNode.h>
#include "PlanetModel.h"

using namespace Agmd;

#define MAX_FACE 4
#define MAX_LOD 20
#define CONST_DISTANCE 1.0f

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
	friend class Planet;

	PlanetTreeNode(PlanetModel* model,Planet* controller,int face,const mat4& matrix = mat4(1),Transform* transform = NULL,int lod = 0);
	~PlanetTreeNode();
	virtual bool update(Transform* transform, bool updateChildren,bool transformUpdate);

	virtual void render(TRenderPass pass) const;
	virtual void findVisible(Camera*cam,RenderQueue& display,a_vector<LightNode*>& light);
	void generateTexture();
	void needRegenerateMaps()
	{
		m_needGenerate = true;
		for(a_uint32 i = 0; i < MAX_FACE;i++)
			if(m_faces[i])
				m_faces[i]->needRegenerateMaps();
	}
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