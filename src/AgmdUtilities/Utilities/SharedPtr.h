/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SHAREDPTR_H_
#define _SHAREDPTR_H_

#include <cstdlib>
#include <Debug/Exception.h>
#include <Debug/New.h>
#include <Utilities/SmartPtr.h>

namespace AgmdUtilities
{
    template <class T>
    class SharedPtr
    {
    public:
        SharedPtr();

        SharedPtr(const SharedPtr& sptrcpy);

        SharedPtr(T* ptr);

        ~SharedPtr();

        T& operator * () const;
        T* operator ->() const;

        const SharedPtr& operator =(const SharedPtr& sptr);

        const SharedPtr& operator =(T* ptr);



        operator T*() const;

    private :
        SmartPtr<T*> m_Data;
    };

    #include "SharedPtr.inl"
    #include <Debug/NewOff.h>
}

#endif /* _SHAREDPTR_H_ */
