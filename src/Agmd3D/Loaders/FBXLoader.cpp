/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/FBXLoader.h>
#include <Core/Driver.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>


namespace Agmd
{

    FBXLoader::FBXLoader()
    {}

    FBXLoader::~FBXLoader()
    {}

    Model* FBXLoader::LoadFromFile(const std::string& filename)
    {

        return NULL;
    }

    void FBXLoader::SaveToFile(const Model* object, const std::string& filename)
    {

    }


    void FBXLoader::OnError()
    {
        throw Exception("");
    }


}