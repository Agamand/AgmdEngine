
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

}