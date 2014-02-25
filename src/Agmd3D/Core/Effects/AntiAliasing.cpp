/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Effects/AntiAliasing.h>
#include <Core/Texture/Texture.h>
#include <Core/Renderer.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{

    AntiAliasing::AntiAliasing() : iteration(1)
    {
        m_program.LoadFromFile("Shader/Effect/fxaa.glsl");
    }

    void AntiAliasing::Init()
    {}

    void AntiAliasing::Update(a_uint64 /*t_diff*/)
    {}

    void AntiAliasing::ApplyFxaa(Texture& input, Texture& output)
    {
        Renderer::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Renderer::Get().SetTexture(0,input.GetTexture());
        Texture::BeginRenderToTexture(output);
        Fast2DSurface::Instance().Draw();
        Texture::EndRenderToTexture();
        Renderer::Get().SetCurrentProgram(NULL);
    }

    void AntiAliasing::ApplyEffect(Texture& input, Texture& output)
    {
        
        for(auto i = 0; i < iteration; i++)
           !i%2 ? ApplyFxaa(input,output) : ApplyFxaa(output,input);
        
        if(!iteration%2)
            std::swap(input,output);
    }
    

}
