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
#include <Debug/Profiler.h>

namespace Agmd
{
    template <int Type, int bufferCount>
    class GLBuffer : public BaseBuffer
    {
    public :

        GLBuffer(unsigned long count, unsigned int* buffer);

        virtual ~GLBuffer();

        unsigned int GetBuffer() const;

    protected:

        void* Lock(unsigned long offset, unsigned long size, unsigned long flags);

        void* LockByte(unsigned long offset, unsigned long size, unsigned long flags);

        void Unlock();

        virtual void Bind(a_uint32 bindpoint);

        void WaitSync();

        void SwapBuffers();

        void FillByte(unsigned char* data, unsigned long offset, unsigned long size);
        void Flush();

        a_uint32 m_Buffer[bufferCount];
        a_uint32 m_currentBuffer;
        a_uint32 m_bufferCount;
        GLsync m_sync;
    };

    typedef GLBuffer<GL_ARRAY_BUFFER, 1> GLVertexBuffer;
    typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER, 1> GLIndexBuffer;

#include "GLBuffer.inl"
}


#endif /* _GLBUFFER_H_ */
