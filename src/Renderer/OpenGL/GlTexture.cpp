#include <Renderer/OpenGL/GlTexture.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Renderer/OpenGL/GlRenderer.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <Debug/New.h>


namespace Agmd
{
	GLTexture::GLTexture(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, uint32 texture) :
	TextureBase(size,format, hasMipmaps,autoMipmaps),
	m_Texture  (texture)
	{
	}

	GLTexture::~GLTexture()
	{
		if (m_Texture)
			glDeleteTextures(1, &m_Texture);
	}

	uint32 GLTexture::GetGLTexture() const
	{
		return m_Texture;
	}
}
