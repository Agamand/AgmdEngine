/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/Fast2DSurface.h>
#include <Core/Driver.h>
#include <Core/Shader/ShaderProgram.h>

SINGLETON_IMPL(Agmd::Fast2DSurface);
namespace Agmd
{
    Fast2DSurface::Fast2DSurface()
    {
        Init();
    }

    Fast2DSurface::~Fast2DSurface()
    {}


    void Fast2DSurface::Init()
    {
        TVertex _vertex[] =
        {
            {vec3(0,0,0.1),vec2(0,0)},
            {vec3(1,0,0.1),vec2(1,0)},
            {vec3(0,1,0.1),vec2(0,1)},
            {vec3(1,1,0.1),vec2(1,1)}
        };
        short _index[] = 
        {
            0,1,3,
            0,3,2
        };

        Driver& render =  Driver::Get();

        TDeclarationElement Elements[] =
        {
            {0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_TEXCOORD0,    ELT_TYPE_FLOAT2}
        };

        m_VertexBuffer = render.CreateVertexBuffer<TVertex>(sizeof(_vertex),0, _vertex);
        m_IndexBuffer = render.CreateIndexBuffer<short>(sizeof(_index), 0, _index);
        m_Declaration  = render.CreateVertexDeclaration(Elements);
    }

    void Fast2DSurface::Draw()
    {
        Driver& render = Driver::Get();
        render.GetCurrentProgram()->SetParameter("u_matProjection",ortho<float>(0,1,0,1));
        render.SetDeclaration(m_Declaration);
        render.SetIndexBuffer(m_IndexBuffer);
        render.SetVertexBuffer(0, m_VertexBuffer);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 0, m_IndexBuffer.GetCount());
    }
}
