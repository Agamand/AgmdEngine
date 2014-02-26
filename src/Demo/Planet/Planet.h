
#ifndef _PLANET_H_
#define _PLANET_H_

#include <core/SceneNode/SceneNode.h>
#include "QuadTreeNode.h"
using namespace Agmd;
#define MAX_PLANET_FACE 1
class Planet
{
public:
	Planet();

	SceneNode* GetRoot()
	{
		return m_root;
	}

	static PlanetModel* s_plane;

private:
	SceneNode* m_root;

};
#endif
