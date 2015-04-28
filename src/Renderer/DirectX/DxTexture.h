/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_

#include <Core/Texture/TextureBase.h>
#include <CommonDefines.h>

namespace Agmd
{
    class DXTexture : public TextureBase
    {
    public :
        DXTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, a_uint32 texture);
        ~DXTexture();

        a_uint32 GetDXTexture() const;
    protected :
        a_uint32 m_Texture;
    };
}


#endif /* _DXTEXTURE_H_ */
