/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/ShaderPipelineLoader.h>
#include <Core/Renderer.h>
#include <iostream>
#include <string>
#include <fstream>

#include <Utilities\File.h>

namespace Agmd
{
	const char* _normal = "vec3 normal(){return vec3(1,0,0);}";
	const char* _diffuse = "vec4 diffuse(){return vec4(1);}";
	
    ShaderPipelineLoader::ShaderPipelineLoader()
    {
		d_subroutine["diffuse"] = _diffuse;
		d_subroutine["normal"] = _normal;
	}

    ShaderPipelineLoader::~ShaderPipelineLoader()
    {}

    ShaderPipeline* ShaderPipelineLoader::LoadFromFile(const std::string& filename)
    {
        std::ifstream file;
        std::string str;
        std::string shadername;
        try
        {
            file.open(filename,std::ios::in || std::ios::binary);

            file >> str;

            if(GetToken(str) != TOKEN_SHADERPIPELINE)
                throw ParserFail(filename,"First Token must be ShaderPipeline");

            file >> shadername;
            file >> str;
            if(GetToken(str) != TOKEN_BRACE_OPEN)
                throw ParserFail(filename,"");
            bool endfile = false;
            while(!endfile)
            {
                file >> str;
                switch(GetToken(str))
                {
                case TOKEN_PROPERTIES:
                    ParseProperties(file);
                    break;
                case TOKEN_UNIFORMINPUT:
                    ParseUniform(file);
                    break;
                case TOKEN_SUBROUTINE:
                    ParseSubRoutine(file);
                    break;
                case TOKEN_BRACE_CLOSE:
                    endfile = true;
                    break;
                default:
                    throw ParserFail(filename,"");
                    break;
                }
            }

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

        return new ShaderPipeline();
    }

    void ShaderPipelineLoader::ParseProperties(std::ifstream& stream)
    {
        std::string str;
        stream >> str;

        if(GetToken(str) != TOKEN_BRACE_OPEN)
            throw ParserFail("","");

        stream >> str;
        Properties p;
        Token t;
        while( ( t = GetToken(str) ) != TOKEN_BRACE_CLOSE)
        {
            switch(GetToken(str))
            {
            case TOKEN_RENDERTYPE:
                stream >> str;
                p._type = TYPE_RENDER;
                p.value = str;
                m_properties.push_back(p);
                break;
            case TOKEN_USE:
                stream >> str;
                p._type = TYPE_USE;
                p.value = str;
                m_properties.push_back(p);
                break;
            default:
                SkipLine(stream);
            }
            stream >> str;
        }
    }

    void  ShaderPipelineLoader::ParseSubRoutine(std::ifstream& stream)
    {
        std::string str;
        stream >> str;
        std::string name = str;

        stream >> str;
        if(GetToken(str) != TOKEN_BRACE_OPEN)
            throw ParserFail("","");

        stream >> str;
        if(GetToken(str) != TOKEN_GLSLBEGIN)
            throw ParserFail("","");

        
        int begin = stream.tellg(), end = 0;
        while(stream >> str && GetToken(str) != TOKEN_GLSLEND);
        end = -7+stream.tellg();
        stream.seekg(begin,stream.beg);
        char* _str = new char[end-begin+1];
        int i =0;
        std::memcpy(_str,&i,end-begin+1);
        while(stream.tellg() < end)
            _str[i++] = stream.get();
        std::string subroutine(_str);
        stream >> str;
        stream >> str;
        if(GetToken(str) != TOKEN_BRACE_CLOSE)
            throw ParserFail("","");

        m_subroutine[name] = subroutine;
    }
    void ShaderPipelineLoader::ParseUniform(std::ifstream& stream)
    {
        std::string str;
        stream >> str;

        if(GetToken(str) != TOKEN_BRACE_OPEN)
            throw ParserFail("","");

        stream >> str;

        while(GetToken(str) != TOKEN_BRACE_CLOSE)
        {
            std::string varname = str.substr(0, str.find_first_of('('));
            std::string vartype = str.substr(str.find_first_of('(')+1,str.find_last_of(')')-1);
            stream >> str;
            std::string defaultvalue = "";
            if(str.c_str()[0] == '=')
            {
                stream >> str;
                defaultvalue = str;
                stream >> str;
            }
            AddUniform(varname,vartype,defaultvalue);
        }
    }
    Token ShaderPipelineLoader::GetToken(const std::string& str)
    {
        std::string _str(str);
        std::transform(_str.begin(),_str.end(),_str.begin(), ::tolower);
        if(!_str.compare(STR_TOKEN_SHADERPIPELINE))
            return Token::TOKEN_SHADERPIPELINE;
        if(!_str.compare(STR_TOKEN_PROPERTIES))
            return Token::TOKEN_PROPERTIES;
        if(!_str.compare(STR_TOKEN_USE))
            return Token::TOKEN_USE;
        if(!_str.compare(STR_TOKEN_RENDERTYPE))
            return Token::TOKEN_RENDERTYPE;
        if(!_str.compare(STR_TOKEN_SUBROUTINE))
            return Token::TOKEN_SUBROUTINE;
        if(!_str.compare(STR_TOKEN_UNIFORMINPUT))
            return Token::TOKEN_UNIFORMINPUT;
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

    UniformType ShaderPipelineLoader::GetUniformType(const std::string& str )
    {
        std::string _str(str);
        std::transform(_str.begin(),_str.end(),_str.begin(), ::tolower);

        if(!_str.compare(TYPE_FLOAT))
            return UniformType::UNIFORM_FLOAT;

        if(!_str.compare(TYPE_TEXTURE2D))
            return UniformType::UNIFORM_SAMPLER2D;
        return UniformType::UNIFORM_UNKNOWN;
    }

    void ShaderPipelineLoader::AddUniform(const std::string& name, const std::string& type, const std::string& defaultvalue)
    {
        UniformType _type = GetUniformType(type);
        Uniform uniform;
        uniform._type = _type;
        uniform.varname = name;
        switch(_type)
        {
        case UNIFORM_FLOAT:
            uniform._defaultvalue.fvalue[0] =  atof(defaultvalue.c_str());
            break;
        default:
            std::strncpy(uniform._defaultvalue.svalue,defaultvalue.c_str(), 20);
        }

    }

    void ShaderPipelineLoader::SkipLine(std::ifstream& stream)
    {
        char c;
        while(stream.read(&c,1) && c != '\n');
    }

    void ShaderPipelineLoader::OnError()
    {
        throw Exception("");
    }


}
