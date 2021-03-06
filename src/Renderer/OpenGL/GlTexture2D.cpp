/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/OpenGL/GlTexture2D.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Renderer/OpenGL/GlDriver.h>
#include <Core/Texture/Image.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Utilities/PixelUtils.h>


namespace Agmd
{
    GLTexture2D::GLTexture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, a_uint32 texture) :
        GLTexture(size, format, hasMipmaps, autoMipmaps, texture),
        m_Data(size, format)
    {
    }

    GLTexture2D::~GLTexture2D()
    {
    }

    TTextureType GLTexture2D::GetType() const
    {
        return TEXTURE_2D;
    }

    void GLTexture2D::Update(const AgmdMaths::Rectangle& rect)
    {
        Assert(AgmdMaths::Rectangle(0, 0, m_Size.x, m_Size.y).intersects(rect) == INT_IN);

        RGLEnum::TPixelFmt texFmt = RGLEnum::Get(m_Format);
        RGLEnum::TPixelFmt imgFmt = RGLEnum::Get(m_Data.GetFormat());
        unsigned long dataSize = rect.width() * rect.height() * GetBytesPerPixel(m_Data.GetFormat());

        glBindTexture(GL_TEXTURE_2D, m_Texture);

        if (FormatCompressed(m_Data.GetFormat()))
        {
            if (rect.width() == m_Size.x && rect.height() == m_Size.y)
            {
                GLDriver::glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, rect.left(), rect.top(), rect.width(), rect.height(), imgFmt.Format, dataSize, m_Data.GetData());
            }
            else
            {
                Image subData = m_Data.SubImage(rect);
                GLDriver::glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, rect.left(), rect.top(), rect.width(), rect.height(), imgFmt.Format, dataSize, subData.GetData());
            }
        }
        else
        {
            if (!m_HasMipmaps || m_AutoMipmaps)
            {
                if ((rect.width() == m_Size.x) && (rect.height() == m_Size.y))
                {
                    glTexSubImage2D(GL_TEXTURE_2D, 0, rect.left(), rect.top(), rect.width(), rect.height(), imgFmt.Format, imgFmt.Type, m_Data.GetData());
                }
                else
                {
                    Image subData = m_Data.SubImage(rect);
                    glTexSubImage2D(GL_TEXTURE_2D, 0, rect.left(), rect.top(), rect.width(), rect.height(), imgFmt.Format, imgFmt.Type, subData.GetData());
                }
            }
            else
            {
                gluBuild2DMipmaps(GL_TEXTURE_2D, texFmt.Internal, m_Size.x, m_Size.y, imgFmt.Format, imgFmt.Type, m_Data.GetData());
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Image* GLTexture2D::getPixels()
    {
        return &m_Data;
    }

    void GLTexture2D::updatePixelFromTexture()
    {
        RGLEnum::TPixelFmt texFmt = RGLEnum::Get(m_Format);
        RGLEnum::TPixelFmt imgFmt = RGLEnum::Get(m_Data.GetFormat());
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glGetTexImage(GL_TEXTURE_2D, 0, texFmt._Format, m_Format == PXF_DEPTH ? GL_FLOAT : GL_UNSIGNED_BYTE, m_Data.GetDataPtr());
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
