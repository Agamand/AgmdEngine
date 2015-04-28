/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLTEXTUREBUFFER_H_
#define _GLTEXTUREBUFFER_H_

#include <Renderer/OpenGL/GlBuffer.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Core/Texture/TextureBase.h>

namespace Agmd
{
    class GLTextureBuffer : public GLBuffer<GL_TEXTURE_BUFFER,1>
    {
    public :
        GLTextureBuffer(unsigned long count, unsigned int buffer, TextureBase* texture);

        const TextureBase* getTexture() const;

    private:
        TextureBase* m_textureBuffer;
    };

}


#endif /* _GLTEXTUREBUFFER_H_ */
