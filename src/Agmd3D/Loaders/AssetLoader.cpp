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

namespace Agmd
{

    AssetLoader::AssetLoader()
    {}

    AssetLoader::~AssetLoader()
    {}

    SceneNode* AssetLoader::LoadFromFile(const std::string& filename)
    {
      return NULL;
    }

    void AssetLoader::SaveToFile(const Model* object, const std::string& filename)
    {

    }

	void AssetLoader::OnError()
	{

	}

}