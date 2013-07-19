/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <typename T, template <typename> class A>
inline Array<T, A>::Array(uint32 capacity) :
m_capacity(capacity), m_size(0), m_storage(new T[m_capacity]), m_allocator(new A<T>())
{}


template <typename T, template <typename> class A>
inline Array<T, A>::~Array()
{
    m_allocator->UnAllocate(m_storage,true);
    //delete[] m_storage;
}

template <typename T, template <typename> class A>
inline void Array<T, A>::push_back(T element)
{
    if(m_size >=  m_capacity)
        resize_capacity(m_size+DEFAULT_CAPACITY);
    m_storage[m_size] = element;
    m_size++;
}

template <typename T, template <typename> class A> inline void Array<T, A>::pop_back()
{
    m_size && m_size--;
}

template <typename T, template <typename> class A> inline void Array<T, A>::resize(uint32 size)
{
    if(size > m_capacity)
        resize_capacity(size+DEFAULT_CAPACITY);

    m_size = size;
}

template <typename T, template <typename> class A> inline void Array<T, A>::resize_capacity(uint32 capacity)
{
    T* capacitor = m_allocator->Allocate(capacity);
    std::memcpy(capacitor,m_storage,m_size*sizeof(T));
    m_capacity = capacity;
    m_allocator->UnAllocate(m_storage,true);
    m_storage = capacitor;
}

template <typename T, template <typename> class A> inline uint32 Array<T, A>::size() const
{
    return m_size;
}

template <typename T, template <typename> class A> inline uint32 Array<T, A>::capacity() const
{
    return m_capacity;
}


template <typename T, template <typename> class A> inline T& Array<T, A>::operator[](uint32 i)
{
    return *(m_storage+i);
}
template <typename T, template <typename> class A> inline const T& Array<T, A>::operator[](uint32 i) const
{
    return *(m_storage+i);
}
/*
template <typename T, template <typename> class A> inline const T Array::operator[] const
{
    return m_storage+i;
}*/
