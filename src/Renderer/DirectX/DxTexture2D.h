/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXTEXTURE2D_H_
#define _DXTEXTURE2D_H_

#include <Renderer/DirectX/DxTexture.h>
#include <Core/Texture/Image.h>

namespace Agmd
{
    class DXTexture2D : public DXTexture
    {
    public :

        DXTexture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, ID3D11Texture2D* texture);

        ~DXTexture2D();

        virtual TTextureType GetType() const;

        virtual Image* getPixels();
    private :

        virtual void Update(const AgmdMaths::Rectangle& rect);

        virtual void updatePixelFromTexture();

        Image        m_Data;
    };
}


#endif /* _DXTEXTURE2D_H_ */
