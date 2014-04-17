/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/OpenGL/GlTextureCube.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Renderer/OpenGL/GlRenderer.h>
#include <Core/Texture/Image.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Utilities/PixelUtils.h>
#include <Debug/New.h>


namespace Agmd
{

    GLTextureCube::GLTextureCube(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, a_uint32 texture) :
    GLTexture(size, format, hasMipmaps, autoMipmaps, texture)
    {
        for(a_int32 i = 0; i < MAX_CUBEFACE; i++)
            m_Data[i] = Image(size,format);
    }

    GLTextureCube::~GLTextureCube()
    {}

    TTextureType GLTextureCube::GetType() const
    {
        return TEXTURE_CUBE;
    }

    void GLTextureCube::Update(const AgmdMaths::Rectangle& rect)
    {
        Assert(AgmdMaths::Rectangle(0, 0, m_Size.x, m_Size.y).Intersects(rect) == INT_IN);

        glBindTexture(GL_TEXTURE_CUBE_MAP,m_Texture);
        for(int i = 0; i < 6; i++)
        {
        RGLEnum::TPixelFmt texFmt = RGLEnum::Get(m_Format);
        RGLEnum::TPixelFmt imgFmt = RGLEnum::Get(m_Data[i].GetFormat());
        unsigned long dataSize = rect.Width() * rect.Height() * GetBytesPerPixel(m_Data[i].GetFormat());
            if (FormatCompressed(m_Data[i].GetFormat()))
            {
                if (rect.Width() == m_Size.x && rect.Height() == m_Size.y)
                {
                    GLDriver::glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, dataSize, m_Data[i].GetData());
                }
                else
                {
                    Image subData = m_Data[i].SubImage(rect);
                    GLDriver::glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, dataSize, subData.GetData());
                }
            }
            else
            {
                if ((rect.Width() == m_Size.x) && (rect.Height() == m_Size.y))
                {
                    glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, imgFmt.Type, m_Data[i].GetData());
                }
                else
                {
                    Image subData = m_Data[i].SubImage(rect);
                    glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, imgFmt.Type, subData.GetData());
                }
            }
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    Image* GLTextureCube::getPixels()
    {
        return m_Data;
    }

}
