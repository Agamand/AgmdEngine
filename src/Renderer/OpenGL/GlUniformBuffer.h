/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLUNIFORMBUFFER_H_
#define _GLUNIFORMBUFFER_H_

#include <Renderer/OpenGL/GlBuffer.h>
#include <Renderer/OpenGL/GlEnums.h>

namespace Agmd
{
    template <int bufferCount = 1> class GLUniformBuffer : public GLBuffer<GL_UNIFORM_BUFFER,bufferCount>
    {
    public :
        GLUniformBuffer(unsigned long count, unsigned int* buffer, unsigned int bindPoint);

        virtual void Bind(a_uint32 bindpoint);

        unsigned int getBindPoint() const;

    private:
        unsigned int m_bindPoint;
    };

    //#include <Renderer/OpenGL/GlRenderer.h>

    template <int bufferCount>
    GLUniformBuffer<bufferCount>::GLUniformBuffer(unsigned long count, unsigned int *buffer, unsigned int bindPoint) : 
    GLBuffer(count,buffer),
    m_bindPoint(bindPoint)
    {}

    template <int bufferCount>
    void GLUniformBuffer<bufferCount>::Bind(a_uint32 bindpoint)
    {
        GLDriver::glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer[m_currentBuffer]);
        GLDriver::glBindBufferBase(GL_UNIFORM_BUFFER,bindpoint,m_Buffer[m_currentBuffer]);
        GLDriver::glBindBuffer(GL_UNIFORM_BUFFER, 0);
        m_bindPoint = bindpoint;
    }

    template <int bufferCount>
    unsigned int GLUniformBuffer<bufferCount>::getBindPoint() const
    {
        return m_bindPoint;
    }
}



#endif /* _GLUNIFORMBUFFER_H_ */
