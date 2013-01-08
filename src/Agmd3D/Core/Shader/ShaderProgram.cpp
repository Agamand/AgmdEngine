#include <Core\Shader\ShaderProgram.h>
#include <Core\ResourceManager.h>
#include <Core\MediaManager.h>
#include <Core\Renderer.h>

namespace Agmd
{
    void ShaderProgram::Unload()
    {
        m_ShaderProgram = NULL;
    }

    void ShaderProgram::LoadFromFile(const std::string& filename)
    {
        m_ShaderProgram = ResourceManager::Instance().Get<BaseShaderProgram>(filename);

        if (!m_ShaderProgram)
        {
            m_ShaderProgram = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>(filename);
            ResourceManager::Instance().Add(filename, m_ShaderProgram);
        }
    }

    void ShaderProgram::ReloadFromFile(const std::string& filename)
    {
        Unload();
        LoadFromFile(filename);
    }

    BaseShaderProgram* ShaderProgram::GetShaderProgram() const
    {
        return m_ShaderProgram;
    }

    void ShaderProgram::Create(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag)
    {
        m_ShaderProgram = Renderer::Get().CreateShaderProgram(vertex, eval, control, geom, frag);
    }
}