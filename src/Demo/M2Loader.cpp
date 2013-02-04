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

#include <Demo\M2Loader.h>
#include <Core/Renderer.h>
#include <iostream>
#include <string>
#include <fstream>


M2Loader::M2Loader()
{}

M2Loader::~M2Loader()
{}

Model* M2Loader::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename,std::ios::in | std::ios::ate | std::ios::binary);
    if (!file)
        throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ObjLoader)");

    uint32 size =  (uint32)file.tellg();
    file.seekg(0, std::ios::beg);


    std::vector<Model::TVertex> vertices;
    std::vector<Model::TIndex> indices;

    M2ModelHeader header;
    if(size < sizeof(header))
        return NULL;

    M2ModelVertex* m2vertex;

    int8* buffer = new int8[size];
    file.read(buffer,size);
    file.close();

    std::memcpy(&header,buffer,sizeof(header));

    M2RenderFlags* flags = (M2RenderFlags*)(buffer+header.ofsTexFlags);
    m2vertex = new M2ModelVertex[header.nVertices];
    std::memcpy(m2vertex,buffer+header.ofsVertices,sizeof(M2ModelVertex)*header.nVertices);
    vertices.resize(header.nVertices);

    std::ifstream file2(filename+".skin",std::ios::in | std::ios::ate | std::ios::binary);
    if (!file2)
        throw LoadingFailed(filename+".skin","Erreur lors du chargement du fichier (ObjLoader)");

    uint32 size2 =  (uint32)file2.tellg();
    file2.seekg(0, std::ios::beg);

    int8* buffer2 = new int8[size2];
    file2.read(buffer2,size2);
    file2.close();

    M2SkinHeader _header;
    std::memcpy(&_header,buffer2,sizeof(_header));
    M2ModelTextureDef *texdef = (M2ModelTextureDef*)(buffer + header.ofsTextures);


    uint16* indexlook = (uint16*)(buffer2+_header.ofsIndices);
    uint16* triangles = (uint16*)(buffer2+_header.ofsTriangles);


    for(uint32 i = 0; i < _header.nTriangles; i++)
        indices.push_back(indexlook[triangles[i]]);

    for(uint32 i = 0; i < header.nVertices; i++)
    {
        vertices[i].position = m2vertex[i].pos;
        vertices[i].normal = normalize(m2vertex[i].normal);
        vertices[i].texCoords = m2vertex[i].texcoords;
        vertices[i].color = -1;
    }
    delete[] buffer;
    delete[] buffer2;
    delete[] m2vertex;


    Model* model = new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
    Texture tex;
    tex.CreateFromFile(filename + ".png",PXF_A8R8G8B8);
    return model;
}

void M2Loader::SaveToFile(const Model* object, const std::string& filename)
{

}

void M2Loader::OnError()
{
    throw Exception("");
}

