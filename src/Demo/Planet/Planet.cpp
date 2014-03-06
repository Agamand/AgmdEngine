#include "Planet.h"
#include "PlanetModel.h"

vec3 face[] = {
	vec3(0,0,1),
	vec3(0,0,-1),
	vec3(1,0,0),
	vec3(-1,0,0),
	vec3(0,1,0),
	vec3(0,-1,0),
};

quat sRot[] = {
	quat(),
	quat(glm::rotate(mat4(1),180.f,vec3(1,0,0))),
	quat(glm::rotate(mat4(1),90.f,vec3(0,1,0))),
	quat(glm::rotate(mat4(1),-90.f,vec3(0,1,0))),
	quat(glm::rotate(mat4(1),-90.f,vec3(1,0,0))),
	quat(glm::rotate(mat4(1),90.f,vec3(1,0,0)))
};

Planet::Planet(Material* mat)
{
	s_mat = mat;
	s_plane = new PlanetModel(0,0,0);
	m_root = new SceneNode(ROOT_NODE,new Transform(vec3(0),quat(),vec3(2)));
	for(int i = 0; i < MAX_PLANET_FACE; i++ )
		m_root->AddChild(new PlanetTreeNode(s_plane,new Transform(0.5f*face[i],sRot[i])));
	
}
PlanetModel* Planet::s_plane = NULL;
Material* Planet::s_mat = NULL;