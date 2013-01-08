#ifndef OGLTEXTURE_H
#define OGLTEXTURE_H

#include <Renderer/OpenGL/GlTexture.h>
#include <Core/Texture/Image.h>

namespace Agmd
{
    class GLTexture2D : public GLTexture
    {
    public :

        GLTexture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, uint32 texture);

        ~GLTexture2D();

        virtual TTextureType GetType() const;

        virtual Image* getPixels();
    private :

        virtual void Update(const AgmdMaths::Rectangle& rect);

        Image        m_Data;
    };
}


#endif //OGLTEXTURE_H
