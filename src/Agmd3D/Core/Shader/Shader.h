/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef SHADER_H
#define SHADER_H

//==========================================================
// En-têtes
//==========================================================
#include <Config/Fwd.h>
#include <Core/Shader/BaseShader.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Utilities/SmartPtr.h>
#include <string>

using namespace AgmdUtilities;
namespace Agmd
{
    class AGMD3D_EXPORT Shader
    {
    public :

        void LoadFromFile(const std::string& filename);

        void CreateFromSrc(const std::string& src, TShaderType type);

        void Unload();

        const BaseShader* GetShader() const;

    private :

        SmartPtr<BaseShader, ResourceCOM> m_Shader;
    };

}


#endif //SHADER_H