#include "Planet.h"
#include "PlanetModel.h"

#include <Core/SceneObject/Material.h>
#include <Core/Texture/Image.h>

#include <Utilities/StringUtils.h>

#include <fstream>


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
	m_material = mat;
	//mat->setParameter("u_size",size);
	s_plane = new PlanetModel(0,0,0);
	m_root = new SceneNode(ROOT_NODE,new Transform(vec3(0),quat(),vec3(2)));
	for(int i = 0; i < 1*MAX_PLANET_FACE; i++ )
	{
		//Material*_mat = new Material(*mat);
		//mat->SetTexture(tex[i],0,(TRenderPass)((1<<RENDERPASS_DEFERRED) | (1<<RENDERPASS_ZBUFFER)| (1<<RENDERPASS_DIFFUSE)));
		m_root->AddChild(new PlanetTreeNode(s_plane,this,i,translate(mat4(1),0.5f*face[i])*mat4_cast(sRot[i])));
	}
}

Model* Planet::exportToFile( const std::string& filename,int precision /*= 0*/ )
{

	std::vector<Model::TVertex> vertices;
	std::vector<unsigned short> indices;
	for(a_uint32 i = 0; i < MAX_PLANET_FACE; i++)
	{
		PlanetModel::CreateFaceMetaSphere(vertices,indices,precision);
	}
	std::ofstream out(filename, std::ios::out);
	

	int face_order[] ={
		4,
		5,
		0,
		1,
		2,
		3
	};

	Texture planet_tex = m_material->getTexture(0);
	Image* pixel = planet_tex.GetPixelsPtr();
	int _size =	vertices.size()/6;
	Color c;
	for(a_uint32 i = 0, size = vertices.size(); i < size; i++)
	{
		planet_tex;
		int j = i/_size;
		Image& img = pixel[face_order[j]];
		vertices[i].normal = normalize(vec3(translate(mat4(1),face[j]*0.5f)*mat4_cast(sRot[j])*vec4(vertices[i].position,1)));
		const ivec2& isize = img.GetSize();
		ivec2 pixel;
		//if(j == 5)
			//pixel = ivec2(255-(0.5+vertices[i].position.x)*(isize.x-1),(0.5+vertices[i].position.y)*(isize.y-1));
		/*else*/ if(j == 1)
			pixel = ivec2(255-(0.5+vertices[i].position.x)*(isize.x-1),(0.5+vertices[i].position.y)*(isize.y-1));
		else pixel = ivec2((0.5+vertices[i].position.x)*(isize.x-1),255-(0.5+vertices[i].position.y)*(isize.y-1));
		
		c = img.GetPixel(pixel.x,pixel.y);
		float grayScale = c.ToGrey()/255.0f;
		float displacement = grayScale;
		if(displacement < 0 || displacement > 1.0f)
			break;
		vertices[i].position = vertices[i].normal*(float)m_size+vertices[i].normal*displacement*m_offset;
		out << "v " << vertices[i].position.x << " " << vertices[i].position.y << " " << vertices[i].position.z << std::endl;
	}

	for(a_uint32 i = 0, size = indices.size()/3; i < size; i++)
	{
		out << "f " << std::string(StringBuilder(indices[i*3]+1)("//")) <<" "<< std::string(StringBuilder(indices[i*3+1]+1)("//")) <<" "<< std::string(StringBuilder(indices[i*3+2]+1)("//")) << std::endl;
	}


	out.close();
	return new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
}

PlanetModel* Planet::s_plane = NULL;
Material* Planet::s_mat = NULL;