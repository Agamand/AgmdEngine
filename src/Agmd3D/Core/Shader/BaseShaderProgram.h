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

    class AGMD_EXPORT BaseShaderProgram : public Resource
    {
    public :

        virtual ~BaseShaderProgram();

		virtual void SetParameter(std::string name, float value) const = 0;
		virtual void SetParameter(std::string name, vec2 value) const = 0;
		virtual void SetParameter(std::string name, vec3 value) const = 0;
		virtual void SetParameter(std::string name, vec4 value) const = 0;

		virtual void SetParameter(std::string name, int value) const = 0;
		virtual void SetParameter(std::string name, ivec2 value) const = 0;
		virtual void SetParameter(std::string name, ivec3 value) const = 0;
		virtual void SetParameter(std::string name, ivec4 value) const = 0;

		virtual void SetParameter(std::string name, mat2 value) const = 0;
		virtual void SetParameter(std::string name, mat3 value) const = 0;
		virtual void SetParameter(std::string name, mat4 value) const = 0;

		virtual void SetParameter(std::string name,	float* value, uint32 count) const = 0;
		virtual void SetParameter(std::string name,	vec2* value, uint32 count) const = 0;
		virtual void SetParameter(std::string name,	vec3* value, uint32 count) const = 0;
		virtual void SetParameter(std::string name,	vec4* value, uint32 count) const = 0;
		virtual void SetParameter(std::string name, mat4* value, uint32 count) const = 0;

		virtual void SetParameter(TMatrixType type,mat4 value) const = 0;

		virtual void SetParameter(std::string name, const BaseBuffer* buf) const = 0;

		virtual void Use(bool) const = 0;

    protected :
		friend class ShaderProgram;

		BaseShaderProgram();
    };
}


#endif //BASESHADERPROGRAM