/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MEMPOOLALLOCATOR_H_
#define _MEMPOOLALLOCATOR_H_
/*
#include <CommonDefines.h>
#include <vector>
#include <queue>
#include <Utilities/SharedPtr.h>

namespace AgmdUtilities
{
    template <typename T ,uint32 base_memory = 256>
    class MemPoolAllocator
    {
    public:
        MemPoolAllocator();
        ~MemPoolAllocator();

        T* Allocate();

        void ReallocatePool(size_t count);

    private:
        struct memBlock
        {
            memBlock(T* mem, uint32 offset) :
            _offset(offset), _mem(mem)
            {}

            SharedPtr<T> _mem;
            uint32 _offset;
        }
        uint32 m_allocate;
        T* m_pool;
        std::queue<memBlock*> m_UnusedBlocks;
        std::stack<memBlock*> m_UsedBlocks;
    };

    template <typename T, uint32 base_memory>
    inline MemPoolAllocator::MemPoolAllocator()
    {
        m_allocate = base_memory;
        m_pool = new T[base_memory];
        for(int i = 0; i < base_memory; i++)
            m_UnusedBlocks.push(new MemPoolAllocator::memBlock(m_pool+i,i));
    }

    template <typename T, uint32 base_memory>
    inline MemPoolAllocator::~MemPoolAllocator()
    {
        for(int i = 0;  i < m_UnusedBlock.size(), i++);
            delete m_UnusedBlock[i]._mem = pool+m_UnusedBlock[i]._offset;

        for(int = 0; i < m_UsedBlocks.size(); i++)
            delete m_UsedBlock[i]
    }
    

    template <typename T, uint32 size>
    inline T* MemPoolAllocator::Allocate()
    {
        return m_UnusedBlocks.pop();
    }

    template <typename T, uint32 size>
    inline MemPoolAllocator::ReallocatePool(size_t count)
    {
        if(m_count <= m_allocate)
            return;
        T* pool = new[count];
        for(int i = 0;  i < m_UnusedBlock.size(), i++);
            m_UnusedBlock[i]._mem = pool+m_UnusedBlock[i]._offset;

        for(int = 0; i < m_UsedBlocks.size(); i++)
            m_UsedBlock[i]._mem = pool+UsedBlock[i]._offset;

        for(int i = m_allocate; i < count; i++)
            m_UnusedBlocks.push(new MemPoolAllocator::memBlock(m_pool+i,i*sizeof(T)));
    }
}*/


#endif /* _MEMPOOLALLOCATOR_H_ */
