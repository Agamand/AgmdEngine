/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include <Core/Texture/TextureBase.h>
#include <CommonDefines.h>

namespace Agmd
{
    class GLTexture : public TextureBase
    {
    public :
        GLTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, a_uint32 texture);
        ~GLTexture();

        a_uint32 GetGLTexture() const;
    protected :
        a_uint32 m_Texture;
    };
}


#endif /* _GLTEXTURE_H_ */
