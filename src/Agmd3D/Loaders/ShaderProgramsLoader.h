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
#include <Core/Shader/ShaderProgram.h>
#include <Core/Enums.h>


namespace Agmd
{
    enum ShaderPreprocessor
    {
        PREPROCESSOR_UNKNOW,
        PREPROCESSOR_INCLUDE,
        PREPROCESSOR_REVISION
    };

    class ShaderProgramsLoader : public Loader<BaseShaderProgram>
    {
    public :

        ShaderProgramsLoader();

        ~ShaderProgramsLoader();

        virtual BaseShaderProgram* LoadFromFile(const std::string& filename);

    private :

        std::string LoadShader(const std::string& filename, const std::string& parentdir = "");

        ShaderPreprocessor preprocessor(const std::string& instruction);
        static void OnError();

    };

}


#endif /* _SHADERPROGRAMSLOADER_H_ */
