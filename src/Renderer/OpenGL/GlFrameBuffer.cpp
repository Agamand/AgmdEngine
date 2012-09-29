#include <Renderer\OpenGL\GlFrameBuffer.h>
#include <Renderer\OpenGL\GlRenderer.h>
#include <Renderer\OpenGL\GlTexture.h>
#include <Renderer\OpenGL\GlRenderBuffer.h>

namespace Agmd
{

	GLFrameBuffer::GLFrameBuffer(uint32 buff_id) : 
	m_Id(buff_id)
	{}

	GLFrameBuffer::~GLFrameBuffer()
	{
		GLRenderer::glDeleteFramebuffers(1 ,&m_Id);
	}

	void GLFrameBuffer::setTexture(TextureBase* tex, TAttachment attach)
	{
		m_TextureMap[attach] = tex;
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
		GLRenderer::glFramebufferTexture(GL_FRAMEBUFFER,RGLEnum::Get(attach),static_cast<GLTexture*>(m_TextureMap[attach])->GetGLTexture(),0);
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
	}

	void GLFrameBuffer::UnBind()
	{
		GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

}
