/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/Inverse.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{
    Inverse::Inverse()
    {
        m_program.LoadFromFile("Shader/Effect/inverse.glsl");
    }

    void Inverse::Init()
    {
    }

    void Inverse::Update(a_uint64 /*t_diff*/)
    {
    }

    void Inverse::ApplyEffect(Texture& input, Texture& output)
    {
        Texture::BeginRenderToTexture(output);
        Driver::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Driver::Get().SetTexture(0, input.GetTexture());
        Fast2DSurface::Instance().Draw();
        Driver::Get().SetCurrentProgram(NULL);
        Texture::EndRenderToTexture();
    }
}
