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

const char* face_names[] = {
	"top",	
	"bottom",
	"fore",
	"back",
	"left",
	"right"
};


quat sRot[] = {
	quat(),
	quat(glm::rotate(mat4(1),180.f,vec3(1,0,0))),
	quat(glm::rotate(mat4(1),90.f,vec3(0,1,0))),
	quat(glm::rotate(mat4(1),-90.f,vec3(0,1,0))),
	quat(glm::rotate(mat4(1),-90.f,vec3(1,0,0))),
	quat(glm::rotate(mat4(1),90.f,vec3(1,0,0)))
};

Planet::Planet(PlanetModel* model, Material* mat,float size,bool atmosphere) : m_offset(0.f),m_size(size),lightDir(1,0,0),m_use_atmosphere(atmosphere)
{
	
	m_material = mat;
	if(!model)
		m_model = new PlanetModel(0,0,0);
	else m_model = model;
	Transform* t = new Transform(vec3(0),quat(),vec3(1));
	t->scale(m_size,m_size,m_size);
	m_root = new SceneNode(ROOT_NODE,t);
	memset(m_faces,0,sizeof(m_faces));
	for(int i = 0; i < 1*MAX_PLANET_FACE; i++ )
	{
		m_faces[i] = new PlanetTreeNode(m_model,this,i,translate(mat4(1),0.5f*face[i])*mat4_cast(sRot[i]));
		m_root->addChild(m_faces[i]);
	}
	m_root->addChild(new PlanetAtmosphereNode(this));
}

Model* Planet::exportToFile( const std::string& filename,int precision /*= 0*/,int textureSize/* = 1024*/)
{

	a_vector<Model::TVertex> vertices;
	a_vector<unsigned short> indices;
	for(a_uint32 i = 0; i < MAX_PLANET_FACE; i++)
	{
		PlanetModel::CreateFaceMetaSphere(vertices,indices,precision);
		std::ofstream out(StringBuilder("export/")(face_names[i])("_")(filename)(".obj"), std::ios::out);
		Texture heightMap, normalMap, diffuseMap;
		heightMap.Create(ivec2(textureSize),PXF_A8R8G8B8,TEXTURE_2D);
		normalMap.Create(ivec2(textureSize),PXF_A8R8G8B8,TEXTURE_2D);
		diffuseMap.Create(ivec2(textureSize),PXF_A8R8G8B8,TEXTURE_2D);

		m_model->generateTexture(heightMap,normalMap,m_faces[i]->m_positionMatrix);
		m_model->generateTexture(diffuseMap,heightMap,m_material->getTexture(1));
		heightMap.updatePixelFromTexture();
		normalMap.updatePixelFromTexture();
		diffuseMap.updatePixelFromTexture();
		Image& img = heightMap.GetPixels();
		for(a_uint32 j = 0, size = vertices.size(); j < size; j++)
		{
			vertices[j].position = vertices[j].normal = normalize(vec3(m_faces[i]->m_positionMatrix*vec4(vertices[j].position,1)));
			const ivec2& isize = img.GetSize();
			ivec2 pixel;
			vertices[j].texCoords = clamp(vertices[j].texCoords,0.0f,1.0f);
			pixel = ivec2((vertices[j].texCoords.x)*(isize.x-1),(vertices[j].texCoords.y)*(isize.y-1));

			Color c = img.GetPixel(pixel.x,pixel.y);
			float grayScale = c.GetRed()/255.0f;
			float displacement = grayScale;
			if(displacement < 0 || displacement > 1.0f)
				displacement = 0.0f;
			vertices[j].position *= m_size+displacement*m_offset;
			out << "v " << vertices[j].position.x << " " << vertices[j].position.y << " " << vertices[j].position.z << std::endl;
			out << "vn " << vertices[j].normal.x << " " << vertices[j].normal.y << " " << vertices[j].normal.z << std::endl;
			out << "vt " << vertices[j].texCoords.x << " " << vertices[j].texCoords.y << std::endl;
		}
		
		for(a_uint32 j = 0, size = indices.size()/3; j < size; j++)
		{
			out << "f " << (indices[j*3]+1) << ("/") << (indices[j*3]+1) << ("/") << (indices[j*3]+1) <<" "<< (indices[j*3+1]+1)<<("/")<<(indices[j*3+1]+1)<<("/")<<(indices[j*3+1]+1) <<" "<< (indices[j*3+2]+1)<<("/")<<(indices[j*3+2]+1)<<("/")<<(indices[j*3+2]+1) << std::endl;
		}
		vertices.clear();
		indices.clear();
		out.close();
		heightMap.GetPixels().saveToFile(StringBuilder("export/")(face_names[i])("_")(filename)("_h")(".png"));
		normalMap.GetPixels().saveToFile(StringBuilder("export/")(face_names[i])("_")(filename)("_n")(".png"));
		diffuseMap.GetPixels().saveToFile(StringBuilder("export/")(face_names[i])("_")(filename)("_d")(".png"));
	}
	
	return NULL;// new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
}
