#include <Renderer\OpenGL\GlFrameBuffer.h>
#include <Renderer\OpenGL\GlRenderer.h>
#include <Renderer\OpenGL\GlTexture.h>
#include <Renderer\OpenGL\GlRenderBuffer.h>
#include <Core\Texture\Texture.h>

namespace Agmd
{

	GLFrameBuffer::GLFrameBuffer(uint32 buff_id) : 
	m_Id(buff_id)
	{}

	GLFrameBuffer::~GLFrameBuffer()
	{
		GLRenderer::glDeleteFramebuffers(1 ,&m_Id);
	}

	void GLFrameBuffer::setTexture(Texture tex, TAttachment attach)
	{
		//if(tex.GetType() != TEXTURE_2D)
			//return;

		const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
		m_TextureMap[attach] = tex;
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		GLRenderer::glFramebufferTexture(GL_FRAMEBUFFER,RGLEnum::Get(attach),gl_tex->GetGLTexture(),0);
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void GLFrameBuffer::setTextureCube(Texture tex, TAttachment attach, int face)
	{
		if(tex.GetType() != TEXTURE_CUBE)
			return;

		const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
		m_TextureMap[attach] = tex;
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		if(face >= 0 && face < 6)
			GLRenderer::glFramebufferTexture2D(GL_FRAMEBUFFER,RGLEnum::Get(attach),GL_TEXTURE_CUBE_MAP_POSITIVE_X+face,gl_tex->GetGLTexture(),0);
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void GLFrameBuffer::setRender(RenderBuffer* render, TAttachment attach)
	{
		m_RenderBufferMap[attach] = render;
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		GLRenderer::glFramebufferRenderbuffer(GL_FRAMEBUFFER, RGLEnum::Get(attach), GL_RENDERBUFFER, static_cast<GLRenderBuffer*>(m_RenderBufferMap[attach])->GetID());
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void GLFrameBuffer::Bind()
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
		for(RenderBufferMap::iterator itr = m_RenderBufferMap.begin(); itr != m_RenderBufferMap.end(); itr++)
		{
			GLRenderer::glBindRenderbuffer(GL_RENDERBUFFER,static_cast<GLRenderBuffer*>(itr->second)->GetID());
		}
	}

	void GLFrameBuffer::UnBind()
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		for(RenderBufferMap::iterator itr = m_RenderBufferMap.begin(); itr != m_RenderBufferMap.end(); itr++)
		{
			GLRenderer::glBindRenderbuffer(GL_RENDERBUFFER,0);
		}
	}

	uint32 GLFrameBuffer::GetID()
	{
		return m_Id;
	}

	void GLFrameBuffer::Clear()
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void GLFrameBuffer::DrawBuffer(uint32 flag)
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		glDrawBuffer(flag);
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

	void GLFrameBuffer::ReadBuffer(uint32 flag)
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		glReadBuffer(flag);
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
}
