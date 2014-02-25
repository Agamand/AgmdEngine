
#include <Core/Effects/PostEffect.h>
#include <Core/Renderer.h>
namespace Agmd
{
    PostEffect::PostEffect()
    {
        m_framebuffer = Renderer::Get().CreateFrameBuffer();
    }
    
    PostEffect::~PostEffect()
    {
        delete m_framebuffer;
    }

    void PostEffect::SetEnable(bool enable)
    {
        Renderer::Get().SetCurrentProgram(m_program.GetShaderProgram());
        m_program.SetParameter("u_enable",(int)enable);
        Renderer::Get().SetCurrentProgram(NULL);
    }

}