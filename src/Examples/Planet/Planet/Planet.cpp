#include "Planet.h"
#include "PlanetModel.h"

#include <Core/SceneObject/Material.h>

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

Planet::Planet(Texture tex[6],Material* mat,float offset) : m_offset(offset),m_size(1.0f)
{
	
	s_mat = mat;
	//mat->setParameter("u_size",size);
	s_plane = new PlanetModel(0,0,0);
	m_root = new SceneNode(ROOT_NODE,new Transform(vec3(0),quat(),vec3(2)));
	for(int i = 0; i < 1+0*MAX_PLANET_FACE; i++ )
	{
		//Material*_mat = new Material(*mat);
		//mat->SetTexture(tex[i],0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)| (1<<RENDERPASS_DIFFUSE)));
		m_root->AddChild(new PlanetTreeNode(s_plane,this,tex[i],new Transform(0.5f*face[i],sRot[i])));
	}
}
PlanetModel* Planet::s_plane = NULL;
Material* Planet::s_mat = NULL;