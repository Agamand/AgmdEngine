/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <int Type, int bufferCount>
inline DXBuffer<Type, bufferCount>::DXBuffer(unsigned long count, unsigned int* buffer) :
BaseBuffer    (count),
//m_Buffer   (buffer),
m_currentBuffer(0),
m_bufferCount(sizeof(m_Buffer)/sizeof(int)),
m_sync (NULL)
{
    for(a_uint32 i = 0; i < m_bufferCount; i++)
        m_Buffer[i] = buffer[i]; //temp
}

template <int Type, int bufferCount>
inline DXBuffer<Type, bufferCount>::~DXBuffer()
{
//     if (m_Buffer) // fail 
//         DXDriver::glDeleteBuffers(m_bufferCount, m_Buffer);
    if(m_sync)
        //DXDriver::glDeleteSync(m_sync);
}

template <int Type, int bufferCount>
inline unsigned int DXBuffer<Type, bufferCount>::GetBuffer() const
{
    return m_Buffer[m_currentBuffer];
}

template <int Type, int bufferCount>
inline void* DXBuffer<Type, bufferCount>::Lock(unsigned long offset, unsigned long size, unsigned long flags)
{
    //DXDriver::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
    unsigned char* buffer = reinterpret_cast<unsigned char*>(DXDriver::glMapBuffer(Type, RGLEnum::LockFlags(flags)));

    return buffer + offset;
}

template <int Type, int bufferCount>
inline void* DXBuffer<Type, bufferCount>::LockByte(unsigned long offset, unsigned long size, unsigned long flags)
{
    //DXDriver::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
   // unsigned char* buffer = reinterpret_cast<unsigned char*>(DXDriver::glMapBufferRange(Type, offset, size, RGLEnum::LockBitsFlags(flags) | GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_INVALIDATE_RANGE_BIT));
    //if(flags & LOCK_SYNC_WAIT)
        //m_sync = DXDriver::glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
    return buffer;
}

template <int Type, int bufferCount>
inline void DXBuffer<Type, bufferCount>::FillByte(unsigned char* data, unsigned long offset, unsigned long size)
{
    //DXDriver::glBindBuffer(Type, m_Buffer[m_currentBuffer]);
    //DXDriver::DXBufferSubData(Type,offset,size,data);
}

template <int Type, int bufferCount>
inline void DXBuffer<Type, bufferCount>::Unlock()
{
    //DXDriver::glUnmapBuffer(Type);
}


template <int Type, int bufferCount>
inline void DXBuffer<Type, bufferCount>::Flush()
{
    //glFlush();
}

template <int Type, int bufferCount>
inline void DXBuffer<Type, bufferCount>::Bind(a_uint32 /*bindpoint*/)
{}

#define TIMEOUT 100000
template <int Type, int bufferCount>
void DXBuffer<Type, bufferCount>::WaitSync()
{
//     DXDriver::glClientWaitSync(m_sync,0,TIMEOUT);
//     DXDriver::glDeleteSync(m_sync);
//     m_sync = NULL;
}
#undef TIMEOUT

/* partial template
template <int Type>
void DXBuffer<Type, 1>::SwapBuffers()
{}

template <int Type>
void DXBuffer<Type, 2>::SwapBuffers()
{
    m_currentBuffer = m_currentBuffer ? 0 : 1;
}*/

template <int Type, int bufferCount>
void DXBuffer<Type, bufferCount>::SwapBuffers()
{
    m_currentBuffer = (m_currentBuffer+1)%m_bufferCount;
}
