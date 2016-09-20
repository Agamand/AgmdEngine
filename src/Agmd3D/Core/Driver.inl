/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T>
inline Buffer<T> Driver::CreateVertexBuffer(unsigned long size, unsigned long flags, const T* data) const
{
    Buffer<T> buffer(CreateVB(size, sizeof(T), flags));
    if (data)
        buffer.Fill(data, size);

    return buffer;
}

template <class T>
inline Buffer<T> Driver::CreateIndexBuffer(unsigned long size, unsigned long flags, const T* data) const
{
    Buffer<T> buffer(CreateIB(size, sizeof(T), flags));
    if (data)
        buffer.Fill(data, size);

    return buffer;
}

template <class T>
inline Buffer<T> Driver::CreateUniformBuffer(unsigned long size, unsigned long flags, int bindPoint, int ubflags, const T* data) const
{
    Buffer<T> buffer(CreateUB(size, sizeof(T), flags, bindPoint, ubflags));
    if (data)
        buffer.Fill(data, size);

    return buffer;
}

template <class T>
inline Buffer<T> Driver::CreateTextureBuffer(unsigned long size, unsigned long flags, const T* data) const
{
    Buffer<T> buffer(CreateTB(size, sizeof(T), flags));
    if (data)
        buffer.Fill(data, size);

    return buffer;
}

template <class T>
inline void Driver::SetVertexBuffer(unsigned int stream, const Buffer<T>& buffer, unsigned long minVertex, unsigned long maxVertex)
{
    SetVB(stream, buffer.GetBuffer(), sizeof(T), minVertex, maxVertex ? maxVertex : buffer.GetCount() - 1);
}

template <class T>
inline void Driver::SetIndexBuffer(const Buffer<T>& buffer)
{
    SetIB(buffer.GetBuffer(), sizeof(T));
}

template <std::size_t N>
Declaration* Driver::CreateVertexDeclaration(const TDeclarationElement (&elt)[N]) const
{
    return CreateDeclaration(elt, N);
}

inline void Driver::SetCurrentTransform(const Transform* transform)
{
    m_CurrentTransform = transform;
}
