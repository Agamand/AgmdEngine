/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/BlurMotionEffect.h>
#include <Core/Texture/Texture.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{

    BlurMotionEffect::BlurMotionEffect(const ivec2& screen_size)
    {
        m_accumulate.Create(screen_size,PXF_A8R8G8B8,TEXTURE_2D,TEX_NOMIPMAP);
        m_program.LoadFromFile("Shader/Effect/blurmotioneffect.glsl");
    }
    void BlurMotionEffect::Init()
    {}

    void BlurMotionEffect::Update(a_uint64 /*t_diff*/)
    {}

    void BlurMotionEffect::ApplyEffect(Texture& input, Texture& output)
    {
        Texture::BeginRenderToTexture(output);
        Driver::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Driver::Get().SetTexture(0,input.GetTexture());
        Driver::Get().SetTexture(1,m_accumulate.GetTexture());
        Fast2DSurface::Instance().Draw();
        Driver::Get().SetCurrentProgram(NULL);
        Texture::EndRenderToTexture();

        //save new accumulate buffer !
        Texture::BeginRenderToTexture(m_accumulate);
        Texture::TextureRender(output);
        Texture::EndRenderToTexture();
    }

    void BlurMotionEffect::SetIntensity(float a)
    {
        m_program.Enable();
        m_program.SetParameter("u_intensity",a);
        m_program.Disable();
    }
}
