#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <Config\Fwd.h>
#include <Core/Renderer.h>
#include <Renderer\OpenGL\GlBuffer.h>
#include <Renderer\OpenGL\GlDeclaration.h>
#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlEnums.h>
#include <Core\Shader\ShaderProgram.h>
#include <Utilities/Singleton.h>
#include <vector>
#include <windows.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/wglew.h>


namespace Agmd
{
    class GLRenderer : public Renderer, public Singleton<GLRenderer>
    {
    MAKE_SINGLETON(GLRenderer)

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

        virtual uint32 ConvertColor(const Color& color) const;

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

        virtual void setClipPlane(uint32 clipUnit, double* plane);

        virtual void setRenderMode(TRenderMode mode);

        virtual const BaseShaderProgram* getPipeline();

        virtual void ReloadPipeline();

        virtual void SetCurrentProgram( const BaseShaderProgram* prog);

        virtual void SetViewPort(ivec2 xy, ivec2 size);

        virtual void SetCullFace(int face);

    public :

        static PFNGLGETSTRINGIPROC                    glGetStringi;
        static PFNGLBINDBUFFERPROC                    glBindBuffer;
        static PFNGLDELETEBUFFERSPROC                glDeleteBuffers;
        static PFNGLGENBUFFERSPROC                    glGenBuffers;
        static PFNGLBUFFERDATAPROC                    glBufferData;
        static PFNGLBUFFERSUBDATAPROC                glBufferSubData;
        static PFNGLGETBUFFERSUBDATAPROC            glGetBufferSubData;
        static PFNGLMAPBUFFERPROC                    glMapBuffer;
        static PFNGLUNMAPBUFFERPROC                    glUnmapBuffer;
        static PFNGLACTIVETEXTUREPROC                glActiveTexture;
        static PFNGLCLIENTACTIVETEXTUREPROC            glClientActiveTexture;
        static PFNGLCOMPRESSEDTEXIMAGE2DPROC        glCompressedTexImage2D;
        static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC        glCompressedTexSubImage2D;
        static PFNGLPATCHPARAMETERIPROC             glPatchParameteri;
        static PFNGLGENPROGRAMPIPELINESPROC            glGenProgramPipelines;
        static PFNGLBINDPROGRAMPIPELINEPROC            glBindProgramPipelines;
        static PFNGLCREATEPROGRAMPROC                glCreateProgram;
        static PFNGLDELETEPROGRAMPROC                glDeleteProgram;
        static PFNGLCREATESHADERPROC                glCreateShader;
        static PFNGLDELETESHADERPROC                glDeleteShader;
        static PFNGLSHADERSOURCEPROC                glShaderSource;
        static PFNGLCOMPILESHADERPROC                glCompileShader;
        static PFNGLGETSHADERIVPROC                 glGetShaderiv;
        static PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
        static PFNGLATTACHSHADERPROC                glAttachShader;
        static PFNGLLINKPROGRAMPROC                    glLinkProgram;
        static PFNGLGETPROGRAMIVPROC                glGetProgramiv;
        static PFNGLGETPROGRAMINFOLOGPROC            glGetProgramInfoLog;
        static PFNGLGETACTIVEUNIFORMSIVPROC            glGetActiveUniformsiv;
        static PFNGLGETACTIVEUNIFORMNAMEPROC        glGetActiveUniformName;
        static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC    glGetActiveUniformBlockName;
        static PFNGLGETACTIVEUNIFORMBLOCKIVPROC        glGetActiveUniformBlockiv;
        static PFNGLGETINTEGERI_VPROC               glGetIntegeri_v;
        static PFNGLGETACTIVEUNIFORMPROC            glGetActiveUniform;
        static PFNGLGETUNIFORMLOCATIONPROC            glGetUniformLocation;
        static PFNGLGETACTIVEATTRIBPROC             glGetActiveAttrib;
        static PFNGLGETATTRIBLOCATIONPROC           glGetAttribLocation;
        static PFNGLGETACTIVEUNIFORMBLOCKIVPROC     glGetActiveUniformBlock;
        static PFNGLGETUNIFORMBLOCKINDEXPROC        glGetUniformBlockIndex;
        static PFNGLUNIFORMBLOCKBINDINGPROC            glUniformBlockBinding;
        static PFNGLBINDBUFFERBASEPROC              glBindBufferBase;
        static PFNGLUSEPROGRAMPROC                    glUseProgram;
        static PFNGLUNIFORM1IPROC                    glUniform1i;
        static PFNGLUNIFORM2IPROC                    glUniform2i;
        static PFNGLUNIFORM3IPROC                    glUniform3i;
        static PFNGLUNIFORM4IPROC                    glUniform4i;
        static PFNGLUNIFORM1FPROC                    glUniform1f;
        static PFNGLUNIFORM2FPROC                    glUniform2f;
        static PFNGLUNIFORM3FPROC                    glUniform3f;
        static PFNGLUNIFORM4FPROC                    glUniform4f;
        static PFNGLUNIFORM1FVPROC                    glUniform1fv;
        static PFNGLUNIFORM2FVPROC                    glUniform2fv;
        static PFNGLUNIFORM3FVPROC                    glUniform3fv;
        static PFNGLUNIFORM4FVPROC                    glUniform4fv;
        static PFNGLUNIFORMMATRIX2FVPROC            glUniformMatrix2fv;
        static PFNGLUNIFORMMATRIX3FVPROC            glUniformMatrix3fv;
        static PFNGLUNIFORMMATRIX4FVPROC            glUniformMatrix4fv;
        static PFNGLVERTEXATTRIB1FNVPROC            glVertexAttrib1f;
        static PFNGLVERTEXATTRIB2FNVPROC            glVertexAttrib2f;
        static PFNGLVERTEXATTRIB3FNVPROC            glVertexAttrib3f;
        static PFNGLVERTEXATTRIB4FNVPROC            glVertexAttrib4f;
        static PFNGLVERTEXATTRIBPOINTERPROC         glVertexAttribPointer;
        static PFNGLENABLEVERTEXATTRIBARRAYPROC     glEnableVertexAttribArray;
        static PFNGLBINDATTRIBLOCATIONPROC          glBindAttribLocation;
        static PFNGLGENRENDERBUFFERSPROC            glGenRenderbuffers;
        static PFNGLDELETERENDERBUFFERSPROC         glDeleteRenderbuffers;
        static PFNGLBINDRENDERBUFFERPROC            glBindRenderbuffer;
        static PFNGLRENDERBUFFERSTORAGEPROC         glRenderbufferStorage;
        static PFNGLGENFRAMEBUFFERSPROC             glGenFramebuffers;
        static PFNGLBINDFRAMEBUFFERPROC             glBindFramebuffer;
        static PFNGLDRAWBUFFERSPROC                 glDrawBuffers;
        static PFNGLFRAMEBUFFERRENDERBUFFERPROC     glFramebufferRenderbuffer;
        static PFNGLFRAMEBUFFERTEXTUREPROC          glFramebufferTexture;
        static PFNGLFRAMEBUFFERTEXTURE2DPROC        glFramebufferTexture2D;
        static PFNGLFRAMEBUFFERTEXTURE3DPROC        glFramebufferTexture3D;
        static PFNGLCHECKFRAMEBUFFERSTATUSPROC      glCheckFramebufferStatus;
        static PFNGLDELETEFRAMEBUFFERSPROC          glDeleteFramebuffers;
        
