#ifndef GLSHADER_H
#define GLSHADER_H

#include <AgmdDefines.h>
#include <Core/Shader/BaseShader.h>
#include <string>

namespace Agmd
{
	class GLShader : public BaseShader
	{
	public:
		GLShader(uint32 shaderEntry, TShaderType type);
		virtual ~GLShader();

		uint32 GetId() {return m_Shader;}

	private:
		uint32 m_Shader;
	};
}

#endif