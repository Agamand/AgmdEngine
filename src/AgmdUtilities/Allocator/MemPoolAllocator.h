/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MEMPOOLALLOCATOR_H_
#define _MEMPOOLALLOCATOR_H_

#include <CommonDefines.h>
#include <queue>
#include <stack>
#include <Utilities/SharedPtr.h>

namespace AgmdUtilities
{
    template <typename T ,a_uint32 base_memory = 256>
    class MemPoolAllocator
    {
    public:
        MemPoolAllocator();
        ~MemPoolAllocator();

        T*& Allocate();

        void ReallocatePool(size_t count);

    private:
        struct memBlock
        {
            memBlock(T* mem, a_uint32 offset) :
            _offset(offset), _mem(mem)
            {}

            SharedPtr<T> _mem;
            a_uint32 _offset;
        };
        a_uint32 m_allocate;
        T* m_pool;
        a_uint32 m_current_offset;
        std::queue<memBlock> m_UnusedBlocks;
        std::stack<memBlock> m_UsedBlocks;
    };

    template <typename T, a_uint32 base_memory>
    inline MemPoolAllocator<T,base_memory>::MemPoolAllocator():
    m_allocate(base_memory),m_current_offset(0),m_pool(new T[m_allocate])
    {
        /*for(int i = 0; i < base_memory; i++)
            m_UnusedBlocks.push(new MemPoolAllocator::memBlock(m_pool+i,i));*/
    }

    template <typename T, a_uint32 base_memory>
    inline MemPoolAllocator<T,base_memory>::~MemPoolAllocator()
    {
        delete m_pool;
        /*uint32 s = m_UnusedBlocks.size()+1;
        while(--s !=0)
            m_UnusedBlocks.pop();*/
    }
    

    template <typename T, a_uint32 base_memory>
    inline T*& MemPoolAllocator<T,base_memory>::Allocate()
    {
        memBlock b = memBlock(((T*)m_pool)+(++m_current_offset),m_current_offset);
        m_UsedBlocks.push(b);
        int *& t = b._mem;
        int ** a = &t;
        return *a;//m_UnusedBlocks.pop();
    }

    template <typename T, a_uint32 base_memory>
    inline void MemPoolAllocator<T,base_memory>::ReallocatePool(size_t count)
    {
        if(m_count <= m_allocate)
            return;
        T* pool = new[count];
        /*
        for(int i = 0;  i < m_UnusedBlocks.size(), i++);
            m_UnusedBlocks[i]._mem = pool+m_UnusedBlocks[i]._offset;

        for(int = 0; i < m_UsedBlocks.size(); i++)
            m_UsedBlocks[i]._mem = pool+UsedBlocks[i]._offset;
        */
        /*
        for(int i = m_allocate; i < count; i++)
            m_UnusedBlocks.push(new MemPoolAllocator::memBlock(m_pool+i,i*sizeof(T)));
        */
    }
}


#endif /* _MEMPOOLALLOCATOR_H_ */
