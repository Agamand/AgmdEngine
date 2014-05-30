
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
	Planet(Material*mat = NULL, float size = 0);

	SceneNode* GetRoot()
	{
		return m_root;
	}
	
	static PlanetModel* s_plane;
	static Material* s_mat;
private:
	SceneNode* m_root;
	int m_size;
};
#endif
