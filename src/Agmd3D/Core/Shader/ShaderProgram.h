/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Config/Fwd.h>
#include <Core/Shader/BaseShaderProgram.h>
#include <Utilities/SmartPtr.h>

#ifndef _SHADERPROGRAM_H_
#define _SHADERPROGRAM_H_

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD3D_EXPORT ShaderProgram
    {
    public :

        void Create(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag);

        void LoadFromFile(const std::string& filename);

        void ReloadFromFile(const std::string& filename);

        void Unload();

        const BaseShaderProgram* GetShaderProgram() const;

        inline void Enable() const;

        inline void Disable() const;

        template <class T>
        inline void SetParameter(TMatrixType type, T value) const;
        template <class T>
        inline void SetParameter(const std::string& name, T value) const;
        template <class T>
        inline void SetParameter(const std::string& name, T value, a_uint32 size) const;
        template <class T>
        inline void SetParameter(const std::string& name, Buffer<T> buf);

    private :
        SmartPtr<BaseShaderProgram, ResourceCOM> m_ShaderProgram;
    };

#include "ShaderProgram.inl"
}

#endif /* _SHADERPROGRAM_H_ */
