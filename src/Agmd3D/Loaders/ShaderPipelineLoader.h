/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SHADERPIPELINEPROGRAMSLOADER_H_
#define _SHADERPIPELINELOADER_H_

#include <Core/Loader.h>
#include <Core/Shader/ShaderPipeline.h>
#include <Core/Enums.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>

namespace Agmd
{

    #define STR_TOKEN_SHADERPIPELINE    "shaderpipeline"
    #define STR_TOKEN_SUBROUTINE        "subroutine"
    #define STR_TOKEN_UNIFORMINPUT      "uniforminput"
    #define STR_TOKEN_GLSLBEGIN         "glslbegin"
    #define STR_TOKEN_GLSLEND           "glslend"
    #define STR_TOKEN_PROPERTIES        "properties"
    #define STR_TOKEN_PASS              "pass"
    #define STR_TOKEN_BRACE_OPEN        "{"
    #define STR_TOKEN_BRACE_CLOSE       "}"
    #define STR_TOKEN_INSTRUCTION_END   ";"


    // PROPERTIES TOKEN
    #define STR_TOKEN_RENDERTYPE        "rendertype"
    #define STR_TOKEN_USE               "use"

    //UNIFORM TOKEN
    #define STR_TOKEN_FLOAT             "float"
    #define STR_TOKEN_TEXTURE2D         "texture2D"

    enum Token
    {
        TOKEN_UNKNOWN,
        TOKEN_SHADERPIPELINE,
        TOKEN_UNIFORMINPUT,
        TOKEN_SUBROUTINE,
        TOKEN_PROPERTIES,
        TOKEN_GLSLBEGIN,
        TOKEN_GLSLEND,
        TOKEN_PASS,
        TOKEN_BRACE_OPEN,
        TOKEN_BRACE_CLOSE,
        TOKEN_INSTRUCTION_END,
        TOKEN_RENDERTYPE,
        TOKEN_USE,
        TOKEN_FLOAT,
        TOKEN_TEXTURE2D
    };

    enum PropertiesType
    {
        TYPE_RENDER,
        TYPE_USE
    };

    struct Properties
    {
        PropertiesType _type;
        std::string value;
    };
    enum UniformType
    {
        UNIFORM_UNKNOWN,
        UNIFORM_FLOAT,
        UNIFORM_SAMPLER2D
    };

    #define TYPE_TEXTURE2D "texture2D"
    #define TYPE_FLOAT "float"
    #define TYPE_INT "int"
    struct Uniform
    {
        union Data
        {
            float fvalue[4];
            int ivalue;
            char svalue[20];
        };
        UniformType _type;
        std::string varname;
        Data _defaultvalue;

    };

    class ShaderPipelineLoader : public Loader<ShaderPipeline>
    {
    public :

        ShaderPipelineLoader();
        ~ShaderPipelineLoader();
        virtual ShaderPipeline* LoadFromFile(const std::string& filename);

    private :
        static void OnError();
        Token GetToken(const std::string& str);
        void ParseProperties(std::ifstream& str);
        void ParseUniform(std::ifstream& str);
        void ParseSubRoutine(std::ifstream& str);
        void SkipLine(std::ifstream& stream);
        UniformType GetUniformType(const std::string& str);
        void AddUniform(const std::string& name, const std::string& type, const std::string& defaultvalue);


        std::vector<Properties> m_properties;
        std::map<std::string,std::string> m_subroutine;
    };

}


#endif /* _SHADERPIPELINELOADER_H_ */
