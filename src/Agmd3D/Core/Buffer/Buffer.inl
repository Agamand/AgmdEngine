/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T>
inline Buffer<T>::Buffer(BaseBuffer* buffer) : m_Buffer(buffer)
{}

template <class T>
inline T* Buffer<T>::Lock(unsigned long offset, unsigned long size, unsigned long flags)
{
    return reinterpret_cast<T*>(m_Buffer->Lock(offset * sizeof(T), size * sizeof(T), flags));
}


template <class T>
template <class D>
inline D* Buffer<T>::LockBits(unsigned long offset, unsigned long size, unsigned long flags)
{
    return reinterpret_cast<D*>(m_Buffer->LockBits(offset, size, flags));
}


template <class T>
template <class D>
inline void Buffer<T>::FillByte(D* data, unsigned long offset, unsigned long sizes)
{
    m_Buffer->FillByte(reinterpret_cast<unsigned char*>(data), offset, sizes);
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

template <class T>
inline void Buffer<T>::Bind(uint32 bindpoint)
{
    m_Buffer->Bind(bindpoint);
}

template <class T>
inline void Buffer<T>::WaitSync()
{
    m_Buffer->WaitSync();
}

template <class T>
inline void Buffer<T>::SwapBuffers()
{
    m_Buffer->SwapBuffers();
}

template <class T>
inline void Buffer<T>::Flush()
{
    m_Buffer->Flush();
}

