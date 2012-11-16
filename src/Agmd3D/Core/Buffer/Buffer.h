#ifndef BUFFER_H
#define BUFFER_H

//==========================================================
// En-têtes
//==========================================================
#include <Core/Buffer/BaseBuffer.h>
#include <Debug/Exception.h>
#include <Utilities/SmartPtr.h>
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

    private :

        SmartPtr<BaseBuffer> m_Buffer;
    };
    #include "Buffer.inl"
}

#endif // BUFFER_H
