template <int Type>
inline GLBuffer<Type>::GLBuffer(unsigned long count, unsigned int buffer, int bindPoint) :
BaseBuffer	(count),
m_Buffer	(buffer),
m_bindPoint	(bindPoint)
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
inline int GLBuffer<Type>::GetBindPoint() const
{
    return -1;
}

template<>
inline int GLBuffer<GL_UNIFORM_BUFFER>::GetBindPoint() const
{
	return m_bindPoint;
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
