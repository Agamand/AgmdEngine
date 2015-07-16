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

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

namespace Agmd
{
    class DXTexture : public TextureBase
    {
    public :
        DXTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, ID3D11Resource* texture);
        ~DXTexture();

        ID3D11Resource* GetDXTexture() const;
    protected :
        ID3D11Resource* m_Texture;
    };
}


#endif /* _DXTEXTURE_H_ */
