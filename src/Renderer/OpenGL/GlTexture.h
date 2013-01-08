#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include <Core/Texture/TextureBase.h>
#include <AgmdDefines.h>

namespace Agmd
{
    class GLTexture : public TextureBase
    {
    public :
        GLTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, uint32 texture);
        ~GLTexture();

        uint32 GetGLTexture() const;
    protected :
        uint32 m_Texture;
    };
}


#endif //_GLTEXTURE_H_
