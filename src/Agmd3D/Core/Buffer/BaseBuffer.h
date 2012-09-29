//==========================================================
// Agmd::Engine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
#ifndef BUFFERBASE_H
#define BUFFERBASE_H

#include <Config/Export.h>
#include <cstdlib>


namespace Agmd
{
    class AGMD_EXPORT BaseBuffer
    {
    public :

        virtual ~BaseBuffer();

    protected :

        BaseBuffer(unsigned long count);

        template <class T> friend class Buffer;

        virtual void* Lock(unsigned long offset, unsigned long size, unsigned long flags) = 0;

        virtual void Unlock() = 0;

        unsigned long m_Count;
    };

}


#endif // BUFFERBASE_H
