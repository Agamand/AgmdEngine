/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef SHADERSLOADER_H
#define SHADERSLOADER_H

#include <Core/Loader.h>
#include <Core/Shader/Shader.h>
#include <Core/Enums.h>


namespace Agmd
{
    class ShadersLoader : public Loader<BaseShader>
    {
    public :

        ShadersLoader(TShaderType type);

        ~ShadersLoader();

        virtual BaseShader* LoadFromFile(const std::string& filename);

    private :

        static void OnError();

        TShaderType m_Type;
    };

}


#endif //SHADERSLOADER_H
