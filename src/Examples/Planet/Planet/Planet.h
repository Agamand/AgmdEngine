
#ifndef _PLANET_H_
#define _PLANET_H_

#include <core/SceneNode/SceneNode.h>
#include "PlanetTreeNode.h"
#include <map>
#include <string>
using namespace Agmd;
#define MAX_PLANET_FACE 6

class Planet
{
public:
	friend class PlanetTreeNode;
	Planet(Texture tex[MAX_PLANET_FACE],Material*mat = NULL, float size = 0);

	SceneNode* GetRoot()
	{
		return m_root;
	}
	
	static PlanetModel* s_plane;
	static Material* s_mat;
private:
	Texture m_texture[MAX_PLANET_FACE];
	SceneNode* m_root;
	float m_offset;
	float m_size;
};
#endif