        //CONTEXT

        static PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribsARB;
        static PFNWGLSWAPINTERVALEXTPROC            wglSwapIntervalEXT;


        static char VertexPipeline[];
        static char FragmentPipeline[];

        virtual void DrawSomething();

        virtual void DebugCubeMap(const TextureBase* tex);



    protected :

        virtual void _LoadMatrix(TMatrixType type, const glm::mat2& matrix)
        {
            if(m_CurrentProgram)
                m_CurrentProgram->SetParameter(RGLEnum::GetName(type),matrix);
            else
                m_Pipeline.SetParameter(RGLEnum::GetName(type),matrix);
        }

        virtual void _LoadMatrix(TMatrixType type, const glm::mat3& matrix)
        {
            if(m_CurrentProgram)
                m_CurrentProgram->SetParameter(RGLEnum::GetName(type),matrix);
            else
                m_Pipeline.SetParameter(RGLEnum::GetName(type),matrix);
        }

        virtual void _LoadMatrix(TMatrixType type, const glm::mat4& matrix)
        {
            if(m_CurrentProgram)
                m_CurrentProgram->SetParameter(type,matrix);
            else
                m_Pipeline.SetParameter(type,matrix);
        }

        void updateGlobalBuffer()
        {
            if(!m_needUpdate)
                return;
            
            m_needUpdate = false;
        }

        virtual void Setup(HWND Hwnd);

        virtual void CheckCaps();

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint) const;

        virtual BaseBuffer* CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const;

    private :

        GLRenderer();
        ~GLRenderer();

        bool CheckExtension(const std::string& Extension) const;
        void LoadExtensions();

        HWND                        m_Hwnd;
        HDC                            m_Handle;
        HGLRC                        m_Context;
        const GLDeclaration*        m_CurrentDeclaration;
        unsigned long                m_IndexStride;
        std::string                    m_Extensions;
        ShaderProgram                m_Pipeline;
        ShaderProgram                m_DebugPipeline[4];
        const BaseShaderProgram*    m_CurrentProgram;
        const TextureBase*            m_TextureBind[MAX_TEXTUREUNIT];
        bool                        m_Reload;
        uint32                      last_unit;

    };

}
#endif //GLRENDERER_H