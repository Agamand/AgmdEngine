/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <CommonDefines.h>
//#include <cstring>

#define DEFAULT_CAPACITY 10

#include <Allocator/DefaultAllocator.h>

namespace AgmdUtilities
{
    template<typename T, template <typename> class A = DefaultAllocator>
    class Array
    {
    public:
        Array(uint32 capacity = DEFAULT_CAPACITY);
        ~Array();

        void push_back(T);
        void pop_back();

        void resize(uint32 size);
        uint32 size() const;
        uint32 capacity() const;


        T& operator[](uint32 i);
        const T& operator[](uint32 i) const;

    private:
        void resize_capacity(uint32 capacity);


        uint32          m_size;
        uint32          m_capacity;
        T*              m_storage;
        Allocator<T>*   m_allocator;
    };

    #include "Array.inl"

}
#endif /* _ARRAY_H_ */
