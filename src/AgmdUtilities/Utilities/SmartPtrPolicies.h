#ifndef SMARTPTRPOLICIES_H
#define SMARTPTRPOLICIES_H

#include <Debug/New.h>


namespace AgmdUtilities
{
    template <class T>
    class RefCount
    {
    public :

        RefCount() : m_Counter(new int(1))
        {
        }

        T* Clone(T* ptr)
        {
            ++*m_Counter;
            return ptr;
        }

        void Release(T* ptr)
        {
            if (--*m_Counter == 0)
            {
                delete m_Counter;
                delete ptr;
            }
        }

        void Swap(RefCount& refCount)
        {
            std::swap(refCount.m_Counter, m_Counter);
        }

    private :

        int* m_Counter;
    };

    template <class T>
    class ResourceCOM
    {
    public :

        static T* Clone(T* ptr)
        {
            if (ptr)
                ptr->AddRef();
            return ptr;
        }

        static void Release(T* ptr)
        {
            if (ptr)
                ptr->Release();
        }
        static void Swap(ResourceCOM&)
        {
        }
    };

    #include <Debug/NewOff.h>

};

#endif // SMARTPTRPOLICIES_H
