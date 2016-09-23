/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/ObjLoader.h>
#include <Core/Driver.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>


namespace Agmd
{
    ObjLoader::ObjLoader()
    {
    }

    ObjLoader::~ObjLoader()
    {
    }

    Model* ObjLoader::LoadFromFile(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::in);
        if (!file)
            throw LoadingFailed(filename, "Error on loading file (ObjLoader)");

        a_uint32 size = (a_uint32)file.tellg();
        file.seekg(0, std::ios::beg);

        a_vector<vec3> position;
        a_vector<vec2> texPos;
        a_vector<vec3> normal;

        a_vector<Model::TVertex> vertices;
        a_vector<FaceVertex> faceVertex;
        a_vector<Model::TIndex> indices;

        while (skipCommentLine(file))
        {
            if (!processLine(position, texPos, normal, faceVertex, file))
                break;
        }

        //         for(a_uint32 i = 0; i < position.size(); i++)
        //         {
        //             Model::TVertex vertex;
        //             vertex.position = position[i];
        //             vertex.texCoords = texPos.size() > i ? texPos[i] : vec2();
        //             vertex.normal = normal.size() > i ? normal[i] : vec3();
        //             vertices.push_back(vertex);
        //         }
        for (a_uint32 i = 0; i < faceVertex.size(); i++)
        {
            Model::TVertex vertex;
            FaceVertex& face = faceVertex[i];
            vertex.position = position[faceVertex[i].vindex];
            vertex.texCoords = texPos.size() > faceVertex[i].tindex ? texPos[faceVertex[i].tindex] : vec2();
            vertex.normal = normal.size() > faceVertex[i].nindex ? normal[faceVertex[i].nindex] : vec3();
            vertices.push_back(vertex);
        }
        if (indices.size())
            return new Model(&vertices[0], vertices.size(), &indices[0], indices.size());
        return new Model(&vertices[0], vertices.size());
    }

    void ObjLoader::SaveToFile(const Model* object, const std::string& filename)
    {
    }

    bool ObjLoader::skipCommentLine(std::istream& file)
    {
        char next;
        while (file >> std::skipws >> next)
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
        while ((file >> next) && ('\n' != next));
    }

    struct FaceVertex
    {
        int vindex;
        int tindex;
        int nindex;
    };

    bool ObjLoader::processLine(a_vector<vec3>& position,a_vector<vec2>& texPos,a_vector<vec3>& normal,a_vector<FaceVertex>& faceVertex, std::istream& is)
    {
        std::string value;
        a_int32 index = 0,
            tindex = 0,
            nindex = 0;
        a_int32 temp = 0;

        if (!(is >> value))
            return false;

        if (value == "v")
        {
            float x, y, z;
            is >> x >> y >> z;
            vec3 pos(x, y, z);
            position.push_back(pos);
        }
        else if (value == "vt")
        {
            float x, y;
            is >> x >> y;
            vec2 pos(x, y);
            texPos.push_back(pos);
        }
        else if (value == "vn")
        {
            float x, y, z;
            is >> x >> y >> z;
            vec3 pos(x, y, z);
            normal.push_back(pos);
        }
        else if (value == "f")
        {
            int i = 0;
            for (char c; i < 10; ++i)
            {
                //std::string str = is.;
                is >> index >> c >> tindex >> c >> nindex;

                FaceVertex face;
                face.vindex = index - 1;
                face.tindex = tindex - 1;
                face.nindex = nindex - 1;
                if (!is.good())
                    break;

                //indices.push_back(index-1);
                faceVertex.push_back(face);
                index = 0;
            }
            is.clear();
        }
        else skipLine(is);

        return true;
    }

    void ObjLoader::OnError()
    {
        throw Exception("");
    }
}
