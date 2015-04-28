/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXBuffer_H_
#define _DXBuffer_H_

#include <Core/Buffer/BaseBuffer.h>
#include <Renderer/DirectX/DxEnums.h>
#include <gl/glext.h>
#include <Debug/Profiler.h>

namespace Agmd
{
    template <class Type, int bufferCount>
    class DXBuffer : public BaseBuffer
    {
    public :

        DXBuffer(unsigned long count, unsigned int *buffer);

        virtual ~DXBuffer();

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

        Type m_Buffer[bufferCount];
        Type m_currentBuffer;
        a_uint32 m_bufferCount;
        GLsync m_sync;
    };

    typedef DXBuffer<ID3D11Buffer*,1>         DXVertexBuffer;
    typedef DXBuffer<GL_ELEMENT_ARRAY_BUFFER,1> DXIndexBuffer;

    #include "DxBuffer.inl"

}


#endif /* _DXBuffer_H_ */
