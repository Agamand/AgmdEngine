template <typename T>
inline StackAllocator<T>::MemPoolAllocator(a_uint32 base_memory/* = 256*/):
m_pool(new T[m_allocate]),m_cursor(m_pool),m_poolSize(base_memory)
{}

template <typename T>
inline StackAllocator<T>::~MemPoolAllocator()
{
    delete m_pool;
}


template <typename T>
inline T*& StackAllocator<T>::Allocate(size_t count/* = 1*/)
{
    void* value = m_cursor;
    m_cursor += sizeof(T)*count;
    return value;
}

template <typename T>
inline void StackAllocator<T>::Release(T* value ,size_t count/* = 1*/)
{
    void* value = m_cursor;
    m_cursor += sizeof(T)*count;
    return value;
}