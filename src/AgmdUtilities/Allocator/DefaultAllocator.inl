template <typename T>
inline DefaultAllocator<T>::DefaultAllocator()
{
}

template <typename T>
inline DefaultAllocator<T>::~DefaultAllocator()
{
}

template <typename T>
inline T* DefaultAllocator<T>::Allocate(size_t count)
{
    if (count > 1)
        return new T[count];
    return new T;
}

template <typename T>
inline void DefaultAllocator<T>::UnAllocate(T* ptr, size_t count)
{
    if (count > 1)
        delete[] ptr;
    else delete ptr;
}
