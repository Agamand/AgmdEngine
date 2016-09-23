/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DxTexture.h>
#include <Renderer/DirectX/DxEnums.h>
#include <Renderer/DirectX/DxDriver.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Debug/New.h>


namespace Agmd
{
    DXTexture::DXTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, ID3D11Resource* texture) :
        TextureBase(size, format, hasMipmaps, autoMipmaps),
        m_Texture(texture)
    {
    }

    DXTexture::~DXTexture()
    {
        m_Texture->Release();
    }

    ID3D11Resource* DXTexture::GetDXTexture() const
    {
        return m_Texture;
    }
}
