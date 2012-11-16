#ifndef _GLTEXTURECUBE_H_
#define _GLTEXTURECUBE_H_

#include <Core/Texture/Image.h>
#include <Renderer/OpenGL/GlTexture.h>

#define MAX_CUBEFACE 6

namespace Agmd
{
    class GLTextureCube : public GLTexture
    {
    public :

        GLTextureCube(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, uint32 texture);

        ~GLTextureCube();

		virtual TTextureType GetType() const;

		virtual Image* getPixels();

    private :

        virtual void Update(const AgmdMaths::Rectangle& rect);

		Image m_Data[MAX_CUBEFACE];

    };
}


#endif /* _GLTEXTURECUBE_H_ */
