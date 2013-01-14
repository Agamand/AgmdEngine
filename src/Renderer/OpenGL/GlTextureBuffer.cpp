/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/OpenGL/GlTextureBuffer.h>
#include <Renderer/OpenGL/GlRenderer.h>

namespace Agmd
{
    GLTextureBuffer::GLTextureBuffer(unsigned long count, unsigned int buffer, TextureBase* texture) : 
    GLBuffer(count,buffer),
    m_textureBuffer(texture)
    {}

    const TextureBase* GLTextureBuffer::getTexture() const
    {
        return m_textureBuffer;
    }
}