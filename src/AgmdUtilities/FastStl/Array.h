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
        Array(a_uint32 capacity = DEFAULT_CAPACITY);
        ~Array();

        void push_back(T);
        void pop_back();

        void resize(a_uint32 size);
        a_uint32 size() const;
        a_uint32 capacity() const;


        T& operator[](a_uint32 i);
        const T& operator[](a_uint32 i) const;

    private:
        void resize_capacity(a_uint32 capacity);


        a_uint32          m_size;
        a_uint32          m_capacity;
        T*              m_storage;
        Allocator<T>*   m_allocator;
    };

    #include "Array.inl"

}
#endif /* _ARRAY_H_ */
