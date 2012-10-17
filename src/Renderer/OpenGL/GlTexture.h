#ifndef OGLTEXTURE_H
#define OGLTEXTURE_H

#include <Core/TextureBase.h>


namespace Agmd
{
    class GLTexture : public TextureBase
    {
    public :

        GLTexture(const ivec2& size, TPixelFormat format, TTextureType type, bool hasMipmaps, bool autoMipmaps, uint32 texture);

        ~GLTexture();

        uint32 GetGLTexture() const;
		int GetActiveTexture() { return activeTexture;}

    private :

        virtual void Update(const AgmdMaths::Rectangle& rect);

		virtual void SetActiveTexture(int32 id);
		

        uint32 m_Texture;
    };
}


#endif //OGLTEXTURE_H
