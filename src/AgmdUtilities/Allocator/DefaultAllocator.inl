template <typename T> 
inline DefaultAllocator<T>::DefaultAllocator()
{}

template <typename T> 
inline DefaultAllocator<T>::~DefaultAllocator()
{}
    
template <typename T>
inline T* DefaultAllocator<T>::Allocate(size_t count)
{
    if(count)
        return new T[count];
    return new T;
}

template <typename T>
inline void DefaultAllocator<T>::UnAllocate(T* ptr, bool isArray)
{
    if(isArray)
        delete[] ptr;
    else delete ptr;
}