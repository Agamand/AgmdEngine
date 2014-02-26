#include "Planet.h"
#include "PlanetModel.h"
Planet::Planet()
{
	s_plane = new PlanetModel(0,0,0);
	m_root = new SceneNode(ROOT_NODE,NULL);
	for(int i = 0; i < MAX_PLANET_FACE; i++ )
		m_root->AddChild(new QuadTreeNode(s_plane));
}
PlanetModel* Planet::s_plane = NULL;