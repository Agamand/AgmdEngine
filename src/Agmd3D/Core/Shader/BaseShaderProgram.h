/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef BASESHADERPROGRAM_H
#define BASESHADERPROGRAM_H

#include <Config/Fwd.h>
#include <Core/Enums.h>
#include <Core/Shader/BaseShader.h>
#include <Core/Resource.h>
#include <Matrix4.h>

#include <AgmdDefines.h>

#include <map>


namespace Agmd
{

    class AGMD3D_EXPORT BaseShaderProgram : public Resource
    {
    public :

        virtual ~BaseShaderProgram();

        virtual void SetParameter(const std::string& name, float value) const = 0;
        virtual void SetParameter(const std::string& name, const vec2& value) const = 0;
        virtual void SetParameter(const std::string& name, const vec3& value) const = 0;
        virtual void SetParameter(const std::string& name, const vec4& value) const = 0;

        virtual void SetParameter(const std::string& name, int value) const = 0;
        virtual void SetParameter(const std::string& name, const ivec2& value) const = 0;
        virtual void SetParameter(const std::string& name, const ivec3& value) const = 0;
        virtual void SetParameter(const std::string& name, const ivec4& value) const = 0;

        virtual void SetParameter(const std::string& name, const mat2& value) const = 0;
        virtual void SetParameter(const std::string& name, const mat3& value) const = 0;
        virtual void SetParameter(const std::string& name, const mat4& value) const = 0;

        virtual void SetParameter(const std::string& name, float* value, uint32 count) const = 0;
        virtual void SetParameter(const std::string& name, vec2* value,  uint32 count) const = 0;
        virtual void SetParameter(const std::string& name, vec3* value,  uint32 count) const = 0;
        virtual void SetParameter(const std::string& name, vec4* value,  uint32 count) const = 0;
        virtual void SetParameter(const std::string& name, mat4* value,  uint32 count) const = 0;

        virtual void SetParameter(TMatrixType type, const mat4& value) const = 0;

        virtual void SetParameter(const std::string& name, const uint32 bindpoint) const = 0;
        
        virtual void Use(bool) const = 0;

    protected :
        friend class ShaderProgram;

        BaseShaderProgram();
    };
}


#endif //BASESHADERPROGRAM