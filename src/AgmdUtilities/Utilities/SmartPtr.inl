/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T, template <class> class Ownership>
T*& GetPtr(SmartPtr<T, Ownership>& sptr)
{
    return sptr.m_Data;
}

template <class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr() :
m_Data(NULL)
{}

template <class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr(const SmartPtr<T, Ownership>& sptrcpy) :
Ownership<T>(sptrcpy),
m_Data(Clone(sptrcpy.m_Data))
{}

template <class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::SmartPtr(T* ptr) :
m_Data(ptr)
{}

template <class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::~SmartPtr()
{
    Release(m_Data);
}

template <class T, template <class> class Ownership>
inline void SmartPtr<T, Ownership>::Swap(SmartPtr<T, Ownership>& sptr)
{
    Ownership<T>::Swap(sptr);
    std::swap(m_Data, sptr.m_Data);
}

template <class T, template <class> class Ownership>
inline T& SmartPtr<T, Ownership>::operator *() const
{
    Assert(m_Data != NULL);

    return *m_Data;
}

template <class T, template <class> class Ownership>
inline T* SmartPtr<T, Ownership>::operator ->() const
{
    Assert(m_Data != NULL);

    return m_Data;
}

template <class T, template <class> class Ownership>
inline const SmartPtr<T, Ownership>& SmartPtr<T, Ownership>::operator =(const SmartPtr<T, Ownership>& sptr)
{
    SmartPtr<T, Ownership>(sptr).Swap(*this);

    return *this;
}

template <class T, template <class> class Ownership>
inline const SmartPtr<T, Ownership>& SmartPtr<T, Ownership>::operator =(T* ptr)
{
    if (m_Data != ptr)
    {
        SmartPtr<T, Ownership>(ptr).Swap(*this);
    }

    return *this;
}

template <class T, template <class> class Ownership>
inline SmartPtr<T, Ownership>::operator T*() const
{
    return m_Data;
}
