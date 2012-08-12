#ifndef BASESHADERPROGRAM_H
#define BASESHADERPROGRAM_H

#include <Core/Enums.h>
#include <Core\BaseShader.h>
#include <Core/Resource.h>
#include <Maths/Matrix4.h>
#include <map>


namespace Agmd
{

    class AGMD_EXPORT BaseShaderProgram : public Resource
    {
    public :

        virtual ~BaseShaderProgram();

		virtual void SetParameter(std::string name, float value) = 0;
		virtual void SetParameter(std::string name, vec2 value) = 0;
		virtual void SetParameter(std::string name, vec3 value) = 0;
		virtual void SetParameter(std::string name, vec4 value) = 0;

		virtual void SetParameter(std::string name, int value) = 0;
		virtual void SetParameter(std::string name, ivec2 value) = 0;
		virtual void SetParameter(std::string name, ivec3 value) = 0;
		virtual void SetParameter(std::string name, ivec4 value) = 0;

		virtual void SetParameter(std::string name, mat2 value) = 0;
		virtual void SetParameter(std::string name, mat3 value) = 0;
		virtual void SetParameter(std::string name, mat4 value) = 0;

		virtual void Use(bool) = 0;

    protected :
		friend class ShaderProgram;

		BaseShaderProgram();
    };
}


#endif //BASESHADERPROGRAM