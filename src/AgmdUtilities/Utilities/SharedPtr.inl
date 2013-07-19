


template <typename T>
inline SharedPtr<T>::SharedPtr() :
m_Data(new T*())
{}

template <typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T>& sptrcpy) :
m_Data(sptrcpy.m_Data)
{}

template <typename T>
inline SharedPtr<T>::SharedPtr(T* ptr) :
m_Data(new T*())
{
    *m_Data = ptr;
}

template <typename T>
inline SharedPtr<T>::~SharedPtr()
{}

template <typename T>
inline T& SharedPtr<T>::operator * () const
{
    return **m_Data;
}

template <typename T>
inline T* SharedPtr<T>::operator ->() const
{
    return *m_Data;
}

template <typename T>
inline const SharedPtr<T>& SharedPtr<T>::operator =(const SharedPtr<T>& sptr)
{
    m_Data = sptr.m_Data;
    return *this;
}

template <typename T>
inline const SharedPtr<T>& SharedPtr<T>::operator =(T* ptr)
{
    *m_Data = ptr;
    return *this;
}