/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/AsciEffect.h>
#include <Core/Texture/Texture.h>
#include <Core/Renderer.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/MediaManager.h>
#include <core/ResourceManager.h>

namespace Agmd
{

    AsciEffect::AsciEffect() : m_speed(1),m_time(0)
    {
        m_program.LoadFromFile("Shader/Effect/ascieffect.glsl");
        m_asciTable.CreateFromFile("Texture/DC39_FS_Texture_0.png",PXF_A8R8G8B8);
    }

    void AsciEffect::Init()
    {}

    void AsciEffect::Update(a_uint64 t_diff)
    {
        m_time +=(int)t_diff;
        m_time %=(int)(1000/m_speed);
    }

    void AsciEffect::ApplyEffect(Texture& input, Texture& output)
    {
        Texture::BeginRenderToTexture(output);
        Driver::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Driver::Get().SetTexture(0,input.GetTexture());
        Driver::Get().SetTexture(1,m_asciTable.GetTexture());
        m_program.SetParameter("u_time",(float)m_time/1000*m_speed);
        Fast2DSurface::Instance().Draw();
        Driver::Get().SetCurrentProgram(NULL);
        Texture::EndRenderToTexture();
    }

    void AsciEffect::SetSpeed( float a )
    {
        m_speed = a;
/*        Renderer::Get().SetCurrentProgram(m_program.GetShaderProgram());
        m_program.SetParameter("u_speed",a);*/
    }

}
