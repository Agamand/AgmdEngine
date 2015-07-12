/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _STACKALLOCATOR_H_
#define _STACKALLOCATOR_H_

#include <CommonDefines.h>
#include <queue>
#include <stack>
#include <Utilities/SharedPtr.h>
#include <Allocator/Allocator.h>
namespace AgmdUtilities
{
    template <typename T>
    class StackAllocator : public Allocator<T>
    {
    public:
        StackAllocator(a_uint32 base_memory = 256);
        ~StackAllocator();



        T* Allocate(size_t count = 1);
        void Release(T* value,int size_t = 1);

    private:
        void*       m_pool;
        void*       m_cursor;
        a_uint32    m_poolSize;
    };
    
    #include "StackAllocator.inl"
}


#endif /* _STACKALLOCATOR_H_ */
