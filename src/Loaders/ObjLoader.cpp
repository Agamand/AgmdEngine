#include <Loaders/ObjLoader.h>
#include <Core/Renderer.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>


namespace Agmd
{

	ObjLoader::ObjLoader()
	{}

	ObjLoader::~ObjLoader()
	{}

	Model* ObjLoader::LoadFromFile(const std::string& filename)
	{
		std::ifstream file(filename,std::ios::in|std::ios::ate);
		if (!file)
			throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ObjLoader)");

		uint32 size =  (uint32)file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<vec3> position;
		std::vector<vec2> texPos;
		std::vector<vec3> normal;

		std::vector<Model::TVertex> vertices;
		std::vector<Model::TIndex> indices;

		while(skipCommentLine(file))
		{
			if(!processLine(position,texPos,normal,indices,file))
				break;
		}

		for(uint32 i = 0; i < position.size(); i++)
		{
			Model::TVertex vertex;
			vertex.position = position[i];
			vertex.texCoords = texPos[i];
			vertex.normal = normal[i];
			vertices.push_back(vertex);
		}

		return new Model(&vertices[0],vertices.size(),&indices[0],indices.size(),"amarr.png");
	}

	void ObjLoader::SaveToFile(const Model* object, const std::string& filename)
	{

	}

	bool ObjLoader::skipCommentLine(std::istream& file)
	{
		char next;
		while( file >> std::skipws >> next ) 
		{
			file.putback(next);
			if ('#' == next)
				skipLine(file);
			else
				return true;
		}
		return false;
	}

	void ObjLoader::skipLine(std::istream& file)
	{
		char next;
		file >> std::noskipws;
		while( (file >> next) && ('\n' != next) );
	}

	bool ObjLoader::processLine(std::vector<vec3>& position,std::vector<vec2>& texPos,std::vector<vec3>& normal,std::vector<Model::TIndex>& indices, std::istream& is)
	{
		std::string value;
		int32 index = 0;
		int32 temp = 0;

		if (!(is >> value))
			return false;

		if(value == "v")
		{
			float x,y,z;
			is >> x >> y >> z;
			vec3 pos(x,y,z);
			position.push_back(pos);
		}else if(value == "vt")
		{
			float x,y;
			is >> x >> y;
			vec2 pos(x,y);
			texPos.push_back(pos);
		}else if(value == "vn")
		{
			float x,y,z;
			is >> x >> y >> z;
			vec3 pos(x,y,z);
			normal.push_back(pos);
		}else if(value == "f")
		{

			int i = 0;
			for (char c; i<10; ++i) 
			{
				is >> index >> c >> temp >> c >> temp;

				if(!is.good())
					break;	

				indices.push_back(index-1);
				index = 0;

			}
			is.clear();
		}else skipLine(is);

		return true;
	}

	void ObjLoader::OnError()
	{
		throw Exception("");
	}


}