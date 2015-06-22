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
#include <Allocator/StackAllocator.h>
#include <Utilities/Singleton.h>


#define BASE_POOL 1048576

namespace AgmdUtilities
{
    class StackPool : public Singleton<StackPool>
    {
        MAKE_SINGLETON(StackPool)
    public:
        StackPool(a_uint32 base_memory = BASE_POOL);
        ~StackPool();
        
    private:
        StackAllocator m_stack; 
    };
}


#endif /* _STACKALLOCATOR_H_ */
