#include "PlanetModel.h"
#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))


void PlanetModel::CreatePlane(int size, int offset_index, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index,mat4 matrix)
{


	vec3 orientation = vec3(0,0,1);
	float x_2 = 1;
	float y_2 = 1;
	vec3 o = -vec3(0.5f,0.5f,0);
	int count = size+2;
	float offset = 1.f/size;
	offset_index = vertices.size();

	for(int i = 0; i <= count; i++)
	{
		for(int j = 0; j <= count; j++)
		{
			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = orientation;
			vertex.position = vec3(matrix*vec4(o.x+offset*clamp(i-1,0,size),o.y+offset*clamp(j-1,0,size),0.f,1.f));
			vertex.texCoords = vec2((i-1)*offset,(j-1)*offset);
			vertices.push_back(vertex);
		}
	}

	for(int i = 0; i < count;i++)
	{
		for(int j = 0; j < count; j++)
		{
			int _i = SELECT(i+1, count+1), _j = SELECT(j+1, count+1);
			index.push_back(offset_index+i*(count+1)+j);
			index.push_back(offset_index+_i*(count+1)+j);
			index.push_back(offset_index+_i*(count+1)+_j);

			index.push_back(offset_index+i*(count+1)+j);
			index.push_back(offset_index+_i*(count+1)+_j);
			index.push_back(offset_index+i*(count+1)+_j);
		}
	}
}


void PlanetModel::CreateFaceMetaSphere(std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& indices,int layer,mat4 matrix)
{
	CreatePlane(20*(1+layer),0,vertices,indices,matrix);
	/*mat4 inv = inverse(matrix);
	for(std::vector<Model::TVertex>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
	{
		(*itr).position = vec3(matrix*vec4((*itr).position,1.0f));
		(*itr).position = normalize((*itr).position);
		(*itr).position = vec3(inv*vec4((*itr).position,1.0f));
		//(*itr).position.z -= 0.5f;
	}*/
}

PlanetModel::PlanetModel( int layer, int x, int y ) : Model()
{
	std::vector<Model::TVertex> vertices;
	std::vector<Model::TIndex> indices;

	CreateFaceMetaSphere(vertices,indices,layer);
	GenerateBuffer(&vertices[0],vertices.size(),&indices[0],indices.size());
	//this->m_PrimitiveType = PT_PATCHLIST;
}

PlanetModel::PlanetModel(mat4 matrix)
{
	std::vector<Model::TVertex> vertices;
	std::vector<Model::TIndex> indices;

	CreateFaceMetaSphere(vertices,indices,0,matrix);
	GenerateBuffer(&vertices[0],vertices.size(),&indices[0],indices.size());
	//this->m_PrimitiveType = PT_PATCHLIST;
}
