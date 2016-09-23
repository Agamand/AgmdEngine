/*
============================================================================
DXRender - DirectX Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXDRIVER_H_
#define _DXDRIVER_H_

#include <Config\Fwd.h>
#include <Renderer/DirectX/Config.h>
#include <Core/Driver.h>

#include <Renderer\DirectX\DxDeclaration.h>
//#include <Renderer\DirectX\DxShaderProgram.h>
#include <Renderer\DirectX\DxEnums.h>
#include <Core\Shader\ShaderProgram.h>
#include <Utilities/Singleton.h>
#include <Container/Vector.h>
#include <windows.h>
#include <windowsx.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3dtypes.h>


#pragma comment (lib, "x86/d3d11.lib")


namespace Agmd
{

    class DXDriver : public Driver, public Singleton<DXDriver>
    {
    MAKE_SINGLETON(DXDriver)

    public :

        virtual std::string GetRendererDesc() const;

        virtual const std::string GetExtension() const;

        virtual const std::string GetConstant() const;

        virtual void InitScene();

        virtual void EndScene();

        virtual void SetVB(unsigned int stream, const BaseBuffer* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex);

        virtual void SetIB(const BaseBuffer* buffer, unsigned long stride);

        virtual void SetDeclaration(const Declaration* declaration);

        virtual void DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count);

        virtual void DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count);

        virtual a_uint32 ConvertColor(const Color& color) const;

        virtual void SetTexture(unsigned int Unit, const TextureBase* texture, TTextureType type);

        virtual TextureBase* CreateTexture(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags = 0) const;

        virtual TextureBase* CreateTexture2D(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const;

        virtual TextureBase* CreateTextureCube(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const;

        virtual void SetupAlphaBlending(TBlend src, TBlend dest) const;

        virtual void SetupDepthTest(TDepth mode);

        virtual void SetupTextureUnit(unsigned int Unit, TTextureOp Op, TTextureArg Arg1, TTextureArg Arg2 = TXA_DIFFUSE, const Color& constant = 0x00) const;

        virtual void Enable(TRenderParameter Param, bool Value);

        virtual BaseShader* CreateShader(std::string source, TShaderType type) const;

        virtual BaseShaderProgram* CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const;

        virtual FrameBuffer* CreateFrameBuffer() const;
        
        virtual RenderBuffer* CreateRenderBuffer(const ivec2& size, TPixelFormat format) const;

        virtual void SetRenderMode(TRenderMode mode);

        virtual const BaseShaderProgram* GetCurrentProgram();

        virtual void SetCurrentProgram( const BaseShaderProgram* prog);

        virtual void SetViewPort(const ivec2& xy,const ivec2& size);

        virtual void SetCullFace(int face);


        /* debug function */
        virtual void drawBoundingBox(const BoundingSphere& bbox,const BaseShaderProgram* program);
        virtual void clear( a_uint32 clear );


        /* Dx context getter*/

        ID3D11Device * Device() const { return m_device; }
        ID3D11DeviceContext * DeviceContext() const { return m_deviceContext; }

    protected :

        virtual void Setup(HWND Hwnd);

        virtual void CheckCaps();

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint, int ubflags) const;

        virtual BaseBuffer* CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count, BaseBuffer* buffer, a_uint32 stride) const;

    private :

        DXDriver();
        ~DXDriver();

        bool CheckExtension(const std::string& Extension) const;
        void LoadExtensions();

        HWND                        m_Hwnd;
        HDC                         m_Handle;
        HGLRC                       m_Context;
        const DXDeclaration*        m_currentDeclaration;
        unsigned long               m_IndexStride;
        std::string                 m_Extensions;
        ShaderProgram               m_DebugPipeline[4];
        const BaseShaderProgram*    m_CurrentProgram;
        const TextureBase*          m_TextureBind[MAX_TEXTUREUNIT];
        a_uint32                    m_last_unit; // last used texture unit
        
        //Dx11 Variables

        ID3D11Device                *m_device;
        ID3D11DeviceContext         *m_deviceContext;
        IDXGISwapChain              *swapchain;
        ID3D11RenderTargetView      *backbuffer;
		ID3D11DepthStencilView		*depthStencilView;
		Buffer<mat4>				m_ModelMatrix;
		ID3D11RasterizerState* m_defaultRasterizerState;
		ID3D11DepthStencilState* m_depthStencilState;
	};

}
#endif /* _DXDRIVER_H_ */