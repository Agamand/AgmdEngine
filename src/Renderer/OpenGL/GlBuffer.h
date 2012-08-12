#ifndef GLBUFFER_H
#define GLBUFFER_H

#include <Core/BaseBuffer.h>
#include <Renderer\OpenGL\GlEnums.h>
#include <gl\glext.h>

namespace Agmd
{
    template <int Type>
    class GLBuffer : public BaseBuffer
    {
    public :

        GLBuffer(unsigned long count, unsigned int buffer);

        virtual ~GLBuffer();

        unsigned int GetBuffer() const;

    private :

        void* Lock(unsigned long offset, unsigned long size, unsigned long flags);

        void Unlock();

        unsigned int m_Buffer;
    };

    typedef GLBuffer<GL_ARRAY_BUFFER>         GLVertexBuffer;
    typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> GLIndexBuffer;

    #include "GLBuffer.inl"

}


#endif // GLBUFFER_H
