/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef BUFFER_H
#define BUFFER_H

#include <Core/Buffer/BaseBuffer.h>
#include <Utilities/SmartPtr.h>
#include <Debug/Exception.h>

#include <algorithm>
#include <assert.h>

using namespace AgmdUtilities;

namespace Agmd
{
    template <class T>
    class Buffer
    {
    public :

        Buffer(BaseBuffer* buffer = NULL);

        T* Lock(unsigned long offset = 0, unsigned long size = 0, unsigned long flags = 0);

        void Unlock();

        void Fill(const T* data, std::size_t count);

        void Release();

        const BaseBuffer* GetBuffer() const;

        unsigned long GetCount() const;

        void Bind(uint32 bindpoint);

    private :

        SmartPtr<BaseBuffer> m_Buffer;
    };
    #include "Buffer.inl"
}

#endif // BUFFER_H
