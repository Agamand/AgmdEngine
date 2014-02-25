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
        GLRenderer::glDeleteFramebuffers(1 ,&m_Id);
    }

    void GLFrameBuffer::SetTexture(const Texture& tex, a_uint32 attach)
    {
        const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
        m_TextureMap[attach] = tex;
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLRenderer::glFramebufferTexture(GL_FRAMEBUFFER,RGLEnum::GetAttachment(attach),gl_tex->GetGLTexture(),0);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::SetTextureCube(const Texture& tex, a_uint32 attach, int face)
    {
        if(tex.GetType() != TEXTURE_CUBE)
            return;

        const GLTexture* gl_tex = static_cast<const GLTexture*>(tex.GetTexture());
        m_TextureMap[attach] = tex;
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        if(face >= 0 && face < 6)
            GLRenderer::glFramebufferTexture2D(GL_FRAMEBUFFER,RGLEnum::GetAttachment(attach),GL_TEXTURE_CUBE_MAP_POSITIVE_X+face,gl_tex->GetGLTexture(),0);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::SetRender(RenderBuffer* render, a_uint32 attach)
    {
        m_RenderBufferMap[attach] = render;
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLRenderer::glFramebufferRenderbuffer(GL_FRAMEBUFFER, RGLEnum::GetAttachment(attach), GL_RENDERBUFFER, static_cast<GLRenderBuffer*>(m_RenderBufferMap[attach])->GetID());
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

        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glClear(_flags);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::DrawBuffer(a_uint32 flag)
    {
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glDrawBuffer(flag);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }

    void GLFrameBuffer::DrawBuffers(a_uint32 nbuffer, a_uint32* flag)
    {
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        GLRenderer::glDrawBuffers(nbuffer, flag);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
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

    void GLFrameBuffer::ReadBuffer(a_uint32 flag)
    {
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,m_Id);
        glReadBuffer(flag);
        GLRenderer::glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
}
