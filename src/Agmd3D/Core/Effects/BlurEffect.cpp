/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/BlurEffect.h>
#include <Core/Texture/Texture.h>
#include <Core/Renderer.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{

    BlurEffect::BlurEffect(const Texture& depth) :
    m_depth(depth)
    {
        m_program.LoadFromFile("Shader/Effect/blureffect.glsl");
    }

    void BlurEffect::Init()
    {}

    void BlurEffect::Update(a_uint64 /*t_diff*/)
    {}

    void BlurEffect::ApplyEffect(Texture& input, Texture& output)
    {
        Texture::BeginRenderToTexture(output);
        Renderer::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Renderer::Get().SetTexture(0,input.GetTexture());
        Fast2DSurface::Instance().Draw();
        Renderer::Get().SetCurrentProgram(NULL);
        Texture::EndRenderToTexture();
    }

    void BlurEffect::SetNoiseOffset(float a)
    {
        m_program.Enable();
        m_program.SetParameter("offset",a);
        m_program.Disable();
    }
}
