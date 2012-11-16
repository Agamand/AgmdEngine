template <int Type>
inline GLBuffer<Type>::GLBuffer(unsigned long count, unsigned int buffer) :
BaseBuffer	(count),
m_Buffer	(buffer)
{}

template <int Type>
inline GLBuffer<Type>::~GLBuffer()
{
    if (m_Buffer)
        GLRenderer::glDeleteBuffers(1, &m_Buffer);
}

template <int Type>
inline unsigned int GLBuffer<Type>::GetBuffer() const
{
    return m_Buffer;
}

template <int Type>
inline void* GLBuffer<Type>::Lock(unsigned long offset, unsigned long size, unsigned long flags)
{
    GLRenderer::glBindBuffer(Type, m_Buffer);
    unsigned char* buffer = reinterpret_cast<unsigned char*>(GLRenderer::glMapBuffer(Type, RGLEnum::LockFlags(flags)));

    return buffer + offset;
}


template <int Type>
inline void GLBuffer<Type>::Unlock()
{
    GLRenderer::glUnmapBuffer(Type);
}
