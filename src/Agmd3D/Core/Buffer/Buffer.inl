#pragma warning(disable:4996)

template <class T>
inline Buffer<T>::Buffer(BaseBuffer* buffer) : m_Buffer(buffer)
{}

template <class T>
inline T* Buffer<T>::Lock(unsigned long offset, unsigned long size, unsigned long flags)
{
    return reinterpret_cast<T*>(m_Buffer->Lock(offset * sizeof(T), size * sizeof(T), flags));
}

template <class T>
inline void Buffer<T>::Unlock()
{
    m_Buffer->Unlock();
}

template <class T>
inline void Buffer<T>::Fill(const T* data, std::size_t count)
{
    assert(data != NULL);

    T* _data = Lock();
    std::copy(data, data + count, _data);
    Unlock();
}

template <class T>
inline void Buffer<T>::Release()
{
    m_Buffer = NULL;
}

template <class T>
inline const BaseBuffer* Buffer<T>::GetBuffer() const
{
    return m_Buffer;
}

template <class T>
inline unsigned long Buffer<T>::GetCount() const
{
    return m_Buffer->m_Count;
}
