/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLSHADERPROGRAM_H_
#define _GLSHADERPROGRAM_H_

#include <Config\Fwd.h>
#include <Core\Shader/BaseShaderProgram.h>
#include <Core/Buffer/BaseBuffer.h>
#include <Renderer\OpenGL\GlShader.h>
#include <Core\Enums.h>
#include <CommonDefines.h>
#include <string>
#include <map>
#include <Container/Vector.h>

namespace Agmd
{
    class GLShaderProgram : public BaseShaderProgram
    {
    public:

        enum ParameterType
        {
            PARAMETER_NOFOUND,
            PARAMETER_UNIFORM,
            PARAMETER_ATTRIBUT,
            PARAMETER_UNIFORM_BLOCK
        };

        struct Parameter
        {
            a_uint32 loc;
            a_uint32 size;
            a_uint32 typeValue;
            ParameterType type;
        };

        typedef std::map<std::string, Parameter> ParameterMap;
        typedef a_vector<Parameter> APIMatrix;

        GLShaderProgram(a_uint32 id);
        virtual ~GLShaderProgram();

        virtual void SetParameter(const std::string& name, float value) const;
        virtual void SetParameter(const std::string& name, const vec2& value) const;
        virtual void SetParameter(const std::string& name, const vec3& value) const;
        virtual void SetParameter(const std::string& name, const vec4& value) const;

        virtual void SetParameter(const std::string& name, int value) const;
        virtual void SetParameter(const std::string& name, const ivec2& value) const;
        virtual void SetParameter(const std::string& name, const ivec3& value) const;
        virtual void SetParameter(const std::string& name, const ivec4& value) const;

        virtual void SetParameter(const std::string& name, const mat2& value) const;
        virtual void SetParameter(const std::string& name, const mat3& value) const;
        virtual void SetParameter(const std::string& name, const mat4& value) const;

        virtual void SetParameter(const std::string& name, float* value, a_uint32 count) const;
        virtual void SetParameter(const std::string& name, vec2* value, a_uint32 count) const;
        virtual void SetParameter(const std::string& name, vec3* value, a_uint32 count) const;
        virtual void SetParameter(const std::string& name, vec4* value, a_uint32 count) const;
        virtual void SetParameter(const std::string& name, mat4* value, a_uint32 count) const;

        virtual void SetParameter(TMatrixType type, const mat4& value) const;

        virtual void SetParameter(const std::string& name, const a_uint32 bindPoint) const;

        virtual void Use(bool) const;
        void UniformShaderInfo();
        static int getUniformByteSize(int uniSize, int uniType, int uniArrayStride, int uniMatStride);
        static void Init();
    private:
        static std::map<int, std::string> GLShaderProgram::spGLSLType;
        static std::map<int, int> GLShaderProgram::spGLSLTypeSize;
        static bool s_init;
        void SetupShader();

        const Parameter& GetParameter(const std::string& name) const;

        ParameterMap m_UniformMap;
        ParameterMap m_AttributMap;
        Parameter m_APIMatrix[MAX_APIMATRIX];
        Parameter m_defaultParameter;
        a_uint32 m_id;
    };
}

#endif /* _GLSHADERPROGRAM_H_ */
