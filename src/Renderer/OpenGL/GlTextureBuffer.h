#ifndef GLTEXTUREBUFFER_H
#define GLTEXTUREBUFFER_H

#include <Renderer/OpenGL/GlBuffer.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Core/Texture/TextureBase.h>

namespace Agmd
{
    class GLTextureBuffer : public GLBuffer<GL_TEXTURE_BUFFER>
    {
    public :
        GLTextureBuffer(unsigned long count, unsigned int buffer, TextureBase* texture);
        //virtual ~GLTextureBuffer();

		const TextureBase* getTexture() const;

	private:
        TextureBase* m_textureBuffer;
    };

}


#endif /* _GLTEXTUREBUFFER_H_ */
