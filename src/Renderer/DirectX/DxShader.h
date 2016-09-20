/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXSHADER_H_
#define _DXSHADER_H_

#include <CommonDefines.h>
#include <Core/Shader/BaseShader.h>

#include <dxgi.h>
#include <d3d11.h>

#include <string>

namespace Agmd
{
    template <class ShaderClass, TShaderType type>
    class DXShader : public BaseShader
    {
    public:
        DXShader(ShaderClass shaderid) : BaseShader(type), m_Shader(shaderid)
        {
        }

        virtual ~DXShader()
        {
            m_Shader->Release();
        }

        ShaderClass GetShader() { return m_Shader; }

    private:
        ShaderClass m_Shader;
    };


    typedef DXShader<ID3D11VertexShader*, SHADER_VERTEX> DXVertexShader;
    typedef DXShader<ID3D11PixelShader*, SHADER_PIXEL> DXPixelShader;
}

#endif /* _DXSHADER_H_ */
