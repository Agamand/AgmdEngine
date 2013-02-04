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



        }catch(ParserFail e)
        {
            file.close();
            return NULL;
        }
        catch (LoadingFailed e)
        {
            file.close();
            return NULL;
        }

        m_properties.clear();
        m_subroutine.clear();

        return NULL;
    }

    void ShaderPipelineLoader::ParseProperties(const std::string& str)
    {
        
    }

    void ShaderPipelineLoader::ParseSubRoutine(const std::string& str)
    {
        
    }

    Token ShaderPipelineLoader::GetToken(const std::string& str)
    {
        std::string _str(str);
        std::transform(_str.begin(),_str.end(),_str.begin(), ::tolower);
        if(!_str.compare(STR_TOKEN_SHADERPIPELINE))
            return Token::TOKEN_SHADERPIPELINE;
        if(!_str.compare(STR_TOKEN_PROPERTIES))
            return Token::TOKEN_PROPERTIES;
        if(!_str.compare(STR_TOKEN_SUBROUTINE))
            return Token::TOKEN_SUBROUTINE;
        if(!_str.compare(STR_TOKEN_GLSLBEGIN))
            return Token::TOKEN_GLSLBEGIN;
        if(!_str.compare(STR_TOKEN_GLSLEND))
            return Token::TOKEN_GLSLEND;
        if(!_str.compare(STR_TOKEN_PASS))
            return Token::TOKEN_PASS;
        if(!_str.compare(STR_TOKEN_BRACE_OPEN))
            return Token::TOKEN_BRACE_OPEN;
        if(!_str.compare(STR_TOKEN_BRACE_CLOSE))
            return Token::TOKEN_BRACE_CLOSE;
        if(!_str.compare(STR_TOKEN_INSTRUCTION_END))
            return Token::TOKEN_INSTRUCTION_END;
        return Token::TOKEN_UNKNOWN;
    }

    void ShaderPipelineLoader::OnError()
    {
        throw Exception("");
    }


}
