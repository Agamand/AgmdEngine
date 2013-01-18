/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer\OpenGL\GlRenderBuffer.h>
#include <Renderer\OpenGL\GlRenderer.h>

namespace Agmd
{

    GLRenderBuffer::GLRenderBuffer(uint32 buff_id, const ivec2& size) :
    RenderBuffer(size),
    m_Id(buff_id)
    {}


    GLRenderBuffer::~GLRenderBuffer()
    {
        GLRenderer::glDeleteRenderbuffers(1,&m_Id);
    }

    uint32 GLRenderBuffer::GetID()
    {
        return m_Id;
    }

}