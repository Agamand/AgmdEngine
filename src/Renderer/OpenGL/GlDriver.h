/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLRENDERER_H_
#define _GLRENDERER_H_

#include <Config\Fwd.h>
#include <Renderer/OpenGL/Config.h>
#include <Core/Driver.h>
#include <Renderer\OpenGL\GlBuffer.h>
#include <Renderer\OpenGL\GlDeclaration.h>
#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlEnums.h>
#include <Core\Shader\ShaderProgram.h>
#include <Utilities/Singleton.h>
#include <Container/Vector.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/wglew.h>


namespace Agmd
{

    class GLDriver : public Driver, public Singleton<GLDriver>
    {
    MAKE_SINGLETON(GLDriver)

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

    public :

        OPENGL_EXPORT static PFNGLGETSTRINGIPROC                      glGetStringi;
        OPENGL_EXPORT static PFNGLBINDBUFFERPROC                      glBindBuffer;
        OPENGL_EXPORT static PFNGLDELETEBUFFERSPROC                   glDeleteBuffers;
        OPENGL_EXPORT static PFNGLGENBUFFERSPROC                      glGenBuffers;
        OPENGL_EXPORT static PFNGLBUFFERDATAPROC                      glBufferData;
        OPENGL_EXPORT static PFNGLBUFFERSUBDATAPROC                   glBufferSubData;
        OPENGL_EXPORT static PFNGLGETBUFFERSUBDATAPROC                glGetBufferSubData;
        OPENGL_EXPORT static PFNGLMAPBUFFERPROC                       glMapBuffer;
        OPENGL_EXPORT static PFNGLMAPBUFFERRANGEPROC                  glMapBufferRange;
        OPENGL_EXPORT static PFNGLUNMAPBUFFERPROC                     glUnmapBuffer;
        OPENGL_EXPORT static PFNGLDELETESYNCPROC                      glDeleteSync;
        OPENGL_EXPORT static PFNGLGETSYNCIVPROC                       glGetSynciv;
        OPENGL_EXPORT static PFNGLWAITSYNCPROC                        glWaitSync;
        OPENGL_EXPORT static PFNGLCLIENTWAITSYNCPROC                  glClientWaitSync;
        OPENGL_EXPORT static PFNGLFENCESYNCPROC                       glFenceSync;
        OPENGL_EXPORT static PFNGLACTIVETEXTUREPROC                   glActiveTexture;
        OPENGL_EXPORT static PFNGLCLIENTACTIVETEXTUREPROC             glClientActiveTexture;
        OPENGL_EXPORT static PFNGLCOMPRESSEDTEXIMAGE2DPROC            glCompressedTexImage2D;
        OPENGL_EXPORT static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC         glCompressedTexSubImage2D;
        OPENGL_EXPORT static PFNGLPATCHPARAMETERIPROC                 glPatchParameteri;
        OPENGL_EXPORT static PFNGLGENPROGRAMPIPELINESPROC             glGenProgramPipelines;
        OPENGL_EXPORT static PFNGLBINDPROGRAMPIPELINEPROC             glBindProgramPipelines;
        OPENGL_EXPORT static PFNGLCREATEPROGRAMPROC                   glCreateProgram;
        OPENGL_EXPORT static PFNGLDELETEPROGRAMPROC                   glDeleteProgram;
        OPENGL_EXPORT static PFNGLCREATESHADERPROC                    glCreateShader;
        OPENGL_EXPORT static PFNGLDELETESHADERPROC                    glDeleteShader;
        OPENGL_EXPORT static PFNGLSHADERSOURCEPROC                    glShaderSource;
        OPENGL_EXPORT static PFNGLCOMPILESHADERPROC                   glCompileShader;
        OPENGL_EXPORT static PFNGLGETSHADERIVPROC                     glGetShaderiv;
        OPENGL_EXPORT static PFNGLGETSHADERINFOLOGPROC                glGetShaderInfoLog;
        OPENGL_EXPORT static PFNGLATTACHSHADERPROC                    glAttachShader;
        OPENGL_EXPORT static PFNGLLINKPROGRAMPROC                     glLinkProgram;
		OPENGL_EXPORT static PFNGLVALIDATEPROGRAMPROC				  glValidateProgram;
        OPENGL_EXPORT static PFNGLGETPROGRAMIVPROC                    glGetProgramiv;
        OPENGL_EXPORT static PFNGLGETPROGRAMINFOLOGPROC               glGetProgramInfoLog;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMSIVPROC             glGetActiveUniformsiv;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMNAMEPROC            glGetActiveUniformName;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC       glGetActiveUniformBlockName;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMBLOCKIVPROC         glGetActiveUniformBlockiv;
        OPENGL_EXPORT static PFNGLGETINTEGERI_VPROC                   glGetIntegeri_v;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMPROC                glGetActiveUniform;
        OPENGL_EXPORT static PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;
        OPENGL_EXPORT static PFNGLGETACTIVEATTRIBPROC                 glGetActiveAttrib;
        OPENGL_EXPORT static PFNGLGETATTRIBLOCATIONPROC               glGetAttribLocation;
        OPENGL_EXPORT static PFNGLGETACTIVEUNIFORMBLOCKIVPROC         glGetActiveUniformBlock;
        OPENGL_EXPORT static PFNGLGETUNIFORMBLOCKINDEXPROC            glGetUniformBlockIndex;
        OPENGL_EXPORT static PFNGLUNIFORMBLOCKBINDINGPROC             glUniformBlockBinding;
        OPENGL_EXPORT static PFNGLBINDBUFFERBASEPROC                  glBindBufferBase;
        OPENGL_EXPORT static PFNGLUSEPROGRAMPROC                      glUseProgram;
        OPENGL_EXPORT static PFNGLUNIFORM1IPROC                       glUniform1i;
        OPENGL_EXPORT static PFNGLUNIFORM2IPROC                       glUniform2i;
        OPENGL_EXPORT static PFNGLUNIFORM3IPROC                       glUniform3i;
        OPENGL_EXPORT static PFNGLUNIFORM4IPROC                       glUniform4i;
        OPENGL_EXPORT static PFNGLUNIFORM1FPROC                       glUniform1f;
        OPENGL_EXPORT static PFNGLUNIFORM2FPROC                       glUniform2f;
        OPENGL_EXPORT static PFNGLUNIFORM3FPROC                       glUniform3f;
        OPENGL_EXPORT static PFNGLUNIFORM4FPROC                       glUniform4f;
        OPENGL_EXPORT static PFNGLUNIFORM1FVPROC                      glUniform1fv;
        OPENGL_EXPORT static PFNGLUNIFORM2FVPROC                      glUniform2fv;
        OPENGL_EXPORT static PFNGLUNIFORM3FVPROC                      glUniform3fv;
        OPENGL_EXPORT static PFNGLUNIFORM4FVPROC                      glUniform4fv;
        OPENGL_EXPORT static PFNGLUNIFORMMATRIX2FVPROC                glUniformMatrix2fv;
        OPENGL_EXPORT static PFNGLUNIFORMMATRIX3FVPROC                glUniformMatrix3fv;
        OPENGL_EXPORT static PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;
        OPENGL_EXPORT static PFNGLVERTEXATTRIB1FNVPROC                glVertexAttrib1f;
        OPENGL_EXPORT static PFNGLVERTEXATTRIB2FNVPROC                glVertexAttrib2f;
        OPENGL_EXPORT static PFNGLVERTEXATTRIB3FNVPROC                glVertexAttrib3f;
        OPENGL_EXPORT static PFNGLVERTEXATTRIB4FNVPROC                glVertexAttrib4f;
        OPENGL_EXPORT static PFNGLVERTEXATTRIBPOINTERPROC             glVertexAttribPointer;
        OPENGL_EXPORT static PFNGLENABLEVERTEXATTRIBARRAYPROC         glEnableVertexAttribArray;
        OPENGL_EXPORT static PFNGLBINDATTRIBLOCATIONPROC              glBindAttribLocation;
        OPENGL_EXPORT static PFNGLGENRENDERBUFFERSPROC                glGenRenderbuffers;
        OPENGL_EXPORT static PFNGLDELETERENDERBUFFERSPROC             glDeleteRenderbuffers;
        OPENGL_EXPORT static PFNGLBINDRENDERBUFFERPROC                glBindRenderbuffer;
        OPENGL_EXPORT static PFNGLRENDERBUFFERSTORAGEPROC             glRenderbufferStorage;
        OPENGL_EXPORT static PFNGLGENFRAMEBUFFERSPROC                 glGenFramebuffers;
        OPENGL_EXPORT static PFNGLBINDFRAMEBUFFERPROC                 glBindFramebuffer;
        OPENGL_EXPORT static PFNGLDRAWBUFFERSPROC                     glDrawBuffers;
        OPENGL_EXPORT static PFNGLDRAWARRAYSEXTPROC                   glDrawArrays;
        OPENGL_EXPORT static PFNGLFRAMEBUFFERRENDERBUFFERPROC         glFramebufferRenderbuffer;
        OPENGL_EXPORT static PFNGLFRAMEBUFFERTEXTUREPROC              glFramebufferTexture;
        OPENGL_EXPORT static PFNGLFRAMEBUFFERTEXTURE2DPROC            glFramebufferTexture2D;
        static PFNGLFRAMEBUFFERTEXTURE3DPROC						  glFramebufferTexture3D;
        static PFNGLCHECKFRAMEBUFFERSTATUSPROC						  glCheckFramebufferStatus;
        static PFNGLDELETEFRAMEBUFFERSPROC							  glDeleteFramebuffers;
        
        //CONTEXT

        static PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribsARB;
        static PFNWGLSWAPINTERVALEXTPROC            wglSwapIntervalEXT;

    protected :

        virtual void Setup(HWND Hwnd);

        virtual void CheckCaps();

        virtual BaseBuffer* CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual BaseBuffer* CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint, int ubflags) const;

        virtual BaseBuffer* CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const;

        virtual Declaration* CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const;

    private :

        GLDriver();
        ~GLDriver();

        bool CheckExtension(const std::string& Extension) const;
        void LoadExtensions();

        HWND                        m_Hwnd;
        HDC                         m_Handle;
        HGLRC                       m_Context;
        const GLDeclaration*        m_CurrentDeclaration;
        unsigned long               m_IndexStride;
        std::string                 m_Extensions;
        ShaderProgram               m_DebugPipeline[4];
        const BaseShaderProgram*    m_CurrentProgram;
        const TextureBase*          m_TextureBind[MAX_TEXTUREUNIT];
        a_uint32                      last_unit; // last used texture unit

    };

}
#endif /* _GLRENDERER_H_ */