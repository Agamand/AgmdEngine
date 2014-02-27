/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef BUFFERBASE_H
#define BUFFERBASE_H

#include <Config/Export.h>
#include <CommonDefines.h>
#include <cstdlib>



namespace Agmd
{
    class AGMD3D_EXPORT BaseBuffer
    {
    public :

        virtual ~BaseBuffer();

    protected :

        BaseBuffer(unsigned long count);

        template <class T> friend class Buffer;

        virtual void* Lock(unsigned long offset, unsigned long size, unsigned long flags) = 0;
        
        virtual void* LockByte(unsigned long offset, unsigned long size, unsigned long flags) = 0;

        virtual void FillByte(unsigned char* data, unsigned long offset, unsigned long size) = 0;

        virtual void Unlock() = 0;

        virtual void Bind(a_uint32 bindpoint) = 0;

        virtual void WaitSync() = 0;

        virtual void SwapBuffers() = 0;

        virtual void Flush() = 0;

        unsigned long m_Count;
    };

}


#endif // BUFFERBASE_H
