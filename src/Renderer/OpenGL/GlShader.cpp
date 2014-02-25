/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer\OpenGL\GlShader.h>
#include <Renderer\OpenGL\GlRenderer.h>

namespace Agmd
{
    GLShader::GLShader(a_uint32 shaderid, TShaderType type):
    BaseShader(type),
    m_Shader(shaderid)
    {}

    GLShader::~GLShader()
    {
        GLRenderer::glDeleteShader(m_Shader);
    }
}