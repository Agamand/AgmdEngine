/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/ShaderPipelineLoader.h>
#include <Core/Renderer.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>

#include <Utilities\File.h>

namespace Agmd
{

    ShaderPipelineLoader::ShaderPipelineLoader()
    {}

    ShaderPipelineLoader::~ShaderPipelineLoader()
    {}

    ShaderPipeline* ShaderPipelineLoader::LoadFromFile(const std::string& filename)
    {
        std::ifstream file;
        std::string str;
        try
        {
            file.open(filename,std::ios::in);

            file >> str;

            if(GetToken(str) != TOKEN_SHADERPIPELINE)
                throw LoadingFailed(filename,"First Token must be ShaderPipeline");
            //if(GetToken(str) != TOKEN_VARIABLE)
                //throw LoadingFailed(filename,"Error token at ");
        }catch (LoadingFailed execption)
        {
            file.close();
            return nullptr;
        }



        return nullptr;
    }

    void ShaderPipelineLoader::Parse(std::string str)
    {
        
    }

    Token ShaderPipelineLoader::GetToken(std::string str)
    {
        return Token::TOKEN_PASS;
    }

    void ShaderPipelineLoader::OnError()
    {
        throw Exception("");
    }


}
