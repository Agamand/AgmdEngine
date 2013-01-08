#ifndef RENDERER_H
#define RENDERER_H

#include <Utilities/Color.h>
#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Enums.h>
#include <Core/Shader/Shader.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Declaration.h>
#include <Core/Camera/Camera.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Rectangle.h>
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

		virtual const std::string GetExtension() const = 0;

		virtual const std::string GetConstant() const = 0;

        virtual void InitScene() = 0;
        virtual void EndScene() = 0;

        virtual void SetVB(unsigned int stream, const BaseBuffer* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex) = 0;

        virtual void SetIB(const BaseBuffer* buffer, unsigned long stride) = 0;

        virtual void SetDeclaration(const Declaration* declaration) = 0;

        virtual void DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count) = 0;

        virtual void DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count) = 0;

        virtual uint32 ConvertColor(const Color& color) const = 0;

        virtual void SetTexture(unsigned int unit, const TextureBase* texture, TTextureType type = TEXTURE_2D) = 0;

		virtual TextureBase* CreateTexture(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags = 0) const = 0;

        virtual TextureBase* CreateTexture2D(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const = 0;

		virtual TextureBase* CreateTextureCube(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const = 0;

        virtual void SetupAlphaBlending(TBlend src, TBlend dest) const = 0;

        virtual void SetupDepthTest(TDepth mode) = 0;

        virtual void SetupTextureUnit(unsigned int unit, TTextureOp op, TTextureArg arg1, TTextureArg arg2 = TXA_DIFFUSE, const Color& constant = 0x00) const = 0;

        virtual void Enable(TRenderParameter param, bool value) = 0;

        virtual BaseShader* CreateShader(std::string source, TShaderType type) const = 0;

		virtual BaseShaderProgram* CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const = 0;

		virtual FrameBuffer* CreateFrameBuffer() const = 0;
		
		virtual RenderBuffer* CreateRenderBuffer(const ivec2& size, TPixelFormat format) const = 0;

		virtual void setClipPlane(uint32 clipUnit, double* plane) = 0;

		virtual void setRenderMode(TRenderMode mode) = 0;

		virtual const BaseShaderProgram* getPipeline() = 0;

		virtual void ReloadPipeline() = 0;

		virtual void SetCurrentProgram(const BaseShaderProgram* prog) = 0;

		virtual void SetViewPort(ivec2 xy, ivec2 size) = 0;
		
		virtual void DrawSomething() = 0;

		virtual void DebugCubeMap(const TextureBase* tex) = 0;

		virtual void SetCullFace(int face) = 0;

    public :


		template <class T> void LoadMatrix(TMatrixType type, T& matrix);

        template <class T> Buffer<T> CreateVertexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> Buffer<T> CreateIndexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> Buffer<T> CreateUniformBuffer(unsigned long size, unsigned long flags, int bindPoint, const T* data = NULL) const;

        template <class T> Buffer<T> CreateTextureBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> void SetVertexBuffer(unsigned int stream, const Buffer<T>& buffer, unsigned long minVertex = 0, unsigned long maxVertex = 0);

        template <class T> void SetIndexBuffer(const Buffer<T>& buffer);

        template <std::size_t N> Declaration* CreateVertexDeclaration(const TDeclarationElement (&elt)[N]) const;

        bool HasCapability(TCapability Cap) const;

        std::string CapToString(TCapability Cap) const;

        void Initialize(HWND Hwnd);

		mat4 GetMatView();
		mat4 GetMatProjection();
		ivec2 GetScreen();


		void SetCamera(Camera* cam);
		Camera* getCamera();

		void SetTextureFlag(uint32 flag);
		void AddTextureFlag(uint32 flag);
		void RemoveTextureFlag(uint32 flag);
		uint32 GetTextureFlag();

        virtual void OnUpdate(uint64 t_diff);



		void SetMatView(mat4 _MatView);
		void SetMatProjection(mat4 _MatProjection);
		void SetScreen(ivec2 _screen);

        void SetActiveScene(Scene* sc);
        Scene* GetActiveScene();

    protected :


		virtual void _LoadMatrix(TMatrixType type, const glm::mat2& matrix) = 0;

		virtual void _LoadMatrix(TMatrixType type, const glm::mat3& matrix) = 0;

		virtual void _LoadMatrix(TMatrixType type, const glm::mat4& matrix) = 0;

        virtual void Setup(HWND Hwnd) = 0;

        virtual void CheckCaps() = 0;

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

		virtual BaseBuffer* CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint) const = 0;

		virtual BaseBuffer* CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const = 0;

        std::map<TCapability, bool> m_Capabilities;

		uint32 m_TextureFlags;
		bool m_needUpdate;
		ivec2 m_Screen;

        Scene*  m_ActiveScene;
		Camera* m_Camera;
    private :

        static Renderer* s_Instance;
    };
    #include "Renderer.inl"

}


#endif //RENDERER_H