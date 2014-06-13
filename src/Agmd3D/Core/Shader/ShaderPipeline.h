/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SHADERPIPELINE_H_
#define _SHADERPIPELINE_H_

#include <Config/Fwd.h>
#include <Core/Enums.h>

#include <Core/Shader/ShaderProgram.h>

#include <string>
#include <map>
#include <fstream>

namespace Agmd
{
    class AGMD3D_EXPORT ShaderPipeline
    {
    public:

        ShaderPipeline();
		ShaderPipeline(const ShaderPipeline& copy);
		~ShaderPipeline();

        bool Enable(TRenderPass pass) const;
        void Disable() const;

        static ShaderPipeline* GetDefaultPipeline();
		void setShader(const ShaderProgram& program, TRenderPass pass)
		{
				m_pipeline[pass] = program;
		}
		template <typename T> void setParameter(std::string paramName, T value)
		{
			for(int i = 0; i < MAX_RENDERPASS; i++)
				if(m_pipeline[i].GetShaderProgram())
					m_pipeline[i].SetParameter(paramName,value);
		}
    private:
        ShaderProgram m_pipeline[MAX_RENDERPASS];
        static ShaderPipeline* s_defaultPipeline;
        static void LoadDefaultFunction();
        static std::map<std::string,std::string> m_defaultFunction;

    };
    inline std::string LoadFromFile(std::string path)
    {
        std::ifstream stream(path);
        return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    }
}

#endif /* _SHADERPIPELINE_H_ */