/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _RENDERER_H_
#define _RENDERER_H_

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
#include <Transform.h>
#include <string>
#include <map>
#include <vector>
#include <windows.h>


namespace Agmd
{
    class AGMD3D_EXPORT Driver
    {
    public :
        virtual ~Driver();
        static void Change(Driver* newRenderer);

        static void Destroy();

        static Driver& Get();

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

        virtual a_uint32 ConvertColor(const Color& color) const = 0;

        virtual void SetTexture(unsigned int unit, const TextureBase* texture, TTextureType type = TEXTURE_2D) = 0;

        virtual TextureBase* CreateTexture(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags = 0) const = 0;

        virtual TextureBase* CreateTexture2D(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const = 0;

        virtual TextureBase* CreateTextureCube(const ivec2& size, TPixelFormat format, unsigned long flags = 0) const = 0;

        virtual void SetupAlphaBlending(TBlend src, TBlend dest) const = 0;

        virtual void SetupDepthTest(TDepth mode) = 0;

        virtual void SetupTextureUnit(unsigned int unit, TTextureOp op, TTextureArg arg1, TTextureArg arg2 = TXA_DIFFUSE, const Color& constant = 0x00) const = 0;

        virtual void _DEPRECATED_(Enable)(TRenderParameter param, bool value) = 0;

        virtual BaseShader* CreateShader(std::string source, TShaderType type) const = 0;

        virtual BaseShaderProgram* CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const = 0;

        virtual FrameBuffer* CreateFrameBuffer() const = 0;
        
        virtual RenderBuffer* CreateRenderBuffer(const ivec2& size, TPixelFormat format) const = 0;

        virtual void SetRenderMode(TRenderMode mode) = 0;

        virtual const BaseShaderProgram* GetCurrentProgram() = 0;

        virtual void SetCurrentProgram(const BaseShaderProgram* prog) = 0;

        void SetCurrentTransform(const Transform* transform);

        virtual void SetViewPort(const ivec2& xy, const ivec2& size) = 0;

        virtual void SetCullFace(int face) = 0;

    public :

        template <class T> Buffer<T> CreateVertexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> Buffer<T> CreateIndexBuffer(unsigned long size, unsigned long flags, const T* data = NULL) const;

        template <class T> Buffer<T> CreateUniformBuffer(unsigned long size, unsigned long flags, int bindPoint, int ubflags = 0, const T* data = NULL) const;

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
		float GetAspectRatio();



        void SetCamera(Camera* cam);
        Camera* GetCamera();

        void SetTextureFlag(a_uint32 flag);
        void AddTextureFlag(a_uint32 flag);
        void RemoveTextureFlag(a_uint32 flag);
        a_uint32 GetTextureFlag();

        virtual void OnUpdate(a_uint64 t_diff);

        void SetMatView(mat4 _MatView);
        void SetMatProjection(mat4 _MatProjection);
        void SetScreen(ivec2 _screen);

		void SetActiveScene(SceneMgr* sc);
		SceneMgr* GetActiveScene();
        Statistics& GetStatistics();
    protected :

        virtual void Setup(HWND Hwnd) = 0;

        virtual void CheckCaps() = 0;

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual BaseBuffer* CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint, int ubflags) const = 0;

        virtual BaseBuffer* CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const = 0;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const = 0;

        std::map<TCapability, bool> m_Capabilities;

        a_uint32            m_TextureFlags;
        ivec2               m_Screen;
        const Transform*    m_CurrentTransform;

        SceneMgr*           m_ActiveScene;
        Camera*             m_Camera;
        Statistics*         m_stats;
    private :

        static Driver*    s_Instance;
    };
    #include "Renderer.inl"

}


#endif /* _RENDERER_H_ */