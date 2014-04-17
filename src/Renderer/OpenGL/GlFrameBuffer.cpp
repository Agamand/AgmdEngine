/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer\OpenGL\GlFrameBuffer.h>
#include <Renderer\OpenGL\GlRenderer.h>
#include <Renderer\OpenGL\GlTexture.h>
#include <Renderer\OpenGL\GlRenderBuffer.h>
#include <Core\Texture\Texture.h>

namespace Agmd
{

    GLFrameBuffer::GLFrameBuffer(a_uint32 buff_id) : 
    m_Id(buff_id)
    {}

    GLFrameBuffer::~GLFrameBuffer()
    {
        GLDriver::glDeleteFramebuffers(1 ,&m_Id);
    }

    void GLFrameBuffer::SetTexture(const Texture& tex, a_uint32 attach)
    {
        const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
        m_TextureMap[attach] = tex;
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLDriver::glFramebufferTexture(GL_FRAMEBUFFER,RGLEnum::GetAttachment(attach),gl_tex->GetGLTexture(),0);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::SetTextureCube(const Texture& tex, a_uint32 attach, int face)
    {
        if(tex.GetType() != TEXTURE_CUBE)
            return;

        const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
        m_TextureMap[attach] = tex;
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        if(face >= 0 && face < 6)
            GLDriver::glFramebufferTexture2D(GL_FRAMEBUFFER,RGLEnum::GetAttachment(attach),GL_TEXTURE_CUBE_MAP_POSITIVE_X+face,gl_tex->GetGLTexture(),0);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::SetRender(RenderBuffer* render, a_uint32 attach)
    {
        m_RenderBufferMap[attach] = render;
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLDriver::glFramebufferRenderbuffer(GL_FRAMEBUFFER, RGLEnum::GetAttachment(attach), GL_RENDERBUFFER, static_cast<GLRenderBuffer*>(m_RenderBufferMap[attach])->GetID());
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::Bind()
    {
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
    }

    void GLFrameBuffer::UnBind()
    {
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    a_uint32 GLFrameBuffer::GetID()
    {
        return m_Id;
    }

    void GLFrameBuffer::Clear(a_uint32 flags)
    {
        a_uint32 _flags = 0;

        if(flags & CLEAR_COLOR)
            _flags |= GL_COLOR_BUFFER_BIT;

        if(flags & CLEAR_DEPTH)
            _flags |= GL_DEPTH_BUFFER_BIT;

        if(flags & CLEAR_STENCIL)
            _flags |= GL_STENCIL_BUFFER_BIT;

        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glClear(_flags);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::DrawBuffer(a_uint32 flag)
    {
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glDrawBuffer(flag);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::DrawBuffers(a_uint32 nbuffer, a_uint32* flag)
    {
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLDriver::glDrawBuffers(nbuffer, flag);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    a_uint32* GLFrameBuffer::GenerateBufferFlags(a_uint32 count, a_uint32 flags[])
    {
        if(!count)
            return NULL;
        a_uint32* buffer = new a_uint32[count];
        for(a_uint32 i = 0; i < count; i++)
            buffer[i] = RGLEnum::GetAttachment(flags[i]);
        return buffer;
    }
	a_uint32* GLFrameBuffer::GenerateBufferFlags(a_uint32* buffer,a_uint32 count, a_uint32 flags[])
	{
		if(!count)
			return NULL;
		for(a_uint32 i = 0; i < count; i++)
			buffer[i] = RGLEnum::GetAttachment(flags[i]);
		return buffer;
	}

    void GLFrameBuffer::ReadBuffer(a_uint32 flag)
    {
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glReadBuffer(flag);
        GLDriver::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
}
