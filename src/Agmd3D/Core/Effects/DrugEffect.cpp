/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/DrugEffect.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{

    DrugEffect::DrugEffect() : m_time(0)
    {
        m_program.LoadFromFile("Shader/Effect/drug.glsl");
    }

    void DrugEffect::Init()
    {}

    void DrugEffect::Update(a_uint64 t_diff)
    {
		m_time+=t_diff/1000.0f;
	}

    void DrugEffect::ApplyEffect(Texture& input, Texture& output)
    {
        
		Texture::BeginRenderToTexture(output);
		Driver::Get().SetCurrentProgram(m_program.GetShaderProgram());
		Driver::Get().SetTexture(0,input.GetTexture());
		m_program.SetParameter("u_time",m_time);
		Fast2DSurface::Instance().Draw();
		Driver::Get().SetCurrentProgram(NULL);
		Texture::EndRenderToTexture();
    }
    

}
