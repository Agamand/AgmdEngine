
#ifndef _PLANET_H_
#define _PLANET_H_

#include <core/SceneNode/SceneNode.h>
#include "QuadTreeNode.h"
#include <map>
#include <string>
using namespace Agmd;
#define MAX_PLANET_FACE 6

class Planet
{
public:
	Planet(Material*mat);

	SceneNode* GetRoot()
	{
		return m_root;
	}

	static PlanetModel* s_plane;

private:
	SceneNode* m_root;

};
#endif
