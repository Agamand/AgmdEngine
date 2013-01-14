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
#include <sstream>

namespace Agmd
{

    #define STR_TOKEN_SHADERPIPELINE "shaderpipeline"
    #define STR_TOKEN_SUBROUTINE "subshader"
    #define STR_TOKEN_PASS "pass"
    #define STR_TOKEN_GLSLBEGIN ""
    #define STR_TOKEN_GLSLEND ""
    #define STR_TOKEN_PROPERTIES "properties"

    enum Token
    {
        TOKEN_SHADERPIPELINE,
        TOKEN_SUBSHADER,
        TOKEN_PASS,
    };

    class ShaderPipelineLoader : public Loader<ShaderPipeline>
    {
    public :

        ShaderPipelineLoader();
        ~ShaderPipelineLoader();
        virtual ShaderPipeline* LoadFromFile(const std::string& filename);

    private :
        static void OnError();
        Token GetToken(std::string str);
        void Parse(std::string str);

    };

}


#endif /* _SHADERPROGRAMSLOADER_H_ */
