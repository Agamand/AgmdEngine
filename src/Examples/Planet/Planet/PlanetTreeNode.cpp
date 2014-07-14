#include "PlanetTreeNode.h"
#include "Planet.h"
#include <Core/SceneObject/Material.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>

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
	float trigger = 2*m_controller->m_size/m_divisor;
	vec4 point(0,0,0,1);
	mat4 view = cam->GetView();
	point = m_positionMatrix*point;
	vec3 real_point = normalize(vec3(point));
	vec4 points[] = {vec4(0,0,0,1),vec4(-0.5f,-0.5f,0,1),vec4(0.5f,-0.5f,0,1),vec4(-0.5f,0.5f,0,1),vec4(0.5f,0.5f,0,1)};
	point = m_positionMatrix*point;
	float distance = trigger+1;
	bool isVisible = false;
	vec3 camDirection = vec3(0,0,1);
	for(a_uint8 i = 0; i < 5; i++)
	{
		points[i] = m_positionMatrix*points[i];
		vec3 real_point = normalize(vec3(points[i]));
		if(!isVisible)
		{
			vec3 normal = mat3(view*m_transform->ModelMatrix())*real_point;
			float product = dot(camDirection,normal);
			isVisible = product > 0;
		}
		

		points[i] = view*m_transform->ModelMatrix()*vec4(real_point,1.0f);
		
		float len = length(vec3(points[i]));
		if(len < distance)
			distance = len;
	}
	float trigger2 = length(points[0]-points[1]);
	if(!isVisible)
		return;

	if(m_lod >= MAX_LOD)
	{
		display.push_back(this);
		return;
	}
	
	float offset = distance;
	trigger = trigger > trigger2 ? trigger  :  trigger2;
	if(offset > trigger)
	{
		display.push_back(this);
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(m_faces[i])
				delete m_faces[i];
			m_faces[i] = NULL;
		}
	}
	else
	{
		bool first_init = false;
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(!m_faces[i])
			{
				first_init = true;
				m_faces[i] = new PlanetTreeNode(Planet::s_plane,m_controller,m_face,m_positionMatrix*translate(mat4(1.0f),GetTranslation(m_divisor,i))*scale(mat4(1),vec3(0.5f)),new Transform(),m_lod+1);
				//m_faces[i]->Update(m_transform,false,false);
			}
			if(!first_init)
				m_faces[i]->FindVisible(cam,display,light);
			else display.push_back(this);
		}
	}
}

PlanetTreeNode::PlanetTreeNode( PlanetModel* model,Planet* controller,int face,const mat4& matrix /*= mat4(1)*/,Transform* transform /*= NULL*/,int lod /*= 0*/ ) :
MeshNode(model,transform), m_lod(lod), m_controller(controller), m_positionMatrix(matrix),
m_face(face),m_textureInit(false)
{
	if(Planet::s_mat)
		m_material = Planet::s_mat;

	m_faces = new PlanetTreeNode*[4];
	std::memset(m_faces,0,32);
	m_divisor = 1;
	for(int i = 0; i < lod; i++)
		m_divisor *=2;
}

void PlanetTreeNode::Render( TRenderPass pass ) const
{
	//HACK FOR TEST

	//PlanetTreeNode* node = const_cast<PlanetTreeNode*>(this);
	//node->generateTexture();

	if(!m_material || !m_material->Enable(pass))
		return;
	Driver& driver = Driver::Get();
	m_material->setParameter("u_divisor",(float)m_divisor);
	m_material->setParameter("u_offset",(float)m_controller->m_offset);
	m_material->setParameter("u_position_matrix",m_positionMatrix);
	m_material->setParameter("u_face",m_face);
	driver.SetTexture(0,m_heightTexture.GetTexture());
	driver.SetTexture(2,m_normalTexture.GetTexture());
	Draw();
	m_material->Disable();
}

void PlanetTreeNode::Update( Transform* transform, bool updateChildren, bool transformChanged )
{
	float trigger = 4*m_controller->m_size/m_divisor/2;
	bool transformUpdate = transformChanged || m_transform->needUpdate();
	DisplayNode::Update(transform,updateChildren,transformChanged);



	if(!m_textureInit)
		generateTexture();

	for(int i = 0; i < MAX_FACE; i++)
	{
		if(m_faces[i])
			m_faces[i]->Update(m_transform,updateChildren,transformUpdate);
	}

	/*vec4 point(0,0,0,1); //center
	vec4 points[] = {vec4(0,0,0,1),vec4(-0.5f,-0.5f,0,1),vec4(0.5f,-0.5f,0,1),vec4(-0.5f,0.5f,0,1),vec4(0.5f,0.5f,0,1)};
	mat4 view = Camera::GetCurrent(CAMERA_3D)->GetView();
	point = m_positionMatrix*point;
	float distance = trigger+1;;
	for(a_uint8 i = 0; i < 5; i++)
	{
		points[i] = m_positionMatrix*points[i];
		vec3 real_point = normalize(vec3(points[i]));
		points[i] = view*m_transform->ModelMatrix()*vec4(real_point,1.0f);
		float len = length(vec3(points[i]));
		if(len < distance)
			distance = len;
	}
	float tr2 = length(points[0]-points[1]);
	if(m_lod >= MAX_LOD)
		return;
	
	float offset = distance;
	//trigger = trigger > tr2 ? trigger :  tr2;
	if(offset <= trigger || true)
		for(int i = 0; i < MAX_FACE; i++)
		{
			if(m_faces[i])
				m_faces[i]->Update(m_transform,updateChildren);
		}*/
}
#define  TEX_SIZE 256
void PlanetTreeNode::generateTexture()
{
	m_heightTexture.Create(ivec2(TEX_SIZE*2),PXF_A8R8G8B8,TEXTURE_2D,TEX_WRAP_CLAMP);
	m_normalTexture.Create(ivec2(TEX_SIZE*2),PXF_A8R8G8B8,TEXTURE_2D,TEX_WRAP_CLAMP | TEX_NOMIPMAP);
	Texture::BeginRenderToTexture(m_heightTexture,m_normalTexture);

	Driver& driver = Driver::Get();
	driver.SetViewPort(ivec2(0),ivec2(TEX_SIZE*2));
	driver.SetCurrentProgram(m_controller->m_ground_program.GetShaderProgram());
	m_controller->m_ground_program.SetParameter("u_position_matrix",m_positionMatrix);
	Draw();
	Texture::EndRenderToTexture();
	driver.SetCurrentProgram(NULL);
	driver.SetViewPort(ivec2(0),driver.GetScreen());
	m_textureInit = true;
}

