/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <int Type, int bufferCount>
inline GLBuffer<Type, bufferCount>::GLBuffer(unsigned long count, unsigned int* buffer) :
BaseBuffer    (count),
//m_Buffer   (buffer),
m_currentBuffer(0),
m_bufferCount(sizeof(m_Buffer)/sizeof(int)),
m_sync (NULL)
{
    for(int i = 0; i < m_bufferCount; i++)
        m_Buffer[i] = buffer[i]; //temp
}

template <int Type, int bufferCount>
inline GLBuffer<Type, bufferCount>::~GLBuffer()
{
    if (m_Buffer)
        GLRenderer::glDeleteBuffers(m_bufferCount, m_Buffer);
    if(m_sync)
        GLRenderer::glDeleteSync(m_sync);
}

template <int Type, int bufferCount>
inline unsigned int GLBuffer<Type, bufferCount>::GetBuffer() const
{
    return m_Buffer[m_currentBuffer];
}

template <int Type, int bufferCount>
inline void* GLBuffer<Type, bufferCount>::Lock(unsigned long offset, unsigned long size, unsigned long flags)
{
    GLRenderer::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
    unsigned char* buffer = reinterpret_cast<unsigned char*>(GLRenderer::glMapBuffer(Type, RGLEnum::LockFlags(flags)));

    return buffer + offset;
}

template <int Type, int bufferCount>
inline void* GLBuffer<Type, bufferCount>::LockBits(unsigned long offset, unsigned long size, unsigned long flags)
{
    GLRenderer::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
    unsigned char* buffer = reinterpret_cast<unsigned char*>(GLRenderer::glMapBufferRange(Type, offset, size, RGLEnum::LockBitsFlags(flags) | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_INVALIDATE_RANGE_BIT));
    if(flags & LOCK_SYNC_WAIT)
        m_sync = GLRenderer::glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
    return buffer;
}

template <int Type, int bufferCount>
inline void GLBuffer<Type, bufferCount>::FillByte(unsigned char* data, unsigned long offset, unsigned long size)
{
    GLRenderer::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
    GLRenderer::glBufferSubData(Type,offset,size,data);
}

template <int Type, int bufferCount>
inline void GLBuffer<Type, bufferCount>::Unlock()
{
    GLRenderer::glUnmapBuffer(Type);
}


template <int Type, int bufferCount>
inline void GLBuffer<Type, bufferCount>::Flush()
{
    glFlush();
}

template <int Type, int bufferCount>
inline void GLBuffer<Type, bufferCount>::Bind(uint32 /*bindpoint*/)
{}

#define TIMEOUT 100000
template <int Type, int bufferCount>
void GLBuffer<Type, bufferCount>::WaitSync()
{
    GLRenderer::glClientWaitSync(m_sync,0,TIMEOUT);
    GLRenderer::glDeleteSync(m_sync);
    m_sync = NULL;
}
#undef TIMEOUT

/* partial template
template <int Type>
void GLBuffer<Type, 1>::SwapBuffers()
{}

template <int Type>
void GLBuffer<Type, 2>::SwapBuffers()
{
    m_currentBuffer = m_currentBuffer ? 0 : 1;
}*/

template <int Type, int bufferCount>
void GLBuffer<Type, bufferCount>::SwapBuffers()
{
    m_currentBuffer = (m_currentBuffer+1)%m_bufferCount;
}
