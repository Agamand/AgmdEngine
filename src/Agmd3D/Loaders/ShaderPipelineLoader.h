/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SHADERPROGRAMSLOADER_H_
#define _SHADERPROGRAMSLOADER_H_

#include <Core/Loader.h>
#include <Core/Shader/ShaderPipeline.h>
#include <Core/Enums.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>

namespace Agmd
{

    #define STR_TOKEN_SHADERPIPELINE "shaderpipeline"
    #define STR_TOKEN_SUBROUTINE "subroutine"
    #define STR_TOKEN_GLSLBEGIN "glslbegin"
    #define STR_TOKEN_GLSLEND "glslend"
    #define STR_TOKEN_PROPERTIES "properties"
    #define STR_TOKEN_PASS "pass"
    #define STR_TOKEN_BRACE_OPEN "{"
    #define STR_TOKEN_BRACE_CLOSE "}"
    #define STR_TOKEN_INSTRUCTION_END ";"

    enum Token
    {
        TOKEN_UNKNOWN,
        TOKEN_SHADERPIPELINE,
        TOKEN_SUBROUTINE,
        TOKEN_PROPERTIES,
        TOKEN_GLSLBEGIN,
        TOKEN_GLSLEND,
        TOKEN_PASS,
        TOKEN_BRACE_OPEN,
        TOKEN_BRACE_CLOSE,
        TOKEN_INSTRUCTION_END
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
        void ParseProperties(const std::string& str);
        void ParseSubRoutine(const std::string& str);

        std::vector<std::string> m_properties;
        std::map<std::string,std::string> m_subroutine;
    };

}


#endif /* _SHADERPROGRAMSLOADER_H_ */
