#include <Core/Effects/PostEffect.h>
#include <Core/Driver.h>

namespace Agmd
{
    PostEffect::PostEffect()
    {
        m_framebuffer = Driver::Get().CreateFrameBuffer();
    }

    PostEffect::~PostEffect()
    {
        delete m_framebuffer;
    }

    void PostEffect::SetEnable(bool enable)
    {
        Driver::Get().SetCurrentProgram(m_program.GetShaderProgram());
        m_program.SetParameter("u_enable", (int)enable);
        Driver::Get().SetCurrentProgram(NULL);
    }
}
