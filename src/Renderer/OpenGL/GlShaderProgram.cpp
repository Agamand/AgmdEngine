/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlBuffer.h>
#include <Renderer\OpenGL\GlUniformBuffer.h>
#include <Renderer\OpenGL\GlRenderer.h>
#include <Debug/Logger.h>

namespace Agmd
{

    std::map<int, std::string> GLShaderProgram::spGLSLType;
    std::map<int, int> GLShaderProgram::spGLSLTypeSize;
    bool GLShaderProgram::s_init = false;

    void GLShaderProgram::Init()
    {
        if(s_init)
            return;
        s_init = true;
        spGLSLTypeSize[GL_FLOAT] = sizeof(float); 
        spGLSLTypeSize[GL_FLOAT_VEC2] = sizeof(float)*2; 
        spGLSLTypeSize[GL_FLOAT_VEC3] = sizeof(float)*3; 
        spGLSLTypeSize[GL_FLOAT_VEC4] = sizeof(float)*4; 
 
        spGLSLTypeSize[GL_DOUBLE] = sizeof(double); 
        spGLSLTypeSize[GL_DOUBLE_VEC2] = sizeof(double)*2; 
        spGLSLTypeSize[GL_DOUBLE_VEC3] = sizeof(double)*3; 
        spGLSLTypeSize[GL_DOUBLE_VEC4] = sizeof(double)*4; 
 
        spGLSLTypeSize[GL_SAMPLER_1D] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_3D] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_CUBE] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_1D_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_1D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_1D_ARRAY_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_ARRAY_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_MULTISAMPLE] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_CUBE_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_BUFFER] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_RECT] = sizeof(int); 
        spGLSLTypeSize[GL_SAMPLER_2D_RECT_SHADOW] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_1D] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_2D] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_3D] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_CUBE] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_1D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_2D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_2D_MULTISAMPLE] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_BUFFER] = sizeof(int); 
        spGLSLTypeSize[GL_INT_SAMPLER_2D_RECT] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_1D] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_3D] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_CUBE] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_BUFFER] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_SAMPLER_2D_RECT] = sizeof(int); 
        spGLSLTypeSize[GL_BOOL] = sizeof(int); 
        spGLSLTypeSize[GL_INT] = sizeof(int); 
        spGLSLTypeSize[GL_BOOL_VEC2] = sizeof(int)*2; 
        spGLSLTypeSize[GL_INT_VEC2] = sizeof(int)*2; 
        spGLSLTypeSize[GL_BOOL_VEC3] = sizeof(int)*3; 
        spGLSLTypeSize[GL_INT_VEC3] = sizeof(int)*3;  
        spGLSLTypeSize[GL_BOOL_VEC4] = sizeof(int)*4; 
        spGLSLTypeSize[GL_INT_VEC4] = sizeof(int)*4; 
 
        spGLSLTypeSize[GL_UNSIGNED_INT] = sizeof(int); 
        spGLSLTypeSize[GL_UNSIGNED_INT_VEC2] = sizeof(int)*2; 
        spGLSLTypeSize[GL_UNSIGNED_INT_VEC3] = sizeof(int)*2; 
        spGLSLTypeSize[GL_UNSIGNED_INT_VEC4] = sizeof(int)*2; 
 
        spGLSLTypeSize[GL_FLOAT_MAT2] = sizeof(float)*4; 
        spGLSLTypeSize[GL_FLOAT_MAT3] = sizeof(float)*9; 
        spGLSLTypeSize[GL_FLOAT_MAT4] = sizeof(float)*16; 
        spGLSLTypeSize[GL_FLOAT_MAT2x3] = sizeof(float)*6; 
        spGLSLTypeSize[GL_FLOAT_MAT2x4] = sizeof(float)*8; 
        spGLSLTypeSize[GL_FLOAT_MAT3x2] = sizeof(float)*6; 
        spGLSLTypeSize[GL_FLOAT_MAT3x4] = sizeof(float)*12; 
        spGLSLTypeSize[GL_FLOAT_MAT4x2] = sizeof(float)*8; 
        spGLSLTypeSize[GL_FLOAT_MAT4x3] = sizeof(float)*12; 
        spGLSLTypeSize[GL_DOUBLE_MAT2] = sizeof(double)*4; 
        spGLSLTypeSize[GL_DOUBLE_MAT3] = sizeof(double)*9; 
        spGLSLTypeSize[GL_DOUBLE_MAT4] = sizeof(double)*16; 
        spGLSLTypeSize[GL_DOUBLE_MAT2x3] = sizeof(double)*6; 
        spGLSLTypeSize[GL_DOUBLE_MAT2x4] = sizeof(double)*8; 
        spGLSLTypeSize[GL_DOUBLE_MAT3x2] = sizeof(double)*6; 
        spGLSLTypeSize[GL_DOUBLE_MAT3x4] = sizeof(double)*12; 
        spGLSLTypeSize[GL_DOUBLE_MAT4x2] = sizeof(double)*8; 
        spGLSLTypeSize[GL_DOUBLE_MAT4x3] = sizeof(double)*12; 
 
 
 
        spGLSLType[GL_FLOAT] = "GL_FLOAT"; 
        spGLSLType[GL_FLOAT_VEC2] = "GL_FLOAT_VEC2";  
        spGLSLType[GL_FLOAT_VEC3] = "GL_FLOAT_VEC3";  
        spGLSLType[GL_FLOAT_VEC4] = "GL_FLOAT_VEC4";  
        spGLSLType[GL_DOUBLE] = "GL_DOUBLE"; 
        spGLSLType[GL_DOUBLE_VEC2] = "GL_DOUBLE_VEC2";  
        spGLSLType[GL_DOUBLE_VEC3] = "GL_DOUBLE_VEC3";  
        spGLSLType[GL_DOUBLE_VEC4] = "GL_DOUBLE_VEC4";  
        spGLSLType[GL_SAMPLER_1D] = "GL_SAMPLER_1D";
        spGLSLType[GL_SAMPLER_2D] = "GL_SAMPLER_2D";
        spGLSLType[GL_SAMPLER_3D] = "GL_SAMPLER_3D";
        spGLSLType[GL_SAMPLER_CUBE] = "GL_SAMPLER_CUBE";
        spGLSLType[GL_SAMPLER_1D_SHADOW] = "GL_SAMPLER_1D_SHADOW";
        spGLSLType[GL_SAMPLER_2D_SHADOW] = "GL_SAMPLER_2D_SHADOW";
        spGLSLType[GL_SAMPLER_1D_ARRAY] = "GL_SAMPLER_1D_ARRAY";
        spGLSLType[GL_SAMPLER_2D_ARRAY] = "GL_SAMPLER_2D_ARRAY";
        spGLSLType[GL_SAMPLER_1D_ARRAY_SHADOW] = "GL_SAMPLER_1D_ARRAY_SHADOW";
        spGLSLType[GL_SAMPLER_2D_ARRAY_SHADOW] = "GL_SAMPLER_2D_ARRAY_SHADOW";
        spGLSLType[GL_SAMPLER_2D_MULTISAMPLE] = "GL_SAMPLER_2D_MULTISAMPLE";
        spGLSLType[GL_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
        spGLSLType[GL_SAMPLER_CUBE_SHADOW] = "GL_SAMPLER_CUBE_SHADOW";
        spGLSLType[GL_SAMPLER_BUFFER] = "GL_SAMPLER_BUFFER";
        spGLSLType[GL_SAMPLER_2D_RECT] = "GL_SAMPLER_2D_RECT";
        spGLSLType[GL_SAMPLER_2D_RECT_SHADOW] = "GL_SAMPLER_2D_RECT_SHADOW";
        spGLSLType[GL_INT_SAMPLER_1D] = "GL_INT_SAMPLER_1D";
        spGLSLType[GL_INT_SAMPLER_2D] = "GL_INT_SAMPLER_2D";
        spGLSLType[GL_INT_SAMPLER_3D] = "GL_INT_SAMPLER_3D";
        spGLSLType[GL_INT_SAMPLER_CUBE] = "GL_INT_SAMPLER_CUBE";
        spGLSLType[GL_INT_SAMPLER_1D_ARRAY] = "GL_INT_SAMPLER_1D_ARRAY";
        spGLSLType[GL_INT_SAMPLER_2D_ARRAY] = "GL_INT_SAMPLER_2D_ARRAY";
        spGLSLType[GL_INT_SAMPLER_2D_MULTISAMPLE] = "GL_INT_SAMPLER_2D_MULTISAMPLE";
        spGLSLType[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
        spGLSLType[GL_INT_SAMPLER_BUFFER] = "GL_INT_SAMPLER_BUFFER";
        spGLSLType[GL_INT_SAMPLER_2D_RECT] = "GL_INT_SAMPLER_2D_RECT";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_1D] = "GL_UNSIGNED_INT_SAMPLER_1D";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D] = "GL_UNSIGNED_INT_SAMPLER_2D";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_3D] = "GL_UNSIGNED_INT_SAMPLER_3D";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_CUBE] = "GL_UNSIGNED_INT_SAMPLER_CUBE";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE] = "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY] = "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_BUFFER] = "GL_UNSIGNED_INT_SAMPLER_BUFFER";
        spGLSLType[GL_UNSIGNED_INT_SAMPLER_2D_RECT] = "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
        spGLSLType[GL_BOOL] = "GL_BOOL";  
        spGLSLType[GL_INT] = "GL_INT";  
        spGLSLType[GL_BOOL_VEC2] = "GL_BOOL_VEC2";
        spGLSLType[GL_INT_VEC2] = "GL_INT_VEC2";  
        spGLSLType[GL_BOOL_VEC3] = "GL_BOOL_VEC3";
        spGLSLType[GL_INT_VEC3] = "GL_INT_VEC3";  
        spGLSLType[GL_BOOL_VEC4] = "GL_BOOL_VEC4";
        spGLSLType[GL_INT_VEC4] = "GL_INT_VEC4";  
        spGLSLType[GL_UNSIGNED_INT] = "GL_UNSIGNED_INT"; 
        spGLSLType[GL_UNSIGNED_INT_VEC2] = "GL_UNSIGNED_INT_VEC2";  
        spGLSLType[GL_UNSIGNED_INT_VEC3] = "GL_UNSIGNED_INT_VEC3";  
        spGLSLType[GL_UNSIGNED_INT_VEC4] = "GL_UNSIGNED_INT_VEC4";  
        spGLSLType[GL_FLOAT_MAT2] = "GL_FLOAT_MAT2";
        spGLSLType[GL_FLOAT_MAT3] = "GL_FLOAT_MAT3";
        spGLSLType[GL_FLOAT_MAT4] = "GL_FLOAT_MAT4";
        spGLSLType[GL_FLOAT_MAT2x3] = "GL_FLOAT_MAT2x3";
        spGLSLType[GL_FLOAT_MAT2x4] = "GL_FLOAT_MAT2x4";
        spGLSLType[GL_FLOAT_MAT3x2] = "GL_FLOAT_MAT3x2";
        spGLSLType[GL_FLOAT_MAT3x4] = "GL_FLOAT_MAT3x4";
        spGLSLType[GL_FLOAT_MAT4x2] = "GL_FLOAT_MAT4x2";
        spGLSLType[GL_FLOAT_MAT4x3] = "GL_FLOAT_MAT4x3";
        spGLSLType[GL_DOUBLE_MAT2] = "GL_DOUBLE_MAT2";
        spGLSLType[GL_DOUBLE_MAT3] = "GL_DOUBLE_MAT3";
        spGLSLType[GL_DOUBLE_MAT4] = "GL_DOUBLE_MAT4";
        spGLSLType[GL_DOUBLE_MAT2x3] = "GL_DOUBLE_MAT2x3";
        spGLSLType[GL_DOUBLE_MAT2x4] = "GL_DOUBLE_MAT2x4";
        spGLSLType[GL_DOUBLE_MAT3x2] = "GL_DOUBLE_MAT3x2";
        spGLSLType[GL_DOUBLE_MAT3x4] = "GL_DOUBLE_MAT3x4";
        spGLSLType[GL_DOUBLE_MAT4x2] = "GL_DOUBLE_MAT4x2";
        spGLSLType[GL_DOUBLE_MAT4x3] = "GL_DOUBLE_MAT4x3";
    }

    GLShaderProgram::GLShaderProgram(a_uint32 id) :
    m_id(id)
    {
        m_defaultParameter.type = PARAMETER_NOFOUND;
        SetupShader();
    }

    GLShaderProgram::~GLShaderProgram()
    {
        GLDriver::glDeleteProgram(m_id);
    }

    void GLShaderProgram::SetupShader()
    {
        Init();
        a_int32 n = 0;
        GLDriver::glGetProgramiv( m_id, GL_ACTIVE_UNIFORMS, &n );

        for( int i = 0 ; i < n ; i++ )
        {
            Parameter var;
            char name[30] = "\0";
            size_t length = 0;
            GLDriver::glGetActiveUniform( m_id, i, sizeof(name), (GLsizei*)&length, (GLint*)&var.size, &var.typeValue, name );
            var.loc = GLDriver::glGetUniformLocation( m_id, name );
            var.type = PARAMETER_UNIFORM;
            m_UniformMap[name] = var;
        }

        GLDriver::glGetProgramiv( m_id, GL_ACTIVE_ATTRIBUTES, &n );

        for( int i = 0 ; i < n ; i++ )
        {
            Parameter var;
            char name[30] = "\0";
            size_t length = 0;
            GLDriver::glGetActiveAttrib( m_id, i, sizeof(name), (GLsizei*)&length, (GLint*)&var.size, &var.typeValue, name );
            var.loc = GLDriver::glGetAttribLocation( m_id, name );
            var.type = PARAMETER_ATTRIBUT;
            m_AttributMap[name] = var;
        }

        /*GLRenderer::glGetProgramiv( m_id, GL_ACTIVE_UNIFORM_BLOCKS, &n );

        for( int i = 0 ; i < n ; i++ )
        {
            Parameter var;
            char name[30] = "\0";
            int32 length = 0;
            GLRenderer::glGetActiveUniformBlock( m_id, i,GL_UNIFORM_BLOCK_NAME_LENGTH,&length);
            var.loc = GLRenderer::glGetAttribLocation( m_id, name );
            var.type = PARAMETER_UNIFORM_BLOCK;
            m_AttributMap[name] = var;
        }*/

        Use(true);
        SetParameter("texture0",0);
        SetParameter("texture1",1);
        SetParameter("texture2",2);
        SetParameter("texture3",3);
        SetParameter("texture4",4);
        SetParameter("texture5",5);
        SetParameter("u_shadowMap",10);
        SetParameter("u_lightBuffer",11);
        Use(false);

        for(int i = 0; i < MAX_APIMATRIX; i++)
        {
            Parameter par = GetParameter(RGLEnum::GetName((TMatrixType)(MAT_MODEL+i)));
            m_APIMatrix[i] = par;
        }
    }

    const GLShaderProgram::Parameter& GLShaderProgram::GetParameter(const std::string& name) const
    {
        ParameterMap::const_iterator itr;
        if((itr = m_UniformMap.find(name)) != m_UniformMap.end())
        {
            return itr->second;
        }
        if((itr = m_AttributMap.find(name)) != m_AttributMap.end())
        {
            return itr->second;
        }
        return m_defaultParameter;
    }

    void GLShaderProgram::SetParameter(const std::string& name, float value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform1f(var.loc, value);
        else if(var.type == PARAMETER_ATTRIBUT)
            GLDriver::glVertexAttrib1f(var.loc, value);


    }

    void GLShaderProgram::SetParameter(const std::string& name, const vec2& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform2f(var.loc, value.x, value.y);
        else if(var.type == PARAMETER_ATTRIBUT)
            GLDriver::glVertexAttrib2f(var.loc, value.x, value.y);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const vec3& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform3f(var.loc, value.x, value.y, value.z);
        else if(var.type == PARAMETER_ATTRIBUT)
            GLDriver::glVertexAttrib3f(var.loc, value.x, value.y, value.z);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const vec4& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform4f(var.loc, value.x, value.y, value.z, value.w);
        else if(var.type == PARAMETER_ATTRIBUT)
            GLDriver::glVertexAttrib4f(var.loc, value.x, value.y, value.z, value.w);
    }

    void GLShaderProgram::SetParameter(const std::string& name, int value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform1i(var.loc, value);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const ivec2& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform2i(var.loc, value.x, value.y);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const ivec3& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform3i(var.loc, value.x, value.y, value.z);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const ivec4& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniform4i(var.loc, value.x, value.y, value.z, value.w);
    }

    void GLShaderProgram::SetParameter(const std::string& name, const mat2& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniformMatrix2fv(var.loc, 1, 0, value_ptr(value));
    }

    void GLShaderProgram::SetParameter(const std::string& name, const mat3& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniformMatrix3fv(var.loc, 1, 0, value_ptr(value));
    }

    void GLShaderProgram::SetParameter(const std::string& name, const mat4& value) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniformMatrix4fv(var.loc, 1, 0, value_ptr(value));
    }

    void GLShaderProgram::SetParameter(const std::string& name, float* value, a_uint32 count) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
        {
            if(var.size < count)
                return;

            for(a_uint32 i = 0; i < 1; i++)
                GLDriver::glUniform1fv(var.loc, count, (GLfloat*)value);
        }
    }

    void GLShaderProgram::SetParameter(const std::string& name, vec2* value, a_uint32 count) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
        {
            if(var.size < count)
                return;

            for(a_uint32 i = 0; i < 1; i++)
                GLDriver::glUniform2fv(var.loc, count, (GLfloat*)value);
        }
    }

    void GLShaderProgram::SetParameter(const std::string& name, vec3* value, a_uint32 count) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
        {
            if(var.size < count)
                return;

            for(a_uint32 i = 0; i < 1; i++)
                GLDriver::glUniform3fv(var.loc, count, (GLfloat*)value);
        }
    }

    void GLShaderProgram::SetParameter(const std::string& name, vec4* value, a_uint32 count) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
        {
            if(var.size < count)
                return;

            for(a_uint32 i = 0; i < 1; i++)
                GLDriver::glUniform4fv(var.loc, count, (GLfloat*)value);
        }
    }

    void GLShaderProgram::SetParameter(const std::string& name, mat4* value, a_uint32 count) const
    {
        const Parameter& var = GetParameter(name);
        if(var.type == PARAMETER_UNIFORM)
        {
            if(var.size < count)
                return;

            for(a_uint32 i = 0; i < 1; i++)
                GLDriver::glUniformMatrix4fv(var.loc, count, 0, (GLfloat*)value);
        }
    }

    void GLShaderProgram::SetParameter(TMatrixType type, const mat4& value) const
    {
        const Parameter& var = m_APIMatrix[type];
        if(var.type == PARAMETER_UNIFORM)
            GLDriver::glUniformMatrix4fv(var.loc, 1, 0, value_ptr(value));
    }

    void GLShaderProgram::SetParameter(const std::string& name, const a_uint32 bindpoint) const
    {
        a_int32 index = GLDriver::glGetUniformBlockIndex(m_id,name.c_str());
        if(index >= 0)
            GLDriver::glUniformBlockBinding(m_id, index, bindpoint);
    }

    void GLShaderProgram::Use(bool use) const
    {
         GLDriver::glUseProgram(use ? m_id : 0);
    }

    int GLShaderProgram::getUniformByteSize(int uniSize, int uniType, int uniArrayStride, int uniMatStride) 
    {
 
        int auxSize;
        if (uniArrayStride > 0)
            auxSize = uniArrayStride * uniSize;
                 
        else if (uniMatStride > 0) {
 
            switch(uniType) {
                case GL_FLOAT_MAT2:
                case GL_FLOAT_MAT2x3:
                case GL_FLOAT_MAT2x4:
                case GL_DOUBLE_MAT2:
                case GL_DOUBLE_MAT2x3:
                case GL_DOUBLE_MAT2x4:
                    auxSize = 2 * uniMatStride;
                    break;
                case GL_FLOAT_MAT3:
                case GL_FLOAT_MAT3x2:
                case GL_FLOAT_MAT3x4:
                case GL_DOUBLE_MAT3:
                case GL_DOUBLE_MAT3x2:
                case GL_DOUBLE_MAT3x4:
                    auxSize = 3 * uniMatStride;
                    break;
                case GL_FLOAT_MAT4:
                case GL_FLOAT_MAT4x2:
                case GL_FLOAT_MAT4x3:
                case GL_DOUBLE_MAT4:
                case GL_DOUBLE_MAT4x2:
                case GL_DOUBLE_MAT4x3:
                    auxSize = 4 * uniMatStride;
                    break;
            }
        }
        else
            auxSize = spGLSLTypeSize[uniType];
 
        return auxSize;
    }

    void GLShaderProgram::UniformShaderInfo()
    {
        Logger::Log(LOGDEBUG,"\n");
  
        int activeUnif, actualLen, index, uniType, 
            uniSize, uniMatStride, uniArrayStride, uniOffset;
        char name[256];
 
        // Get uniforms info (not in named blocks)
        Logger::Log(LOGDEBUG,"Uniforms Info for program: %d",m_id);
        GLDriver::glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &activeUnif);
 
        for (a_uint32 i = 0; i < (a_uint32)activeUnif; ++i) {
            GLDriver::glGetActiveUniformsiv(m_id, 1, &i, GL_UNIFORM_BLOCK_INDEX, &index);
            if (index == -1) {
                GLDriver::glGetActiveUniformName(m_id, i, 256, &actualLen, name);  
                GLDriver::glGetActiveUniformsiv(m_id, 1, &i, GL_UNIFORM_TYPE, &uniType);
                Logger::Log(LOGDEBUG,name);
                Logger::Log(LOGDEBUG,spGLSLType[uniType].c_str());
                Logger::Log(LOGDEBUG,"location: %d", i );
 
                GLDriver::glGetActiveUniformsiv(m_id, 1, &i, GL_UNIFORM_SIZE, &uniSize);
                GLDriver::glGetActiveUniformsiv(m_id, 1, &i, GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
 
                int auxSize;
                if (uniArrayStride > 0)
                    auxSize = uniArrayStride * uniSize;
                else
                    auxSize = spGLSLTypeSize[uniType];
 
                Logger::Log(LOGDEBUG,"    size: %d", auxSize);
                if (uniArrayStride > 0)
                    Logger::Log(LOGDEBUG,"    stride: %d", uniArrayStride);
            }
        }
        // Get named blocks info
        int count, dataSize, info;
        GLDriver::glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_BLOCKS, &count);
 
        for (int i = 0; i < count; ++i) {
            // Get buffers name
            GLDriver::glGetActiveUniformBlockName(m_id, i, 256, NULL, name);
            GLDriver::glGetActiveUniformBlockiv(m_id, i, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
            Logger::Log(LOGDEBUG,"%s\n  Size %d", name, dataSize);
 
            GLDriver::glGetActiveUniformBlockiv(m_id, i,  GL_UNIFORM_BLOCK_BINDING, &index);
            Logger::Log(LOGDEBUG,"  Block binding point: %d", index);
            GLDriver::glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, index, &info);
            Logger::Log(LOGDEBUG,"  Buffer bound to binding point: %d {", info);
 
 
            GLDriver::glGetActiveUniformBlockiv(m_id, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUnif);
 
            unsigned int *indices;
            indices = (unsigned int *)malloc(sizeof(unsigned int) * activeUnif);
            GLDriver::glGetActiveUniformBlockiv(m_id, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (int *)indices);
             
            for (int k = 0; k < activeUnif; ++k) {
         
                GLDriver::glGetActiveUniformName(m_id, indices[k], 256, &actualLen, name);
                GLDriver::glGetActiveUniformsiv(m_id, 1, &indices[k], GL_UNIFORM_TYPE, &uniType);
                Logger::Log(LOGDEBUG,"\t%s\n\t    %s", name, spGLSLType[uniType].c_str());
 
                GLDriver::glGetActiveUniformsiv(m_id, 1, &indices[k], GL_UNIFORM_OFFSET, &uniOffset);
                Logger::Log(LOGDEBUG,"\t    offset: %d", uniOffset);
 
                GLDriver::glGetActiveUniformsiv(m_id, 1, &indices[k], GL_UNIFORM_SIZE, &uniSize);
 
                GLDriver::glGetActiveUniformsiv(m_id, 1, &indices[k], GL_UNIFORM_ARRAY_STRIDE, &uniArrayStride);
 
                GLDriver::glGetActiveUniformsiv(m_id, 1, &indices[k], GL_UNIFORM_MATRIX_STRIDE, &uniMatStride);
 
                int auxSize;
                if (uniArrayStride > 0)
                    auxSize = uniArrayStride * uniSize;
                 
                else if (uniMatStride > 0) {
 
                    switch(uniType) {
                        case GL_FLOAT_MAT2:
                        case GL_FLOAT_MAT2x3:
                        case GL_FLOAT_MAT2x4:
                        case GL_DOUBLE_MAT2:
                        case GL_DOUBLE_MAT2x3:
                        case GL_DOUBLE_MAT2x4:
                            auxSize = 2 * uniMatStride;
                            break;
                        case GL_FLOAT_MAT3:
                        case GL_FLOAT_MAT3x2:
                        case GL_FLOAT_MAT3x4:
                        case GL_DOUBLE_MAT3:
                        case GL_DOUBLE_MAT3x2:
                        case GL_DOUBLE_MAT3x4:
                            auxSize = 3 * uniMatStride;
                            break;
                        case GL_FLOAT_MAT4:
                        case GL_FLOAT_MAT4x2:
                        case GL_FLOAT_MAT4x3:
                        case GL_DOUBLE_MAT4:
                        case GL_DOUBLE_MAT4x2:
                        case GL_DOUBLE_MAT4x3:
                            auxSize = 4 * uniMatStride;
                            break;
                    }
                }
                else
                    auxSize = spGLSLTypeSize[uniType];
 
                auxSize = getUniformByteSize(uniSize, uniType, uniArrayStride, uniMatStride);
                Logger::Log(LOGDEBUG,"\t    size: %d", auxSize);
                if (uniArrayStride > 0)
                    Logger::Log(LOGDEBUG,"\t    array stride: %d", uniArrayStride);
                if (uniMatStride > 0)
                    Logger::Log(LOGDEBUG,"\t    mat stride: %d", uniMatStride);
            }
            Logger::Log(LOGDEBUG,"    }");
        }
    }
}