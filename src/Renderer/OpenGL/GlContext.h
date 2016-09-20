/*


*/

#ifndef _GLCONTEXT_H_
#define _GLCONTEXT_H_

#include <gl/GL.h>
#include <gl/glext.h>
#include <gl/glew.h>
#include <gl/wglew.h>

#include <string>

using namespace std;

namespace Agmd
{
    #define LOAD_EXTENSION(Ext) LoadExtension(Ext, #Ext)
    enum GLContextState
    {
        DEPTH_ENABLE = 0x00000001,
        BLEND_ENABLE = 0x00000002,

    };

    /*
    OpenGL Wrapper class
    */

    class GLContext
    {
        static PFNWGLCREATECONTEXTATTRIBSARBPROC    wglCreateContextAttribsARB;
    public:
        static void InitOpenGl();
        template <class T> static void LoadExtension(T& Proc, const char* fn0ame);
        GLContext();
        GLContext(GLContext* sharecontext);
        void LoadFunction(const char* fname);
        void LoadAllFunction();
        void ShareData(GLContext* context);
        /*
        OpenGL Wrapper function
        */
        PFNGLGETSTRINGIPROC                      glGetStringi;
        PFNGLBINDBUFFERPROC                      glBindBuffer;
        PFNGLDELETEBUFFERSPROC                   glDeleteBuffers;
        PFNGLGENBUFFERSPROC                      glGenBuffers;
        PFNGLBUFFERDATAPROC                      glBufferData;
        PFNGLBUFFERSUBDATAPROC                   glBufferSubData;
        PFNGLGETBUFFERSUBDATAPROC                glGetBufferSubData;
        PFNGLMAPBUFFERPROC                       glMapBuffer;
        PFNGLMAPBUFFERRANGEPROC                  glMapBufferRange;
        PFNGLUNMAPBUFFERPROC                     glUnmapBuffer;
        PFNGLDELETESYNCPROC                      glDeleteSync;
        PFNGLGETSYNCIVPROC                       glGetSynciv;
        PFNGLWAITSYNCPROC                        glWaitSync;
        PFNGLCLIENTWAITSYNCPROC                  glClientWaitSync;
        PFNGLFENCESYNCPROC                       glFenceSync;
        PFNGLACTIVETEXTUREPROC                   glActiveTexture;
        PFNGLCLIENTACTIVETEXTUREPROC             glClientActiveTexture;
        PFNGLCOMPRESSEDTEXIMAGE2DPROC            glCompressedTexImage2D;
        PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC         glCompressedTexSubImage2D;
        PFNGLPATCHPARAMETERIPROC                 glPatchParameteri;
        PFNGLGENPROGRAMPIPELINESPROC             glGenProgramPipelines;
        PFNGLBINDPROGRAMPIPELINEPROC             glBindProgramPipelines;
        PFNGLCREATEPROGRAMPROC                   glCreateProgram;
        PFNGLDELETEPROGRAMPROC                   glDeleteProgram;
        PFNGLCREATESHADERPROC                    glCreateShader;
        PFNGLDELETESHADERPROC                    glDeleteShader;
        PFNGLSHADERSOURCEPROC                    glShaderSource;
        PFNGLCOMPILESHADERPROC                   glCompileShader;
        PFNGLGETSHADERIVPROC                     glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC                glGetShaderInfoLog;
        PFNGLATTACHSHADERPROC                    glAttachShader;
        PFNGLLINKPROGRAMPROC                     glLinkProgram;
        PFNGLGETPROGRAMIVPROC                    glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC               glGetProgramInfoLog;
        PFNGLGETACTIVEUNIFORMSIVPROC             glGetActiveUniformsiv;
        PFNGLGETACTIVEUNIFORMNAMEPROC            glGetActiveUniformName;
        PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC       glGetActiveUniformBlockName;
        PFNGLGETACTIVEUNIFORMBLOCKIVPROC         glGetActiveUniformBlockiv;
        PFNGLGETINTEGERI_VPROC                   glGetIntegeri_v;
        PFNGLGETACTIVEUNIFORMPROC                glGetActiveUniform;
        PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;
        PFNGLGETACTIVEATTRIBPROC                 glGetActiveAttrib;
        PFNGLGETATTRIBLOCATIONPROC               glGetAttribLocation;
        PFNGLGETACTIVEUNIFORMBLOCKIVPROC         glGetActiveUniformBlock;
        PFNGLGETUNIFORMBLOCKINDEXPROC            glGetUniformBlockIndex;
        PFNGLUNIFORMBLOCKBINDINGPROC             glUniformBlockBinding;
        PFNGLBINDBUFFERBASEPROC                  glBindBufferBase;
        PFNGLUSEPROGRAMPROC                      glUseProgram;
        PFNGLUNIFORM1IPROC                       glUniform1i;
        PFNGLUNIFORM2IPROC                       glUniform2i;
        PFNGLUNIFORM3IPROC                       glUniform3i;
        PFNGLUNIFORM4IPROC                       glUniform4i;
        PFNGLUNIFORM1FPROC                       glUniform1f;
        PFNGLUNIFORM2FPROC                       glUniform2f;
        PFNGLUNIFORM3FPROC                       glUniform3f;
        PFNGLUNIFORM4FPROC                       glUniform4f;
        PFNGLUNIFORM1FVPROC                      glUniform1fv;
        PFNGLUNIFORM2FVPROC                      glUniform2fv;
        PFNGLUNIFORM3FVPROC                      glUniform3fv;
        PFNGLUNIFORM4FVPROC                      glUniform4fv;
        PFNGLUNIFORMMATRIX2FVPROC                glUniformMatrix2fv;
        PFNGLUNIFORMMATRIX3FVPROC                glUniformMatrix3fv;
        PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;
        PFNGLVERTEXATTRIB1FNVPROC                glVertexAttrib1f;
        PFNGLVERTEXATTRIB2FNVPROC                glVertexAttrib2f;
        PFNGLVERTEXATTRIB3FNVPROC                glVertexAttrib3f;
        PFNGLVERTEXATTRIB4FNVPROC                glVertexAttrib4f;
        PFNGLVERTEXATTRIBPOINTERPROC             glVertexAttribPointer;
        PFNGLENABLEVERTEXATTRIBARRAYPROC         glEnableVertexAttribArray;
        PFNGLBINDATTRIBLOCATIONPROC              glBindAttribLocation;
        PFNGLGENRENDERBUFFERSPROC                glGenRenderbuffers;
        PFNGLDELETERENDERBUFFERSPROC             glDeleteRenderbuffers;
        PFNGLBINDRENDERBUFFERPROC                glBindRenderbuffer;
        PFNGLRENDERBUFFERSTORAGEPROC             glRenderbufferStorage;
        PFNGLGENFRAMEBUFFERSPROC                 glGenFramebuffers;
        PFNGLBINDFRAMEBUFFERPROC                 glBindFramebuffer;
        PFNGLDRAWBUFFERSPROC                     glDrawBuffers;
        PFNGLFRAMEBUFFERRENDERBUFFERPROC         glFramebufferRenderbuffer;
        PFNGLFRAMEBUFFERTEXTUREPROC              glFramebufferTexture;
        PFNGLFRAMEBUFFERTEXTURE2DPROC            glFramebufferTexture2D;
        PFNGLFRAMEBUFFERTEXTURE3DPROC            glFramebufferTexture3D;
        PFNGLCHECKFRAMEBUFFERSTATUSPROC          glCheckFramebufferStatus;
        PFNGLDELETEFRAMEBUFFERSPROC              glDeleteFramebuffers;
    };
    #include <Renderer/OpenGL/GlContext.inl>
}
#endif /* _GLCONTEXT_H_ */
