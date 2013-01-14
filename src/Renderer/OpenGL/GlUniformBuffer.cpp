/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/OpenGL/GlUniformBuffer.h>
#include <Renderer/OpenGL/GlRenderer.h>

namespace Agmd
{
    GLUniformBuffer::GLUniformBuffer(unsigned long count, unsigned int buffer, unsigned int bindPoint) : 
    GLBuffer(count,buffer),
    m_bindPoint(bindPoint)
    {}

    void GLUniformBuffer::Bind(uint32 bindpoint)
    {
        GLRenderer::glBindBufferBase(GL_UNIFORM_BUFFER,bindpoint,m_Buffer);
        m_bindPoint = bindpoint;
    }

    unsigned int GLUniformBuffer::getBindPoint() const
    {
        return m_bindPoint;
    }
}