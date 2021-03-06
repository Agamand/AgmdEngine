/*
============================================================================
DXRender - DirectX Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DxDriver.h>
#include <Renderer/DirectX/DxTexture2D.h>
//#include <Renderer/DirectX/DxTextureCube.h>

#include <Renderer/DirectX/DxBuffer.h>
#include <Renderer/DirectX/DxShader.h>
#include <Renderer/DirectX/DxShaderProgram.h>
#include <Renderer/DirectX/DxEnums.h>
//#include <Renderer/DirectX/DxFrameBuffer.h>
//#include <Renderer/DirectX/DxRenderBuffer.h>
//#include <Renderer/DirectX/DxConstantBuffer.h>
//#include <Renderer/DirectX/DxTextureBuffer.h>
#include <Core/MatStack.h>
#include <core/Tools/Statistics.h>
#include <Utilities/Color.h>
#include <Utilities/PixelUtils.h>
#include <Utilities/StringUtils.h>
#include <Debug/Logger.h>
#include <Matrix4.h>
#include <Debug/New.h>

#include <D3Dcompiler.h>

#include <assert.h>


SINGLETON_IMPL(Agmd::DXDriver)

using namespace AgmdUtilities;

namespace Agmd
{
    extern "C" DIRECTX_EXPORT void LoadPlugin()
    {
        Driver::Change(&DXDriver::Instance());
    }


    extern "C" DIRECTX_EXPORT void UnloadPlugin()
    {
        Driver::Destroy();
    }

    template <class T>
    inline void LoadExtension(T& proc, const char* name)
    {
        proc = NULL;
    }

#define LOAD_EXTENSION(Ext) LoadExtension(Ext, #Ext)

#define BUFFER_OFFSET(n) ((byte*)NULL + (n))


    const char* shader_dummies = "struct VOut"
    "{"
    "    float4 position : SV_POSITION;"
    "    float4 color : COLOR;"
    "};"
    "VOut VShader(float4 position : POSITION, float4 color : COLOR)"
    "{"
    "    VOut output;"
    "    output.position = position;"
    "    output.color = color;"
    "    return output;"
    "}"
    "float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET"
    "{"
    "    return color;"
    "}";
    ID3D10Blob* VSdummies; // for creating VERTEX BUFFER :/
    DXDriver::DXDriver() :
        m_Hwnd(NULL),
        m_Handle(NULL),
        m_Context(NULL),
        m_currentDeclaration(NULL),
        m_Extensions(""),
        m_CurrentProgram(NULL),
        m_last_unit(TEXTURE_UNIT_0)
    {
        std::memset(m_TextureBind,NULL, sizeof(void*) * MAX_TEXTUREUNIT);
    }

    DXDriver::~DXDriver()
    {
        swapchain->Release();
        m_device->Release();
        m_deviceContext->Release();
        m_defaultRasterizerState->Release();
        m_depthStencilState->Release();
        if (m_Hwnd && m_Handle)
        {
            ReleaseDC(m_Hwnd, m_Handle);
        }
        Logger::Destroy();
    }

    std::string DXDriver::GetRendererDesc() const
    {
        const char* dx_version = "Dx11";
        const char* hlsl_version = "";
        std::string _const = GetConstant();
        if (!dx_version)
            dx_version = "DX version not found";
        if (!hlsl_version)
            hlsl_version = "HLSL version not found";
        return StringBuilder("DirectX ")(dx_version)(", HLSL ")(hlsl_version)("\n")(_const);
    }

    void DXDriver::Setup(HWND Hwnd)
    {
        Logger::Instance().SetFilename("DirectX");

        // create a struct to hold information about the swap chain
        DXGI_SWAP_CHAIN_DESC scd;

        // clear out the struct for use
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

        // fill the swap chain description struct
        scd.BufferCount = 1; // one back buffer
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how swap chain is to be used
        scd.OutputWindow = Hwnd; // the window to be used
        scd.SampleDesc.Count = 4; // how many multisamples
        scd.Windowed = TRUE; // windowed/full-screen mode
        //scd.Flags = D3D11_CREATE_DEVICE_DEBUG;

        // create a device, device context and swap chain using the information in the scd struct
        D3D11CreateDeviceAndSwapChain(NULL,
                                          D3D_DRIVER_TYPE_HARDWARE,
                                          NULL,
                                          NULL,//D3D11_CREATE_DEVICE_DEBUG,
                                          NULL,
                                          NULL,
                                          D3D11_SDK_VERSION,
                                          &scd,
                                          &swapchain,
                                          &m_device,
                                          NULL,
                                          &m_deviceContext);


        ID3D11Texture2D* pBackBuffer;
        swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        // use the back buffer address to create the render target
        m_device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
        pBackBuffer->Release();


        // set the render target as the back buffer
        // Create depth stencil texture
        ID3D11Texture2D* pDepthStencil;
        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = 1920;
        descDepth.Height = 1080;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 4;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;

        m_device->CreateTexture2D(&descDepth, NULL, &pDepthStencil);

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));

        descDSV.Format = descDepth.Format;
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        descDSV.Texture2D.MipSlice = 0;;
        //descDSV.Texture2DMS.UnusedField_NothingToDefine = 0;  

        m_device->CreateDepthStencilView(pDepthStencil, &descDSV, &depthStencilView);

        // set the render target as the back buffer
        m_deviceContext->OMSetRenderTargets(1, &backbuffer, depthStencilView);


        //create default state
        D3D11_RASTERIZER_DESC wfdesc;
        ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
        wfdesc.FillMode = D3D11_FILL_SOLID;
        wfdesc.CullMode = D3D11_CULL_BACK;
        wfdesc.DepthClipEnable = TRUE;

        m_device->CreateRasterizerState(&wfdesc, &m_defaultRasterizerState);
        m_deviceContext->RSSetState(m_defaultRasterizerState);


        m_depthStencilState;

        D3D11_DEPTH_STENCIL_DESC dsdesc;
        ZeroMemory(&dsdesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

        dsdesc.DepthEnable = TRUE;
        dsdesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsdesc.DepthFunc = D3D11_COMPARISON_LESS;

        m_device->CreateDepthStencilState(&dsdesc, &m_depthStencilState);

        m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);


        //D3DX11CompileFromFile("shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VSdummies, 0, 0);
        ID3DBlob* errorMsg = NULL;
        HRESULT r = D3DCompile(shader_dummies, strlen(shader_dummies),NULL,NULL,NULL, "VShader", "vs_4_0",
                               0, 0, &VSdummies, &errorMsg);


        LoadExtensions();
        m_ModelMatrix = CreateUniformBuffer<mat4>(1, BUF_DYNAMIC, 0, 1,NULL);
        m_ModelMatrix.Bind(1);
    }

    void DXDriver::CheckCaps()
    {
        m_Capabilities[CAP_HW_MIPMAPPING] = CheckExtension("GL_SGIS_generate_mipmap");

        m_Capabilities[CAP_DXT_COMPRESSION] = CheckExtension("GL_ARB_texture_compression") &&
            CheckExtension("GL_EXT_texture_compression_s3tc");

        m_Capabilities[CAP_TEX_NON_POWER_2] = CheckExtension("GL_ARB_texture_non_power_of_two");

        m_Capabilities[CAP_TESSELATION_SHADER] = CheckExtension("GL_ARB_tessellation_shader");
    }

    bool DXDriver::CheckExtension(const std::string& Extension) const
    {
        return m_Extensions.find(Extension) != std::string::npos;
    }

    const std::string DXDriver::GetExtension() const
    {
        return m_Extensions;
    }

    const std::string DXDriver::GetConstant() const
    {
        StringBuilder str;
        a_int32 value;
        //         glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
        //        str("\nGL_MAX_VERTEX_ATTRIBS : ")(value);
        // 
        //         glGetIntegerv(GL_MAX_VARYING_FLOATS, &value);
        //         str("\nGL_MAX_VARYING_FLOATS : ")(value);
        // 
        // 
        //          glGetIntegerv(0x826E, &value);
        //          str("\nMax Uniform location :")(value);

        return str;
    }

    void DXDriver::LoadExtensions()
    {
    }

    void DXDriver::InitScene()
    {
        const float colors[] = {0.0f, 0.2f, 0.4f, 1.0f};
        m_deviceContext->ClearRenderTargetView(backbuffer, colors);
        m_deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void DXDriver::EndScene()
    {
        swapchain->Present(0, 0);
    }


    BaseBuffer* DXDriver::CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const
    {
        ID3D11Buffer* pVBuffer; // global

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DYNAMIC; // write access access by CPU and GPU
        bd.ByteWidth = size * stride; // size is the VERTEX struct * 3
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // use as a vertex buffer
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // allow CPU to write in buffer

        m_device->CreateBuffer(&bd, NULL, &pVBuffer); // create the buffer
        return new DXVertexBuffer(size, &pVBuffer);
    }

    BaseBuffer* DXDriver::CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const
    {
        ID3D11Buffer* pIBuffer; // global

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DYNAMIC; // write access access by CPU and GPU
        bd.ByteWidth = size * stride; // size is the VERTEX struct * 3
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER; // use as a vertex buffer
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // allow CPU to write in buffer

        m_device->CreateBuffer(&bd, NULL, &pIBuffer); // create the buffer
        return new DXIndexBuffer(size, &pIBuffer);
    }

    BaseBuffer* DXDriver::CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint, int ubflags) const
    {
        ID3D11Buffer* pVBuffer;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.ByteWidth = size * stride;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        m_device->CreateBuffer(&bd, NULL, &pVBuffer);
        return new DXConstantBuffer(size, &pVBuffer);
    }

    BaseBuffer* DXDriver::CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const
    {
        return NULL;
    }

    Declaration* DXDriver::CreateDeclaration(const TDeclarationElement* elts, std::size_t count) const
    {
        ID3D11InputLayout* pLayout;
        std::vector<D3D11_INPUT_ELEMENT_DESC> dxElements;
        std::vector<int> offset(count, 0);

        for (const TDeclarationElement* elt = elts; elt < elts + count; ++elt)
        {
            D3D11_INPUT_ELEMENT_DESC curElt;

            curElt.InputSlot = elt->stream;
            curElt.AlignedByteOffset = offset[elt->stream];
            curElt.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            curElt.InstanceDataStepRate = 0;
            switch (elt->dataType)
            {
            case ELT_TYPE_FLOAT1: curElt.Format = DXGI_FORMAT_R32_FLOAT;
                offset[elt->stream] += 4;
                break;
            case ELT_TYPE_FLOAT2: curElt.Format = DXGI_FORMAT_R32G32_FLOAT;
                offset[elt->stream] += 8;
                break;
            case ELT_TYPE_FLOAT3: curElt.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                offset[elt->stream] += 12;
                break;
            case ELT_TYPE_FLOAT4: curElt.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                offset[elt->stream] += 16;
                break;
            case ELT_TYPE_COLOR: curElt.Format = DXGI_FORMAT_R8G8B8A8_UINT;
                offset[elt->stream] += 4;
                break;
            }
            switch (elt->usage)
            {
            case ELT_USAGE_POSITION: curElt.SemanticName = "POSITION";
                curElt.SemanticIndex = 0;
                break;
            case ELT_USAGE_NORMAL: curElt.SemanticName = "NORMAL";
                curElt.SemanticIndex = 0;
                break;
            case ELT_USAGE_DIFFUSE: curElt.SemanticName = "COLOR";
                curElt.SemanticIndex = 0;
                break;

                //             case ELT_USAGE_TEXCOORD0 : curElt.SemanticName = "TEXCOORD"; curElt.SemanticIndex = 0; break;
                //             case ELT_USAGE_TEXCOORD1 : curElt.SemanticName = "TEXCOORD"; curElt.SemanticIndex = 1; break;
                //             case ELT_USAGE_TEXCOORD2 : curElt.SemanticName = "TEXCOORD"; curElt.SemanticIndex = 2; break;
                //             case ELT_USAGE_TEXCOORD3 : curElt.SemanticName = "TEXCOORD"; curElt.SemanticIndex = 3; break;
            default: continue;
            }


            dxElements.push_back(curElt);
        }
        auto a = VSdummies->GetBufferPointer();
        auto b = VSdummies->GetBufferSize();
        D3D11_INPUT_ELEMENT_DESC ied[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        //HRESULT r = m_device->CreateInputLayout(ied,2,VSdummies->GetBufferPointer(),VSdummies->GetBufferSize(),&pLayout);
        HRESULT r = m_device->CreateInputLayout(&dxElements[0], dxElements.size(), VSdummies->GetBufferPointer(), VSdummies->GetBufferSize(), &pLayout);
        assert(pLayout != NULL);
        return new DXDeclaration(pLayout);
    }

    void DXDriver::SetVB(unsigned int stream, const BaseBuffer* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex)
    {
        const DXVertexBuffer* vbuffer = static_cast<const DXVertexBuffer*>(buffer);
        //a_uint32 offset = 0;
        a_uint32 _stride = stride;
        a_uint32 _offset = 0;
        auto dxbuffer = vbuffer->GetBuffer();
        m_deviceContext->IASetVertexBuffers(0, 1, &dxbuffer, &_stride, &_offset);
    }

    void DXDriver::SetIB(const BaseBuffer* buffer, unsigned long stride)
    {
        const DXIndexBuffer* vbuffer = static_cast<const DXIndexBuffer*>(buffer);
        //a_uint32 offset = 0;
        a_uint32 _stride = stride;
        a_uint32 _offset = 0;
        auto dxbuffer = vbuffer->GetBuffer();
        m_deviceContext->IASetIndexBuffer(dxbuffer, stride == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, _offset);
    }

    void DXDriver::SetDeclaration(const Declaration* declaration)
    {
        m_currentDeclaration = static_cast<const DXDeclaration*>(declaration);
        if (m_currentDeclaration)
            m_deviceContext->IASetInputLayout(m_currentDeclaration->GetDeclaration());
    }

    void DXDriver::DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count)
    {
        if (!m_CurrentProgram)
            return;
        mat4 modelMatrix = transpose(m_CurrentTransform ? m_CurrentTransform->modelMatrix() : mat4(1.0f));
        m_ModelMatrix.Fill(&modelMatrix, 1);
        //m_CurrentProgram->SetParameter(MAT_MODEL,m_CurrentTransform ? m_CurrentTransform->modelMatrix() : mat4(1.0f));
        //m_CurrentProgram->SetParameter("u_textureFlags",(int)m_TextureFlags);
        m_stats->IncrDrawCall();
        m_stats->IncrTriangleCount(count);
        m_deviceContext->IASetPrimitiveTopology(DXEnum::Get(type));
        m_deviceContext->Draw(count, firstVertex);
    }

    void DXDriver::DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count)
    {
        if (!m_CurrentProgram)
            return;

        mat4 modelMatrix = transpose(m_CurrentTransform ? m_CurrentTransform->modelMatrix() : mat4(1.0f));
        m_ModelMatrix.Fill(&modelMatrix, 1);
        //         m_CurrentProgram->SetParameter(MAT_MODEL,m_CurrentTransform ? m_CurrentTransform->modelMatrix() : mat4(1.0f));
        //         m_CurrentProgram->SetParameter("u_textureFlags",(int)m_TextureFlags);
        m_stats->IncrDrawCall();
        m_stats->IncrTriangleCount(count);
        m_stats->IncrVertexCount(count * 3);

        m_deviceContext->IASetPrimitiveTopology(DXEnum::Get(type));
        m_deviceContext->DrawIndexed(count, firstIndex, 0);
    }

    a_uint32 DXDriver::ConvertColor(const Color& color) const
    {
        return color.ToABGR();
    }

    void DXDriver::SetTexture(a_uint32 unit, const TextureBase* texture, TTextureType type)
    {
        if (unit > MAX_TEXTUREUNIT)
            return;

        // nope this fail :/
        //if(m_TextureBind[unit] == texture) 
        //return; // NO CHANGE? -> return!

        const DXTexture* oDXTexture = static_cast<const DXTexture*>(texture);

        if (m_last_unit != unit)
        {
            //glActiveTexture(GL_TEXTURE0+unit);
            m_last_unit = unit;
        }

        if (texture)
        {
            //glBindTexture(DXEnum::Get(oDXTexture->GetType()), oDXTexture->GetDXTexture());
        }
        else if (m_TextureBind[unit])
        {
            //glBindTexture(DXEnum::Get(m_TextureBind[unit]->GetType()), 0);
        }

        m_TextureBind[unit] = texture;
    }

    TextureBase* DXDriver::CreateTexture(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags) const
    {
        switch (type)
        {
        case TEXTURE_2D:
            return CreateTexture2D(size, format, flags);
        case TEXTURE_CUBE:
            return CreateTextureCube(size, format, flags);
        default:
            Logger::Log(LOGERROR, "Error on CreateTexture - unknown or unsupported TextureType : %d", (int)type);
            return NULL;
        }
    }

    TextureBase* DXDriver::CreateTexture2D(const ivec2& size, TPixelFormat format, unsigned long flags) const
    {
        ID3D11Texture2D* tex;
        D3D11_TEXTURE2D_DESC desc;
        desc.Width = size.x;
        desc.Height = size.y;
        desc.MipLevels = flags & TEX_NOMIPMAP ? 0 : GetNbMipLevels(size.x, size.y);
        desc.ArraySize = 1;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.Format = DXEnum::Get(format);
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        m_device->CreateTexture2D(&desc,NULL, &tex);
        return new DXTexture2D(size, format, desc.MipLevels > 0, false, tex);
    }

    TextureBase* DXDriver::CreateTextureCube(const ivec2& size, TPixelFormat format, unsigned long flags) const
    {
        return NULL;
    }

    void DXDriver::SetupAlphaBlending(TBlend src, TBlend dest) const
    {
    }

    void DXDriver::SetupDepthTest(TDepth mode)
    {
    }

    void DXDriver::SetupTextureUnit(a_uint32 unit, TTextureOp op, TTextureArg arg1, TTextureArg arg2, const Color& constant) const
    {
    }

    void DXDriver::Enable(TRenderParameter param, bool value)
    {
    }

    void DXDriver::SetRenderMode(TRenderMode mode)
    {
    }


    BaseShader* DXDriver::CreateShader(std::string source, TShaderType type) const
    {
        ID3DBlob* shaderBlob = NULL;
        ID3DBlob* errorMsg = NULL;


        static const char* shaderFunction[] = {
            "VShader",
            "",
            "",
            "",
            "PShader",
        };

        static const char* shaderVersion[] = {
            "vs_4_0",
            "",
            "",
            "",
            "ps_4_0",
        };


        HRESULT r = D3DCompile(source.c_str(), source.length(),NULL,NULL,NULL, shaderFunction[type], shaderVersion[type],
                               0, 0, &shaderBlob, &errorMsg);
        if (errorMsg)
        {
            char* msg = (char*)errorMsg->GetBufferPointer();
            return NULL;
        }
        void* shaderPtr;
        switch (type)
        {
        case Agmd::SHADER_VERTEX:
            m_device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),NULL, (ID3D11VertexShader**)&shaderPtr);

            return new DXVertexShader((ID3D11VertexShader*)shaderPtr);
            //         case Agmd::SHADER_TESS_CONTROL:
            //             break;
            //         case Agmd::SHADER_TESS_EVALUATION:
            //             break;
            //         case Agmd::SHADER_GEOMETRY:
            //             break;
        case Agmd::SHADER_PIXEL:
            m_device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),NULL, (ID3D11PixelShader**)&shaderPtr);
            return new DXPixelShader((ID3D11PixelShader*)shaderPtr);
        default:
            return NULL;
        }
    }

    BaseShaderProgram* DXDriver::CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const
    {
        return new DXShaderProgram(vertex, frag);
    }

    const BaseShaderProgram* DXDriver::GetCurrentProgram()
    {
        return m_CurrentProgram;
    }

    FrameBuffer* DXDriver::CreateFrameBuffer() const
    {
        return NULL;
    }

    RenderBuffer* DXDriver::CreateRenderBuffer(const ivec2& size, TPixelFormat format) const
    {
        return NULL;
    }

    void DXDriver::SetCurrentProgram(const BaseShaderProgram* prog)
    {
        m_CurrentProgram = prog;
        if (prog)
        {
            const DXShaderProgram* p = static_cast<const DXShaderProgram*>(prog);
            BaseShader* const* shaders = p->GetShaders();
            DXVertexShader* vertex = static_cast<DXVertexShader*>(shaders[0]);
            DXPixelShader* frag = static_cast<DXPixelShader*>(shaders[4]);
            if (vertex)
                m_deviceContext->VSSetShader(vertex->GetShader(), 0, 0);
            if (frag)
                m_deviceContext->PSSetShader(frag->GetShader(), 0, 0);
        }
        else
        {
            m_deviceContext->VSSetShader(NULL, 0, 0);
            m_deviceContext->PSSetShader(NULL, 0, 0);
        }
    }

    void DXDriver::SetViewPort(const ivec2& xy, const ivec2& size)
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = xy.x;
        viewport.TopLeftY = xy.y;
        viewport.Width = size.x;
        viewport.Height = size.y;
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1;
        m_deviceContext->RSSetViewports(1, &viewport);
    }

#define FRONT 1
#define BACK  2

    void DXDriver::SetCullFace(int face)
    {
    }

    void DXDriver::drawBoundingBox(const BoundingSphere& bbox, const BaseShaderProgram* program)
    {
    }

    void DXDriver::clear(a_uint32 flags)
    {
    }
}
