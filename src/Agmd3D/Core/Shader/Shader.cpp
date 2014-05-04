/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\Shader\Shader.h>
#include <Core\ResourceManager.h>
#include <Core\MediaManager.h>
#include <Core\Driver.h>

namespace Agmd
{
    void Shader::LoadFromFile(const std::string& filename)
    {
        m_Shader = ResourceManager::Instance().Get<BaseShader>(filename);

        if (!m_Shader)
        {
            m_Shader = MediaManager::Instance().LoadMediaFromFile<BaseShader>(filename);
            ResourceManager::Instance().Add(filename, m_Shader);
        }
    }

    void Shader::CreateFromSrc(const std::string& src, TShaderType type)
    {
        m_Shader = Driver::Get().CreateShader(src,type);
    }

    void Shader::Unload()
    {
        m_Shader = NULL;
    }

    const BaseShader* Shader::GetShader() const
    {
        return m_Shader;
    }
}