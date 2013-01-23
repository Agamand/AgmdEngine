/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FASTLIST_H_
#define _FASTLIST_H_

#include <AgmdDefines.h>
#include <cstring>
#include <cstdlib>

#define DEFAULT_CAPACITY 10

namespace AgmdUtilities
{
    template<class T> class FastArray
    {
    public:
        FastArray(uint32 capacity = DEFAULT_CAPACITY);
        ~FastArray();

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
    };

    #include "FastArray.inl"

}
#endif /* _FASTARRAY_H_ */
