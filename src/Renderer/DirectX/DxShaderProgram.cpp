/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DxShaderProgram.h>
#include <Renderer/DirectX/DxBuffer.h>
//#include <Renderer/DirectX/DxUniformBuffer.h>
#include <Renderer/DirectX/DxDriver.h>
#include <Debug/Logger.h>

namespace Agmd
{

    std::map<int, std::string> DXShaderProgram::spGLSLType;
    std::map<int, int> DXShaderProgram::spGLSLTypeSize;
    bool DXShaderProgram::s_init = false;

    void DXShaderProgram::Init()
    {
        if(s_init)
            return;
    }

    DXShaderProgram::DXShaderProgram()
    {
        std::memset(m_shader,sizeof(BaseShader*)*TSHADERTYPE_MAX,0);
        m_defaultParameter.type = PARAMETER_NOFOUND;
        SetupShader();
    }

    DXShaderProgram::~DXShaderProgram()
    {}

    void DXShaderProgram::SetupShader()
    {}

    const DXShaderProgram::Parameter& DXShaderProgram::GetParameter(const std::string& name) const
    {

        return m_defaultParameter;
    }

    void DXShaderProgram::SetParameter(const std::string& name, float value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const vec2& value) const
    {
    }

    void DXShaderProgram::SetParameter(const std::string& name, const vec3& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const vec4& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, int value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const ivec2& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const ivec3& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const ivec4& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const mat2& value) const
    {


    }

    void DXShaderProgram::SetParameter(const std::string& name, const mat3& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const mat4& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, float* value, a_uint32 count) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, vec2* value, a_uint32 count) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, vec3* value, a_uint32 count) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, vec4* value, a_uint32 count) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, mat4* value, a_uint32 count) const
    {

    }

    void DXShaderProgram::SetParameter(TMatrixType type, const mat4& value) const
    {

    }

    void DXShaderProgram::SetParameter(const std::string& name, const a_uint32 bindpoint) const
    {

    }

    void DXShaderProgram::Use(bool use) const
    {

    }

    int DXShaderProgram::getUniformByteSize(int uniSize, int uniType, int uniArrayStride, int uniMatStride) 
    {
        return 0;
    }

    void DXShaderProgram::UniformShaderInfo()
    {
      
    }
}