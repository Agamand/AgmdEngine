/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/ShaderProgramsLoader.h>
#include <Core/Renderer.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>

#include <Utilities\File.h>

namespace Agmd
{

    ShaderProgramsLoader::ShaderProgramsLoader()
    {}

    ShaderProgramsLoader::~ShaderProgramsLoader()
    {}

    BaseShaderProgram* ShaderProgramsLoader::LoadFromFile(const std::string& filename)
    {
        std::string buffer = LoadShader(filename);
        BaseShader* shader[5];

        shader[0] = Renderer::Get().CreateShader(buffer, SHADER_VERTEX);
        shader[1] = Renderer::Get().CreateShader(buffer, SHADER_TESS_CONTROL);
        shader[2] = Renderer::Get().CreateShader(buffer, SHADER_TESS_EVALUATION);
        shader[3] = Renderer::Get().CreateShader(buffer, SHADER_GEOMETRY);
        shader[4] = Renderer::Get().CreateShader(buffer, SHADER_PIXEL);

        return Renderer::Get().CreateShaderProgram(shader[0],shader[2],shader[1],shader[3],shader[4]);
    }

    std::string ShaderProgramsLoader::LoadShader(const std::string& filename, const std::string& parentdir)
    {
        
        std::ifstream file;
        if(parentdir.empty())
            file.open(filename, std::ios::in);
        else
        {
            File f(parentdir);
            file.open(f.Path()+"\\"+filename, std::ios::in);
        }
        std::string str_shader = "", buffer = "";
        if(!file)
            throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ShaderProgramsLoader)");
        char cbuffer = 0;
        while(file.read(&cbuffer,1))
        {
            std::string instruction = "";
            std::string value = "";
            switch(cbuffer)
            {
            case '#':


                while(file.read(&cbuffer,1) && cbuffer != ' ')
                    instruction += cbuffer;

                while(file.read(&cbuffer,1) && cbuffer != '\n')
                    value += cbuffer;

                value += '\n';
                switch(preprocessor(instruction))
                {
                case PREPROCESSOR_INCLUDE:
                    buffer += LoadShader(value.substr(value.find_first_of('"')+1, value.find_last_of('"')-1),filename);
                    break;
                default:
                    buffer += "#" + instruction + " " + value + "\n";
                    break;
                }
                break;
            case '\n':
                buffer +=cbuffer;
                break;
            default:
                buffer +=cbuffer;
                while(file.read(&cbuffer,1) && cbuffer != '\n')
                    buffer +=cbuffer;

                buffer += '\n';
                break;
            }

            str_shader += buffer;
            buffer = "";
            
        }
        return str_shader;
    }

    ShaderPreprocessor ShaderProgramsLoader::preprocessor(const std::string& instruction)
    {
        if(!instruction.compare("include"))
        {
            return PREPROCESSOR_INCLUDE;
        }

        if(!instruction.compare("revision"))
        {
            return PREPROCESSOR_REVISION;
        }
        return PREPROCESSOR_UNKNOW;
    }

    void ShaderProgramsLoader::OnError()
    {
        throw Exception("");
    }


}
