/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T> inline FastArray<T>::FastArray(uint32 capacity) :
m_capacity(capacity), m_size(0), m_storage(new T[m_capacity])
{
}

template <class T> inline FastArray<T>::~FastArray()
{
    delete[] m_storage;
}

template <class T> inline void FastArray<T>::push_back(T element)
{
    if(m_size >  m_capacity)
        resize_capacity(size+DEFAULT_CAPACITY);
    m_storage[m_size];
    m_size++;
}

template <class T> inline void FastArray<T>::pop_back()
{
    m_size--;
}

template <class T> inline void FastArray<T>::resize(uint32 size)
{
    if(size > m_capacity)
        resize_capacity(size+DEFAULT_CAPACITY);

    m_size = size;
}

template <class T> inline void FastArray<T>::resize_capacity(uint32 capacity)
{
    T* capacitor = new T[capacity];
    std::memcpy(capacitor,m_storage,m_size);
    m_capacity = capacity;
    //std::free(m_storage); // not use delete[] (call dtor)
    delete[] m_storage;
    m_storage = capacitor;
}

template <class T> inline uint32 FastArray<T>::size() const
{
    return m_size;
}

template <class T> inline uint32 FastArray<T>::capacity() const
{
    return m_capacity;
}


template <class T> inline T& FastArray<T>::operator[](uint32 i)
{
    return *(m_storage+i);
}
template <class T> inline const T& FastArray<T>::operator[](uint32 i) const
{
    return *(m_storage+i);
}
/*
template <class T> inline const T operator[] const
{
    return m_storage+i;
}*/