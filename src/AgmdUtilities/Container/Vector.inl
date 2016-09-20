/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/


template <typename T, template <typename> class A>
inline Vector<T, A>::Vector() :
    m_capacity(DEFAULT_CAPACITY), m_size(0), m_storage(NULL), m_allocator(new A<T>())
{
    m_storage = m_allocator->Allocate(m_capacity);
}

template <typename T, template <typename> class A>
inline Vector<T, A>::Vector(a_uint32 size) :
    m_capacity(size), m_size(size), m_storage(NULL), m_allocator(new A<T>())
{
    m_storage = m_allocator->Allocate(m_capacity);
}

template <typename T, template <typename> class A>
inline Vector<T, A>::Vector(a_uint32 size, T val) :
    m_capacity(capacity), m_size(size), m_storage(new T[m_capacity]), m_allocator(new A<T>())
{
    m_storage = m_allocator->Allocate(m_capacity);
    for (a_uint32 i = 0; i < m_size; i++)
        m_storage[i] = val;
}

template <typename T, template <typename> class A>
inline Vector<T, A>::Vector(Vector& cpy) :
    m_capacity(cpy.m_size), m_size(cpy.m_size), m_storage(new T[cpy.m_size]), m_allocator(new A<T>())
{
    m_storage = m_allocator->Allocate(m_capacity);
    for (a_uint32 i = 0; i < m_size; i++)
        m_storage[i] = cpy.m_storage[i];
}


template <typename T, template <typename> class A>
inline Vector<T, A>::~Vector()
{
    m_allocator->UnAllocate(m_storage, true);
    delete m_allocator;
    //delete[] m_storage;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::push_back(T element)
{
    if (m_size >= m_capacity)
        resize_capacity(m_size + DEFAULT_CAPACITY);
    m_storage[m_size] = element;
    m_size++;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::pop_back()
{
    m_storage[m_size] = T::~T();
    m_size &&m_size
    --;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::resize(a_uint32 size)
{
    if (size > m_capacity)
        resize_capacity(size + DEFAULT_CAPACITY);
    if (size > m_size)
        for (a_uint32 i = m_size; i < size; i++)
            m_storage[i] = T();
    m_size = size;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::resize(a_uint32 size, const T val)
{
    if (size > m_capacity)
        resize_capacity(size + DEFAULT_CAPACITY);
    if (size > m_size)
        for (a_uint32 i = m_size; i < size; i++)
            m_storage[i] = val;
    m_size = size;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::resize_capacity(a_uint32 capacity)
{
    T* capacitor = m_allocator->Allocate(capacity);
    std::memcpy(capacitor, m_storage, m_size * sizeof(T));
    m_capacity = capacity;
    m_allocator->UnAllocate(m_storage, true);
    m_storage = capacitor;
}

template <typename T, template <typename> class A>
inline a_uint32 Vector<T, A>::size() const
{
    return m_size;
}

template <typename T, template <typename> class A>
inline void Vector<T, A>::clear()
{
    m_size = 0;
}

template <typename T, template <typename> class A>
inline a_uint32 Vector<T, A>::capacity() const
{
    return m_capacity;
}


template <typename T, template <typename> class A>
inline T& Vector<T, A>::operator[](a_uint32 i)
{
    return *(m_storage + i);
}

template <typename T, template <typename> class A>
inline const T& Vector<T, A>::operator[](a_uint32 i) const
{
    return *(m_storage + i);
}

/*
template <typename T, template <typename> class A> inline const T Vector::operator[] const
{
    return m_storage+i;
}*/
