/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\Buffer\FrameBuffer.h>

namespace Agmd
{
    FrameBuffer::FrameBuffer() :
        m_TextureMap(MAX_ATTACHMENT),
        m_RenderBufferMap(MAX_ATTACHMENT)
    {
    }


    FrameBuffer::~FrameBuffer()
    {
    }
}
