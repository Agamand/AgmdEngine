#include "PlanetTreeNode.h"
#include "Planet.h"
#include <Core/SceneObject/Material.h>

ivec2 order[]=
{
	ivec2(1,1),
	ivec2(1,-1),
	ivec2(-1,1),
	ivec2(-1,-1)
};

quat GetRotationFor(int divisor, int face)
{
	return quat(glm::rotate(mat4(1),order[face].x*45.f,vec3(1,0,0))/*glm::rotate(mat4(1),order[face].y*45.0f/divisor,vec3(0,1,0))*/);
}
vec3 GetTranslation(int divisor, int face)
{
	return vec3(order[face].x*0.25f,order[face].y*0.25f,0);
}

void PlanetTreeNode::FindVisible( Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light )
{
	vec4 point(0,0,0,1);
	mat4 view = cam->GetView();
	point = m_transform->ModelMatrix()*point;
	vec3 real_point = normalize(vec3(point));
	point = view*vec4(real_point,1.0f);
	float distance = length(vec3(point));

	if(m_lod >= MAX_LOD)
	{
		display.push_back(this);
		return;
	}
	float trigger = 4*m_controller->m_size/m_divisor;
	float offset = distance;

	if(offset > trigger)
		display.push_back(this);
	else
	{
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(!m_faces[i])
			{
			Transform* t = new Transform(GetTranslation(m_divisor,i),quat(),vec3(0.5f));
				m_faces[i] = new PlanetTreeNode(Planet::s_plane,m_controller,m_face,m_positionMatrix*translate(mat4(1.0f),GetTranslation(m_divisor,i))*scale(mat4(1),vec3(0.5f)),new Transform(),m_lod+1);
				m_faces[i]->Update(m_transform,false);
			}
			m_faces[i]->FindVisible(cam,display,light);
		}
	}
}

PlanetTreeNode::PlanetTreeNode( PlanetModel* model,Planet* controller,int face,const mat4& matrix /*= mat4(1)*/,Transform* transform /*= NULL*/,int lod /*= 0*/ ) :
MeshNode(model,transform), m_lod(lod), m_controller(controller), m_positionMatrix(matrix),
m_face(face)
{
	if(Planet::s_mat)
		m_material = Planet::s_mat;
	
	//mat4 planetMatrix = controller->GetRoot()->GetTransform().ModelMatrix();
	//mat4 invPM = inverse(planetMatrix);
	//this->setModel(new PlanetModel(invPM*m_transform->ModelMatrix()));

	m_faces = new PlanetTreeNode*[4];
	std::memset(m_faces,0,32);
	m_divisor = 1;
	for(int i = 0; i < lod; i++)
		m_divisor *=2;
}

void PlanetTreeNode::Render( TRenderPass pass ) const
{
	if(!m_material || !m_material->Enable(pass))
		return;
	m_material->setParameter("u_divisor",(float)m_divisor);
	m_material->setParameter("u_offset",(float)m_controller->m_offset);
	m_material->setParameter("u_position_matrix",m_positionMatrix);
	m_material->setParameter("u_face",m_face);
	Draw();
	m_material->Disable();
}

