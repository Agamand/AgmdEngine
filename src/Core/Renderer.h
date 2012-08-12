#ifndef RENDERER_H
#define RENDERER_H

#include <Utilities/Color.h>
#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/Buffer.h>
#include <Core/Enums.h>
#include <Core/Shader.h>
#include <Core/FrameBuffer.h>
#include <Core/RenderBuffer.h>
#include <Core/Declaration.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <Maths/Rectangle.h>
#include <string>
#include <map>
#include <vector>
#include <windows.h>


namespace Agmd
{
    class AGMD_EXPORT Renderer
    {
    public :

        virtual ~Renderer();
        static void Change(Renderer* newRenderer);

        static void Destroy();

        static Renderer& Get();

        virtual std::string GetRendererDesc() const = 0;

        virtual void InitScene() = 0;
        virtual void EndScene() = 0;

        virtual void SetVB(unsigned int stream, const BaseBuffer* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex) = 0;

        virtual void SetIB(const BaseBuffer* buffer, unsigned long stride) = 0;

        virtual void SetDeclaration(const Declaration* declaration) = 0;

        virtual void DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count) const = 0;

        virtual void DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count) const = 0;

        //virtual void PushMatrix(TMatrixType Type) = 0;

        //virtual void PopMatrix(TMatrixType Type) = 0;

        //virtual void LoadMatrixMult(TMatrixType Type, const glm::mat4& Matrix) = 0;

        //virtual void GetMatrix(TMatrixType Type, glm::mat4& Matrix) const = 0;

        virtual uint32 ConvertColor(const Color& color) const = 0;

        virtual void SetTexture(unsigned int unit, const TextureBase* texture) const = 0;

        virtual TextureBase* CreateTexture(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const = 0;

        virtual void SetupAlphaBlending(TBlend src, TBlend dest) const = 0;

        virtual void SetupTextureUnit(unsigned int unit, TTextureOp op, TTextureArg arg1, TTextureArg arg2 = TXA_DIFFUSE, const Color& constant = 0x00) const = 0;

        virtual void Enable(TRenderParameter param, bool value) = 0;

        virtual BaseShader* CreateShader(std::string source, TShaderType type) const = 0;

		virtual BaseShaderProgram* CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const = 0;

		virtual FrameBuffer* CreateFrameBuffer() const = 0;
		
		virtual RenderBuffer* CreateRenderBuffer(const ivec2& size, TPixelFormat format) const = 0;

        //virtual void SetVertexShader(const IShaderBase* Shader) = 0;

        //virtual void SetPixelShader(const IShaderBase* Shader) = 0;

		virtual void setRenderMode(TRenderMode mode) = 0;

		virtual ShaderProgram getPipeline() = 0;

		virtual void ReloadPipeline() = 0;

		virtual void SetCurrentProgram(BaseShaderProgram* prog) = 0;

    public :


		template <class T> void LoadMatrix(TMatrixType type, T& matrix);

        template <class T> Buffer<T> CreateVertexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> Buffer<T> CreateIndexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> void SetVertexBuffer(unsigned int stream, const Buffer<T>& buffer, unsigned long minVertex = 0, unsigned long maxVertex = 0);

        template <class T> void SetIndexBuffer(const Buffer<T>& buffer);

        template <std::size_t N> Declaration* CreateVertexDeclaration(const TDeclarationElement (&elt)[N]) const;

        bool HasCapability(TCapability Cap) const;

        std::string CapToString(TCapability Cap) const;

        void Initialize(HWND Hwnd);

        // CGprofile GetShaderProfile(TShaderType Type) const;

        //const char* const* GetShaderOptions(TShaderType Type) const;

		virtual void DrawSomething() = 0;




    protected :

		virtual void _LoadMatrix(TMatrixType type, const glm::mat2& matrix) = 0;

		virtual void _LoadMatrix(TMatrixType type, const glm::mat3& matrix) = 0;

		virtual void _LoadMatrix(TMatrixType type, const glm::mat4& matrix) = 0;

        virtual void Setup(HWND Hwnd) = 0;

        virtual void CheckCaps() = 0;

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const = 0;

        std::map<TCapability, bool> m_Capabilities;

        //CGprofile   m_VSProfile;
        //CGprofile   m_PSProfile;
        //const char* m_VSOptions[2];
        //const char* m_PSOptions[2];

    private :

        static Renderer* s_Instance;
    };
    #include "Renderer.inl"

}


#endif //RENDERER_H