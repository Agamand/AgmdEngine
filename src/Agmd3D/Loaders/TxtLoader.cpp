/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/TxtLoader.h>
#include <Core/Renderer.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>

namespace Agmd
{

    TxtLoader::TxtLoader()
    {}

    TxtLoader::~TxtLoader()
    {}

    char* TxtLoader::LoadFromFile(const std::string& filename)
    {
        char *src = NULL;
        a_uint32 size;
        std::ifstream file(filename, std::ios::in);
    
        if (!file)
            throw LoadingFailed(filename,"Erreur lors du chargement du fichier (TxtLoader)");

        file.seekg(0,std::ios_base::end);
        size = (a_uint32)file.tellg();
        file.seekg(0,std::ios_base::beg);

        src = new char[size+1];
        file.read(src,size);
        src[size] = '\0';
        file.close();
    
        return src;
    }

    void TxtLoader::OnError()
    {
        throw Exception("");
    }


}
