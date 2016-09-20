/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/ShadersLoader.h>
#include <Core/Driver.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>

namespace Agmd
{

    ShadersLoader::ShadersLoader(TShaderType type) :
    m_Type(type)
    {}

    ShadersLoader::~ShadersLoader()
    {}

    BaseShader* ShadersLoader::LoadFromFile(const std::string& filename)
    {
        char *src = NULL;
        a_uint32 size;
        std::ifstream file(filename, std::ios::in);
    
        if (!file)
            throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ShadersLoader)");

        file.seekg(0,std::ios_base::end);
        size = (a_uint32)file.tellg();
        file.seekg(0,std::ios_base::beg);

        src = new char[size+1];
    
        file.read(src,size);
        src[size] = '\0';
        std::string _src(src);
        delete src;
        file.close();
    
        return Driver::Get().CreateShader(_src, m_Type);
    }

    void ShadersLoader::OnError()
    {
        throw Exception("");
    }


}
