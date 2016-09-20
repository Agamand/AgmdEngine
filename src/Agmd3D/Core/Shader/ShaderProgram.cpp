/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Shader/ShaderProgram.h>
#include <Core/ResourceManager.h>
#include <Core/MediaManager.h>
#include <Core/Driver.h>

#include <Core/AgmdApplication.h>

namespace Agmd
{
    void ShaderProgram::Unload()
    {
        m_ShaderProgram = NULL;
    }

	inline bool ends_with(std::string const &val, std::string const & ending)
	{
		if (ending.size() > val.size()) return false;
		return std::equal(ending.rbegin(), ending.rend(), val.rbegin());
	}
	static const char* subPath[] = {
		"Shader/GL/",
		"Shader/DX/"
	};

	static const char* fileExt[] = {
		".glsl",
		".hlsl"
	};
#define FIRST_TERM "Shader/"
#define FIRST_TERM_SIZE 7
#define SECOND_TERM ".shader"
#define SECOND_TERM_SIZE 7

	inline void fixPath(std::string& outPath,ADriverType type)
	{
		outPath.replace(outPath.find(FIRST_TERM),FIRST_TERM_SIZE,subPath[type]);
		outPath.replace(outPath.find(SECOND_TERM),SECOND_TERM_SIZE,fileExt[type]);
	}


    void ShaderProgram::LoadFromFile(const std::string& filename)
    {
		std::string newFilename;
		if(ends_with(filename,".shader"))
		{
			ADriverType dType = AgmdApplication::getApplication()->GetDriverType();
			newFilename= filename; // inject DX or GL and replace .shader by .glsl/.hlsl
			fixPath(newFilename,dType);
		}else newFilename = filename;

        m_ShaderProgram = ResourceManager::Instance().Get<BaseShaderProgram>(newFilename);

        if (!m_ShaderProgram)
        {
            m_ShaderProgram = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>(newFilename);
            if(NULL != m_ShaderProgram)
                ResourceManager::Instance().Add(newFilename, m_ShaderProgram);
        }
    }

    void ShaderProgram::ReloadFromFile(const std::string& filename)
    {
        Unload();
        LoadFromFile(filename);
    }

    const BaseShaderProgram* ShaderProgram::GetShaderProgram() const
    {
        return m_ShaderProgram;
    }

    void ShaderProgram::Create(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag)
    {
        m_ShaderProgram = Driver::Get().CreateShaderProgram(vertex, eval, control, geom, frag);
    }
}