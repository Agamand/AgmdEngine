#ifndef GLBUFFER_H
#define GLBUFFER_H

#include <Core/Buffer/BaseBuffer.h>
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

    protected:

        void* Lock(unsigned long offset, unsigned long size, unsigned long flags);

        void Unlock();

        virtual void Bind(uint32 bindpoint);

        unsigned int m_Buffer;
    };

    typedef GLBuffer<GL_ARRAY_BUFFER>         GLVertexBuffer;
    typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> GLIndexBuffer;
    /*typedef GLBuffer<GL_UNIFORM_BUFFER>       GLUniformBuffer;
    typedef GLBuffer<GL_TEXTURE_BUFFER>          GLTextureBuffer;*/

    #include "GLBuffer.inl"

}


#endif // GLBUFFER_H
