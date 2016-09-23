/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DxTexture2D.h>
#include <Renderer/DirectX/DxEnums.h>
#include <Renderer/DirectX/DxDriver.h>
#include <Core/Texture/Image.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Utilities/PixelUtils.h>


namespace Agmd
{
    DXTexture2D::DXTexture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, ID3D11Texture2D* texture) :
        DXTexture(size, format, hasMipmaps, autoMipmaps, texture),
        m_Data(size, format)
    {
    }

    DXTexture2D::~DXTexture2D()
    {
    }

    TTextureType DXTexture2D::GetType() const
    {
        return TEXTURE_2D;
    }

    void DXTexture2D::Update(const AgmdMaths::Rectangle& rect)
    {
        Assert(AgmdMaths::Rectangle(0, 0, m_Size.x, m_Size.y).intersects(rect) == INT_IN);

        auto texFmt = DXEnum::Get(m_Format);
        auto imgFmt = DXEnum::Get(m_Data.GetFormat());
        ID3D11Texture2D* tex = static_cast<ID3D11Texture2D*>(m_Texture);
        DXDriver& driver = DXDriver::Instance();
        unsigned long dataSize = rect.width() * rect.height() * GetBytesPerPixel(m_Data.GetFormat());
        if (FormatCompressed(m_Data.GetFormat()))
        {
            //unsupported now
        }
        else
        {
            D3D11_BOX box;
            box.left = rect.left();
            box.right = rect.right();
            box.top = rect.top();
            box.bottom = rect.bottom();
            box.front = 0;
            box.back = 1;
            driver.DeviceContext()->UpdateSubresource(m_Texture, 0, &box, m_Data.GetData(), 0, 0);
        }
    }

    Image* DXTexture2D::getPixels()
    {
        return &m_Data;
    }

    void DXTexture2D::updatePixelFromTexture()
    {
        auto texFmt = DXEnum::Get(m_Format);
        auto imgFmt = DXEnum::Get(m_Data.GetFormat());
        //         glBindTexture(GL_TEXTURE_2D, m_Texture);
        //         glGetTexImage(GL_TEXTURE_2D,0,texFmt._Format,imgFmt.Type,m_Data.GetDataPtr());
        //         glBindTexture(GL_TEXTURE_2D, 0);
    }
}
