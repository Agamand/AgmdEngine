/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/AssetLoader.h>
#include <Core/Driver.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <Core/SceneNode/MeshNode.h>
#include <Core/Model/Model.h>
#include <vector>

namespace Agmd
{
    AssetLoader::AssetLoader()
    {
    }

    AssetLoader::~AssetLoader()
    {
    }

    MeshNode* ProcessMesh(aiMesh* mesh)
    {
        a_vector<Model::TVertex> vertices;
        a_vector<Model::TIndex> indices;
        for (a_uint32 i = 0; i < mesh->mNumVertices; i++)
        {
            Model::TVertex vertex;
            aiVector3D& v = mesh->mVertices[i];
            vertex.position = vec3(v.x, v.y, v.z);

            if (mesh->HasTextureCoords(0))
            {
                aiVector3D& t = mesh->mTextureCoords[0][i];
                vertex.texCoords = vec2(t.x, t.y);
            }
            else
            {
                vertex.texCoords = vec2(0.f);
            }

            if (mesh->HasNormals())
            {
                aiVector3D& n = mesh->mNormals[i];
                vertex.normal = vec3(n.x, n.y, n.z);
            }
            else
            {
                vertex.normal = vec3(0.f);
            }
            vertex.color = -1;
            vertices.push_back(vertex);
        }
        for (a_uint32 i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace& face = mesh->mFaces[i];
            for (a_uint32 j = 0; j < face.mNumIndices; ++j)
                indices.push_back(face.mIndices[j]);
        }
        if (indices.size())
            return new MeshNode(new Model(&vertices[0], vertices.size(), &indices[0], indices.size()));
        else
            return new MeshNode(new Model(&vertices[0], vertices.size()));
    }

    void ProcessNode(aiNode* node, const aiScene* scene, SceneNode** _node)
    {
        (*_node) = new SceneNode();
        for (a_uint32 i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            (*_node)->addChild(ProcessMesh(mesh));
        }
        for (a_uint32 i = 0; i < node->mNumChildren; i++)
        {
            SceneNode* snode;
            ProcessNode(node->mChildren[i], scene, &snode);
            (*_node)->addChild(snode);
        }
    }

    SceneNode* AssetLoader::LoadFromFile(const std::string& filename)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filename,
                                                 aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_GenNormals |
                                                 aiProcess_SortByPType);
        if (!scene)
            return NULL;
        SceneNode* node;
        ProcessNode(scene->mRootNode, scene, &node);
        return node;
    }

    void AssetLoader::SaveToFile(const Model* object, const std::string& filename)
    {
    }

    void AssetLoader::OnError()
    {
    }
}
