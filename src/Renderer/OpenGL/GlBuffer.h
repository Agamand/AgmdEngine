/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLBUFFER_H_
#define _GLBUFFER_H_

#include <Core/Buffer/BaseBuffer.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <gl/glext.h>

namespace Agmd
{
    template <int Type>
    class GLBuffer : public BaseBuffer
    {
    public :

        GLBuffer(unsigned long count, unsigned int buffer);

        virtual ~GLBuffer();

        unsigned int GetBuffer() const;

    protected:

        void* Lock(unsigned long offset, unsigned long size, unsigned long flags);

        void Unlock();

        virtual void Bind(uint32 bindpoint);

        unsigned int m_Buffer;
    };

    typedef GLBuffer<GL_ARRAY_BUFFER>         GLVertexBuffer;
    typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> GLIndexBuffer;

    #include "GLBuffer.inl"

}


#endif /* _GLBUFFER_H_ */
