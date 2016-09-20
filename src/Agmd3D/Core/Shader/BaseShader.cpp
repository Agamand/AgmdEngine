/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\Shader\BaseShader.h>


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