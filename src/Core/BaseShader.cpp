#include <Core\BaseShader.h>


namespace Agmd
{
	BaseShader::BaseShader(TShaderType type) :
	m_Type(type)
	{}

	BaseShader::~BaseShader()
	{}

	TShaderType BaseShader::GetType() const
	{
		return m_Type;
	}
}