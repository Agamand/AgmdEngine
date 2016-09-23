/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXBUFFER_H_
#define _DXBUFFER_H_

#include <Core/Buffer/BaseBuffer.h>
#include <Renderer/DirectX/DxEnums.h>
#include <Debug/Profiler.h>
#include <dxgi.h>
#include <d3d11.h>

namespace Agmd
{
    template <int bufferCount>
    class DXBuffer : public BaseBuffer
    {
    public :

        DXBuffer(unsigned long count, ID3D11Buffer** buffer);

        virtual ~DXBuffer();

        ID3D11Buffer* GetBuffer() const;

    protected:

        void* Lock(unsigned long offset, unsigned long size, unsigned long flags);

        void* LockByte(unsigned long offset, unsigned long size, unsigned long flags);

        void Unlock();

        virtual void Bind(a_uint32 bindpoint);

        void WaitSync();

        void SwapBuffers();

        void FillByte(unsigned char* data, unsigned long offset, unsigned long size);
        void Flush();

        ID3D11Buffer* m_Buffer[bufferCount];
        a_uint32 m_currentBuffer;
        a_uint32 m_bufferCount;
    };

    typedef DXBuffer<1> DXVertexBuffer;
    typedef DXBuffer<1> DXIndexBuffer;
    typedef DXBuffer<1> DXConstantBuffer;

#include "DxBuffer.inl"
}


#endif /* _DXBUFFER_H_ */
