//==========================================================
// Yes::Engine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================


//==========================================================
// En-têtes
//==========================================================
#include <Renderer/OpenGL/GlTexture.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Renderer/OpenGL/GlRenderer.h>
#include <Core\Image.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Utilities/PixelUtils.h>
#include <Debug/New.h>


namespace Agmd
{

	GLTexture::GLTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, uint32 texture) :
	TextureBase(size, format, hasMipmaps, autoMipmaps),
	m_Texture   (texture)
	{}

	GLTexture::~GLTexture()
	{
		if (m_Texture)
			glDeleteTextures(1, &m_Texture);
	}

	uint32 GLTexture::GetGLTexture() const
	{
		return m_Texture;
	}

	void GLTexture::Update(const Rectangle& rect)
	{
		Assert(Rectangle(0, 0, m_Size.x, m_Size.y).Intersects(rect) == INT_IN);

		RGLEnum::TPixelFmt texFmt = RGLEnum::Get(m_Format);
		RGLEnum::TPixelFmt imgFmt = RGLEnum::Get(m_Data.GetFormat());

		glBindTexture(GL_TEXTURE_2D, m_Texture);

		if (FormatCompressed(m_Data.GetFormat()))
		{
			unsigned long dataSize = rect.Width() * rect.Height() * GetBytesPerPixel(m_Data.GetFormat());
			if (rect.Width() == m_Size.x && rect.Height() == m_Size.y)
			{
				GLRenderer::glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, dataSize, m_Data.GetData());
			}
			else
			{
				Image subData = m_Data.SubImage(rect);
				GLRenderer::glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, dataSize, subData.GetData());
			}
		}
		else
		{
			if (!m_HasMipmaps || m_AutoMipmaps)
			{
				if ((rect.Width() == m_Size.x) && (rect.Height() == m_Size.y))
				{
					glTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, imgFmt.Type, m_Data.GetData());
				}
				else
				{
					Image subData = m_Data.SubImage(rect);
					glTexSubImage2D(GL_TEXTURE_2D, 0, rect.Left(), rect.Top(), rect.Width(), rect.Height(), imgFmt.Format, imgFmt.Type, subData.GetData());
				}
			}
			else
			{
				gluBuild2DMipmaps(GL_TEXTURE_2D, texFmt.Internal, m_Size.x, m_Size.y, imgFmt.Format, imgFmt.Type, m_Data.GetData());
			}
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
