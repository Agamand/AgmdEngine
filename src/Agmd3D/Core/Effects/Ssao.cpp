/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/Ssao.h>
#include <Core/Texture/Texture.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{
    Ssao::Ssao(Texture& depth, Texture& normal, Texture& position, Texture& noise) :
        m_depth(depth), m_normal(normal), m_position(position), m_noise(noise)
    {
        m_program.LoadFromFile("Shader/Effect/ssao.glsl");
        m_blurProgram.LoadFromFile("Shader/common/blur4.glsl");
    }

    void Ssao::Init()
    {
    }

    void Ssao::Update(a_uint64 /*t_diff*/)
    {
    }

    void Ssao::CreateSsao(Texture& output)
    {
        Driver& driver = Driver::Get();

        driver.SetCurrentProgram(m_program.GetShaderProgram());
        //driver.SetTexture(0,input.GetTexture());
        driver.SetTexture(0, m_depth.GetTexture());
        driver.SetTexture(1, m_normal.GetTexture());
        //driver.SetTexture(3,m_position.GetTexture());
        driver.SetTexture(2, m_noise.GetTexture());
        Texture::BeginRenderToTexture(output);
        Fast2DSurface::Instance().Draw();
        Texture::EndRenderToTexture();
        driver.SetCurrentProgram(NULL);
    }

    void Ssao::ApplyEffect(Texture& input, Texture& output)
    {
        CreateSsao(m_buffer[0]);
        ApplyBlur(m_buffer[0], m_buffer[1]);
        ApplySsao(input, output);
    }

    void Ssao::ApplySsao(Texture& input, Texture& output)
    {
    }

    void Ssao::ApplyBlur(Texture& input, Texture& output)
    {
    }
}
