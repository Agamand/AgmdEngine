#include <Renderer\OpenGL\GlShader.h>
#include <Renderer\OpenGL\GlRenderer.h>

namespace Agmd
{
    GLShader::GLShader(uint32 shader, TShaderType type):
    BaseShader(type),
    m_Shader(shader)
    {}

    GLShader::~GLShader()
    {
        GLRenderer::glDeleteShader(m_Shader);
    }
}