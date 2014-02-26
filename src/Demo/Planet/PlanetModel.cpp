#include "PlanetModel.h"

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

void _CreatePlane(int size, int offset_index, std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& index)
{


	vec3 orientation = vec3(0,0,1);
	float x_2 = 1;
	float y_2 = 1;
	vec3 o = -vec3(0.5f,0.5f,0);
	int count = size;
	float offset = 1.f/count;

	for(int i = 0; i <= count; i++)
	{
		for(int j = 0; j <= count; j++)
		{
			Model::TVertex vertex;
			vertex.color = -1;
			vertex.normal = orientation;
			vertex.position = vec3(o.x+offset*i,o.y+offset*j,0.f);
			vertex.texCoords = vec2(i*offset,j*offset);
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

void CreateFaceMetaSphere(std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& indices,int layer)
{
	_CreatePlane(20,0,vertices,indices);
	/*for(std::vector<Model::TVertex>::iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		(*itr).position= normalize((*itr).position);*/
}

PlanetModel::PlanetModel( int layer, int x, int y ) : Model()
{
	std::vector<Model::TVertex> vertices;
	std::vector<Model::TIndex> indices;

	CreateFaceMetaSphere(vertices,indices,layer);
	GenerateBuffer(&vertices[0],vertices.size(),&indices[0],indices.size());
}
