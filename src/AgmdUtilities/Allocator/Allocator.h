/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

namespace AgmdUtilities
{
    template <typename T>
    class Allocator
    {
    public:
        Allocator()
        {
        }

        virtual ~Allocator()
        {
        }

        virtual T* Allocate(size_t count = 1) = 0;

        virtual void UnAllocate(T* ptr, size_t count = 1) = 0;
    };
}


#endif /* _ALLOCATOR_H_ */
