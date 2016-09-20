/*
============================================================================
Demo - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/Kinroux)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#include <Demo/Loader/MeshLoader.h>
#include <Core/Driver.h>
#include <iostream>
#include <string>
#include <fstream>


MeshLoader::MeshLoader()
{}

MeshLoader::~MeshLoader()
{}

Model* MeshLoader::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename,std::ios::in);
    if (!file)
        throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ObjLoader)");
    a_vector<Model::TVertex> vertices;
    a_vector<Model::TIndex> indices;
    int vertices_count, index;
    file >> vertices_count;
    for(int i = 0; i < vertices_count; i++)
    {
        Model::TVertex vertex;
        vertex.normal = vec3(0,0,1);
        file >> vertex.position.x >> vertex.position.y >> vertex.position.z >> vertex.normal.x;// >> vertex.normal.y >> vertex.normal.z >> vertex.texCoords.x >> vertex.texCoords.y;
        int c;
        //file >> c >> c >> c >> c;
        vertices.push_back(vertex);
    }
    file >> index;
    for(int i = 0; i < index; i++)
    {
        Model::TIndex index;
        file >> index;
        indices.push_back(index);
        file >> index;
        indices.push_back(index);
        file >> index;
        indices.push_back(index);
    }
    return new Model(&vertices[0],vertices.size(),&indices[0],indices.size(),PT_TRIANGLELIST);
}

void MeshLoader::SaveToFile(const Model* object, const std::string& filename)
{

}

void MeshLoader::OnError()
{
    throw Exception("");
}

