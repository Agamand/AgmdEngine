#include <Renderer/OpenGL/GlRenderer.h>
#include <Renderer/OpenGL/GlTexture2D.h>
#include <Renderer/OpenGL/GlTextureCube.h>
#include <Renderer/OpenGL/GlShader.h>
#include <Renderer/OpenGL/GlShaderProgram.h>
#include <Renderer/OpenGL/GlEnums.h>
#include <Renderer/OpenGL/GlFrameBuffer.h>
#include <Renderer/OpenGL/GlRenderBuffer.h>
#include <Renderer/OpenGL/GlUniformBuffer.h>
#include <Renderer/OpenGL/GlTextureBuffer.h>
#include <Core/MatStack.h>
#include <Utilities/Color.h>
#include <Utilities/PixelUtils.h>
#include <Debug/Logger.h>
#include <Matrix4.h>
#include <Debug/New.h>


SINGLETON_IMPL(Agmd::GLRenderer)

using namespace AgmdUtilities;

namespace Agmd
{
	extern "C" __declspec(dllexport) void LoadPlugin()
	{
		Renderer::Change(&GLRenderer::Instance());
	}


	extern "C" __declspec(dllexport) void UnloadPlugin()
	{
		Renderer::Destroy();
	}

	template <class T> inline void LoadExtension(T& Proc, const char* Name)
	{
		Proc = reinterpret_cast<T>(wglGetProcAddress(Name));
	}
	#define LOAD_EXTENSION(Ext) LoadExtension(Ext, #Ext)

	#define BUFFER_OFFSET(n) ((char*)NULL + (n))

	PFNGLGETSTRINGIPROC				  GLRenderer::glGetStringi;
	PFNGLBINDBUFFERPROC               GLRenderer::glBindBuffer;
	PFNGLDELETEBUFFERSPROC            GLRenderer::glDeleteBuffers;
	PFNGLGENBUFFERSPROC               GLRenderer::glGenBuffers;
	PFNGLBUFFERDATAPROC               GLRenderer::glBufferData;
	PFNGLBUFFERSUBDATAPROC            GLRenderer::glBufferSubData;
	PFNGLGETBUFFERSUBDATAPROC         GLRenderer::glGetBufferSubData;
	PFNGLMAPBUFFERPROC                GLRenderer::glMapBuffer;
	PFNGLUNMAPBUFFERPROC              GLRenderer::glUnmapBuffer;
	PFNGLACTIVETEXTUREPROC            GLRenderer::glActiveTexture;
	PFNGLCLIENTACTIVETEXTUREPROC      GLRenderer::glClientActiveTexture;
	PFNGLCOMPRESSEDTEXIMAGE2DPROC     GLRenderer::glCompressedTexImage2D;
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC  GLRenderer::glCompressedTexSubImage2D;
	PFNGLPATCHPARAMETERIPROC          GLRenderer::glPatchParameteri;
	PFNGLGENPROGRAMPIPELINESPROC      GLRenderer::glGenProgramPipelines;
	PFNGLBINDPROGRAMPIPELINEPROC      GLRenderer::glBindProgramPipelines;
	PFNGLCREATEPROGRAMPROC            GLRenderer::glCreateProgram;
	PFNGLDELETEPROGRAMPROC            GLRenderer::glDeleteProgram;
	PFNGLCREATESHADERPROC             GLRenderer::glCreateShader;
	PFNGLDELETESHADERPROC             GLRenderer::glDeleteShader;
	PFNGLSHADERSOURCEPROC             GLRenderer::glShaderSource;
	PFNGLCOMPILESHADERPROC            GLRenderer::glCompileShader;
	PFNGLGETSHADERIVPROC              GLRenderer::glGetShaderiv;
	PFNGLGETSHADERINFOLOGPROC		  GLRenderer::glGetShaderInfoLog;
	PFNGLATTACHSHADERPROC             GLRenderer::glAttachShader;
	PFNGLLINKPROGRAMPROC              GLRenderer::glLinkProgram;
	PFNGLGETPROGRAMIVPROC             GLRenderer::glGetProgramiv;
	PFNGLGETPROGRAMINFOLOGPROC		  GLRenderer::glGetProgramInfoLog;
    PFNGLGETACTIVEUNIFORMSIVPROC	  GLRenderer::glGetActiveUniformsiv;
    PFNGLGETACTIVEUNIFORMNAMEPROC	  GLRenderer::glGetActiveUniformName;
    PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC GLRenderer::glGetActiveUniformBlockName;
    PFNGLGETACTIVEUNIFORMBLOCKIVPROC  GLRenderer::glGetActiveUniformBlockiv;
    PFNGLGETINTEGERI_VPROC       	  GLRenderer::glGetIntegeri_v;
	PFNGLGETACTIVEUNIFORMPROC         GLRenderer::glGetActiveUniform;
	PFNGLGETUNIFORMLOCATIONPROC       GLRenderer::glGetUniformLocation;
	PFNGLGETACTIVEATTRIBPROC          GLRenderer::glGetActiveAttrib;
	PFNGLGETATTRIBLOCATIONPROC        GLRenderer::glGetAttribLocation;
	PFNGLGETACTIVEUNIFORMBLOCKIVPROC  GLRenderer::glGetActiveUniformBlock;
	PFNGLGETUNIFORMBLOCKINDEXPROC	  GLRenderer::glGetUniformBlockIndex;
	PFNGLUNIFORMBLOCKBINDINGPROC	  GLRenderer::glUniformBlockBinding;
	PFNGLBINDBUFFERBASEPROC           GLRenderer::glBindBufferBase;
	PFNGLUSEPROGRAMPROC               GLRenderer::glUseProgram;
	PFNGLUNIFORM1IPROC				  GLRenderer::glUniform1i;
	PFNGLUNIFORM2IPROC				  GLRenderer::glUniform2i;
	PFNGLUNIFORM3IPROC				  GLRenderer::glUniform3i;
	PFNGLUNIFORM4IPROC				  GLRenderer::glUniform4i;
	PFNGLUNIFORM1FPROC				  GLRenderer::glUniform1f;
	PFNGLUNIFORM2FPROC				  GLRenderer::glUniform2f;
	PFNGLUNIFORM3FPROC				  GLRenderer::glUniform3f;
    PFNGLUNIFORM4FPROC				  GLRenderer::glUniform4f;
	PFNGLUNIFORM4FVPROC				  GLRenderer::glUniform1fv;
	PFNGLUNIFORM4FVPROC				  GLRenderer::glUniform2fv;
	PFNGLUNIFORM4FVPROC				  GLRenderer::glUniform3fv;
	PFNGLUNIFORM4FVPROC				  GLRenderer::glUniform4fv;
	PFNGLUNIFORMMATRIX2FVPROC		  GLRenderer::glUniformMatrix2fv;
	PFNGLUNIFORMMATRIX3FVPROC		  GLRenderer::glUniformMatrix3fv;
	PFNGLUNIFORMMATRIX4FVPROC		  GLRenderer::glUniformMatrix4fv;
	PFNGLVERTEXATTRIB1FNVPROC		  GLRenderer::glVertexAttrib1f;
	PFNGLVERTEXATTRIB2FNVPROC		  GLRenderer::glVertexAttrib2f;
	PFNGLVERTEXATTRIB3FNVPROC		  GLRenderer::glVertexAttrib3f;
	PFNGLVERTEXATTRIB4FNVPROC		  GLRenderer::glVertexAttrib4f;
	PFNGLVERTEXATTRIBPOINTERPROC      GLRenderer::glVertexAttribPointer;
	PFNGLENABLEVERTEXATTRIBARRAYPROC  GLRenderer::glEnableVertexAttribArray;
	PFNGLBINDATTRIBLOCATIONPROC       GLRenderer::glBindAttribLocation;
	PFNGLGENRENDERBUFFERSPROC         GLRenderer::glGenRenderbuffers;
	PFNGLDELETERENDERBUFFERSPROC      GLRenderer::glDeleteRenderbuffers;
	PFNGLBINDRENDERBUFFERPROC         GLRenderer::glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEPROC      GLRenderer::glRenderbufferStorage;
	PFNGLGENFRAMEBUFFERSPROC          GLRenderer::glGenFramebuffers;
	PFNGLDELETEFRAMEBUFFERSPROC       GLRenderer::glDeleteFramebuffers;
	PFNGLBINDFRAMEBUFFERPROC          GLRenderer::glBindFramebuffer;
    PFNGLDRAWBUFFERSPROC              GLRenderer::glDrawBuffers;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC  GLRenderer::glFramebufferRenderbuffer;
	PFNGLFRAMEBUFFERTEXTUREPROC       GLRenderer::glFramebufferTexture;
	PFNGLFRAMEBUFFERTEXTURE2DPROC     GLRenderer::glFramebufferTexture2D;
	PFNGLFRAMEBUFFERTEXTURE3DPROC     GLRenderer::glFramebufferTexture3D;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC   GLRenderer::glCheckFramebufferStatus;

    PFNWGLCREATECONTEXTATTRIBSARBPROC GLRenderer::wglCreateContextAttribsARB;

	char GLRenderer::VertexPipeline[]   = 
		"\n \
		#version 400\n \
		\n \
		in vec3 in_Vertex;\n \
		in vec3 in_Color;\n \
		in vec2 in_TexCoord0;\n \
		\n \
		out vec3 vPosition; \n \
		out vec3 color;\n \
		out vec2 texCoord0;\n \
		\n \
		uniform mat4 projection;\n \
		uniform mat4 modelview;\n \
		\n \
		void main() \n \
		{ \n \
			vPosition = in_Vertex.xyz;\n \
			gl_Position = projection * modelview * vec4(in_Vertex, 1.0); \n \
			\n \
			color = in_Color; \n \
			texCoord0 = in_TexCoord0; \n \
		} \n";
	char GLRenderer::FragmentPipeline[] = 
		"\n \
		#version 400\n \
		 \n \
		in vec3 color; \n \
		\n \
		in vec2 texCoord0; \n \
		 \n \
		out vec4 out_Color; \n \
		 \n \
		uniform sampler2D texture0; \n \
		 \n \
		void main() \n \
		{ \n \
			out_Color = texture2D(texture0, texCoord0); \n \
		} \n";
	static char tessEval[] = 
		" \n \
		#version 400\n \
		layout(triangles, equal_spacing, cw) in; \n \
		in vec3 tcPosition[]; \n \
		out vec3 tePosition; \n \
		out vec3 tePatchDistance; \n \
		uniform mat4 projection; \n \
		uniform mat4 modelview; \n \
		 \n \
		void main() \n \
		{ \n \
			vec3 p0 = gl_TessCoord.x * tcPosition[0]; \n \
			vec3 p1 = gl_TessCoord.y * tcPosition[1]; \n \
			vec3 p2 = gl_TessCoord.z * tcPosition[2]; \n \
			tePatchDistance = gl_TessCoord; \n \
			tePosition = normalize(p0 + p1 + p2); \n \
			gl_Position = projection * modelview * vec4(tePosition, 1); \n \
		} \n";

	static char tessControl[] = 
		" \n \
		#version 400\n \
		layout(vertices = 3) out;\n \
		in vec3 vPosition[];\n \
		out vec3 tcPosition[];\n \
		uniform float TessLevelInner;\n \
		uniform float TessLevelOuter;\n \
		\n \
		#define ID gl_InvocationID\n \
		\n \
		void main()\n \
		{\n \
			tcPosition[ID] = vPosition[ID];\n \
			if (ID == 0) {\n \
				gl_TessLevelInner[0] = TessLevelInner;\n \
				gl_TessLevelOuter[0] = TessLevelOuter;\n \
				gl_TessLevelOuter[1] = TessLevelOuter;\n \
				gl_TessLevelOuter[2] = TessLevelOuter;\n \
			}\n \
		}";

	static char geom[] = 
		"\n \
		#version 400\n \
		uniform mat4 modelview; \n \
		layout(triangles) in; \n \
		layout(triangle_strip, max_vertices = 3) out; \n \
		in vec3 tePosition[3]; \n \
		in vec3 tePatchDistance[3]; \n \
		out vec3 gFacetNormal; \n \
		out vec3 gPatchDistance; \n \
		out vec3 gTriDistance; \n \
		 \n \
		void main() \n \
		{ \n \
			mat3 NormalMatrix = mat3(modelview); \n \
			vec3 A = tePosition[2] - tePosition[0]; \n \
			vec3 B = tePosition[1] - tePosition[0]; \n \
			gFacetNormal = NormalMatrix * normalize(cross(A, B)); \n \
		 \n \
			gPatchDistance = tePatchDistance[0]; \n \
			gTriDistance = vec3(1, 0, 0); \n \
			gl_Position = gl_in[0].gl_Position; EmitVertex(); \n \
			 \n \
			gPatchDistance = tePatchDistance[1]; \n \
			gTriDistance = vec3(0, 1, 0); \n \
			gl_Position = gl_in[1].gl_Position; EmitVertex(); \n \
			 \n \
			gPatchDistance = tePatchDistance[2]; \n \
			gTriDistance = vec3(0, 0, 1); \n \
			gl_Position = gl_in[2].gl_Position; EmitVertex(); \n \
			 \n \
			EndPrimitive(); \n \
		}";
	GLRenderer::GLRenderer() :
	m_Hwnd              (NULL),
	m_Handle            (NULL),
	m_Context           (NULL),
	m_CurrentDeclaration(NULL),
	m_Extensions        (""),
	m_Reload			(false),
	m_CurrentProgram    (NULL),
    last_unit(TEXTURE_UNIT_0)
	{
		std::memset(m_TextureBind,NULL,sizeof(void*)*MAX_TEXTUREUNIT);
	}

	GLRenderer::~GLRenderer()
	{
		// Destruction du contexte
		if (m_Context)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_Context);
		}

		// Libération du handle graphique de la fenêtre
		if (m_Hwnd && m_Handle)
		{
			ReleaseDC(m_Hwnd, m_Handle);
		}
		Logger::Destroy();
	}

	std::string GLRenderer::GetRendererDesc() const
	{
		
		return std::string("OpenGL ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)) + ", GLSL " + reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void GLRenderer::Setup(HWND Hwnd)
	{
		Logger::Instance().SetFilename("OpenGL");
		/*if (bFullscreen)
		{
			DEVMODE ScreenSettings;
			memset(&ScreenSettings, 0, sizeof(DEVMODE));
			ScreenSettings.dmSize       = sizeof(DEVMODE);
			ScreenSettings.dmPelsWidth  = 1024;
			ScreenSettings.dmPelsHeight = 768;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	
			if (ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				throw COGLException("ChangeDisplaySettings", "Initialize");
		}*/

		// Paramètres de rendu
		PIXELFORMATDESCRIPTOR PixelDescriptor = 
		{ 
			sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
			1,                               // version number 
			PFD_DRAW_TO_WINDOW |             // support window 
			PFD_SUPPORT_OPENGL |             // support OpenGL 
			PFD_DOUBLEBUFFER,                // double buffered 
			PFD_TYPE_RGBA,                   // RGBA type 
			32,                              // 32-bit color depth 
			0, 0, 0, 0, 0, 0,                // color bits ignored 
			0,                               // no alpha buffer 
			0,                               // shift bit ignored 
			0,                               // no accumulation buffer 
			0, 0, 0, 0,                      // accum bits ignored 
			32,                              // 32-bit z-buffer 
			32,                              // 32-bits stencil buffer 
			0,                               // no auxiliary buffer 
			PFD_MAIN_PLANE,                  // main layer 
			0,                               // reserved 
			0, 0, 0                          // layer masks ignored 
		};

		// Récupération du Hwnd et du HDC de la fenêtre de rendu
		m_Hwnd   = Hwnd;
		m_Handle = GetDC(Hwnd);

		// Choix du meilleur format de pixel
		assert(SetPixelFormat(m_Handle, ChoosePixelFormat(m_Handle, &PixelDescriptor), &PixelDescriptor));

		// Création du contexte de rendu
		m_Context = wglCreateContext(m_Handle);
		assert(wglMakeCurrent(m_Handle, m_Context));

	    int attribs[] =
	    {
		    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		    WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		    WGL_CONTEXT_FLAGS_ARB, 0,
		    0
	    };

		// Chargement des extensions
		LoadExtensions();

        if(wglCreateContextAttribsARB != NULL)
        {
            HGLRC temp =  wglCreateContextAttribsARB(m_Handle,0,attribs);
		    wglMakeCurrent(NULL,NULL);
		    wglDeleteContext(m_Context);
            m_Context = temp;
		    wglMakeCurrent(m_Handle, m_Context);
        }

		// Récupération des extensions supportées
		int n;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n);
		for (int i = 0; i < n; i++)
		{
			m_Extensions += reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i));
			m_Extensions +="\n";
		}


		// States par défaut
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		glDepthRange(0.0, 1.0);
		glClearStencil(0x00);

		glEnable(GL_DEPTH_TEST);

		//init default shader

		m_Pipeline.LoadFromFile("Shader/classic_pipeline.glsl");

		m_DebugPipeline[0].LoadFromFile("Shader/debug_cubemap.glsl");

		glFrontFace(GL_CCW);
	}

	void GLRenderer::CheckCaps()
	{
		m_Capabilities[CAP_HW_MIPMAPPING] = CheckExtension("GL_SGIS_generate_mipmap");

		m_Capabilities[CAP_DXT_COMPRESSION] = CheckExtension("GL_ARB_texture_compression") &&
											  CheckExtension("GL_EXT_texture_compression_s3tc");

		m_Capabilities[CAP_TEX_NON_POWER_2] = CheckExtension("GL_ARB_texture_non_power_of_two");

		m_Capabilities[CAP_TESSELATION_SHADER] = CheckExtension("GL_ARB_tessellation_shader");
	}

	bool GLRenderer::CheckExtension(const std::string& Extension) const
	{
		return m_Extensions.find(Extension) != std::string::npos;
	}

	const std::string GLRenderer::GetExtension() const
	{
		return m_Extensions;
	}

	const std::string GLRenderer::GetConstant() const
	{
		std::string str = "";
		int32 value;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &value);
		str += "Max vertex attrib : " + value;

		glGetIntegerv(GL_MAX_VARYING_FLOATS, &value);
		str += "\nMax vertex attrib : " + value;
		return str;
	}

	void GLRenderer::LoadExtensions()
	{
		LOAD_EXTENSION(glGetStringi);
		LOAD_EXTENSION(glBindBuffer);
		LOAD_EXTENSION(glDeleteBuffers);
		LOAD_EXTENSION(glGenBuffers);
		LOAD_EXTENSION(glBufferData);
		LOAD_EXTENSION(glBufferSubData);
		LOAD_EXTENSION(glBindBufferBase);
		LOAD_EXTENSION(glGetBufferSubData);
		LOAD_EXTENSION(glMapBuffer);
		LOAD_EXTENSION(glUnmapBuffer);
		LOAD_EXTENSION(glActiveTexture);
		LOAD_EXTENSION(glClientActiveTexture);
		LOAD_EXTENSION(glCompressedTexImage2D);
		LOAD_EXTENSION(glCompressedTexSubImage2D);
		LOAD_EXTENSION(glPatchParameteri);
		LOAD_EXTENSION(glGenProgramPipelines);
		LOAD_EXTENSION(glBindProgramPipelines);
		LOAD_EXTENSION(glCreateProgram);
		LOAD_EXTENSION(glDeleteProgram);
		LOAD_EXTENSION(glCreateShader);
		LOAD_EXTENSION(glDeleteShader);
		LOAD_EXTENSION(glShaderSource);
		LOAD_EXTENSION(glCompileShader);
		LOAD_EXTENSION(glGetShaderiv);
		LOAD_EXTENSION(glGetShaderInfoLog);
		LOAD_EXTENSION(glAttachShader);
		LOAD_EXTENSION(glLinkProgram);
		LOAD_EXTENSION(glGetProgramiv);
		LOAD_EXTENSION(glGetProgramInfoLog);
		LOAD_EXTENSION(glGetActiveUniformsiv);
		LOAD_EXTENSION(glGetActiveUniformName);
		LOAD_EXTENSION(glGetActiveUniformBlockName);
		LOAD_EXTENSION(glGetActiveUniformBlockiv);
		LOAD_EXTENSION(glGetIntegeri_v);
		LOAD_EXTENSION(glGetActiveUniform);
		LOAD_EXTENSION(glGetUniformLocation);
		LOAD_EXTENSION(glGetActiveAttrib);
		LOAD_EXTENSION(glGetAttribLocation);
		LOAD_EXTENSION(glGetActiveUniformBlock);
		LOAD_EXTENSION(glUniformBlockBinding);
		LOAD_EXTENSION(glGetUniformBlockIndex);
		LOAD_EXTENSION(glUseProgram);
		LOAD_EXTENSION(glUniform1i);
		LOAD_EXTENSION(glUniform2i);
		LOAD_EXTENSION(glUniform3i);
		LOAD_EXTENSION(glUniform4i);
		LOAD_EXTENSION(glUniform1f);
		LOAD_EXTENSION(glUniform2f);
		LOAD_EXTENSION(glUniform3f);
		LOAD_EXTENSION(glUniform4f);	
		LOAD_EXTENSION(glUniform1fv);
		LOAD_EXTENSION(glUniform2fv);
		LOAD_EXTENSION(glUniform3fv);
		LOAD_EXTENSION(glUniform4fv);
		LOAD_EXTENSION(glUniformMatrix2fv);
		LOAD_EXTENSION(glUniformMatrix3fv);
		LOAD_EXTENSION(glUniformMatrix4fv);
		LOAD_EXTENSION(glVertexAttrib1f);
		LOAD_EXTENSION(glVertexAttrib2f);
		LOAD_EXTENSION(glVertexAttrib3f);
		LOAD_EXTENSION(glVertexAttrib4f);
		LOAD_EXTENSION(glVertexAttribPointer);
		LOAD_EXTENSION(glBindAttribLocation);
        LOAD_EXTENSION(glEnableVertexAttribArray);
		LOAD_EXTENSION(glGenRenderbuffers);
		LOAD_EXTENSION(glDeleteRenderbuffers);
		LOAD_EXTENSION(glBindRenderbuffer);
		LOAD_EXTENSION(glRenderbufferStorage);
		LOAD_EXTENSION(glGenFramebuffers);
		LOAD_EXTENSION(glDeleteFramebuffers);
		LOAD_EXTENSION(glBindFramebuffer);
        LOAD_EXTENSION(glDrawBuffers);
		LOAD_EXTENSION(glFramebufferRenderbuffer);
		LOAD_EXTENSION(glFramebufferTexture);
		LOAD_EXTENSION(glFramebufferTexture2D);
		LOAD_EXTENSION(glFramebufferTexture3D);
		LOAD_EXTENSION(glCheckFramebufferStatus);

        LOAD_EXTENSION(wglCreateContextAttribsARB);
	}

	void GLRenderer::InitScene()
	{
		if(m_Reload)
		{
			m_Pipeline.ReloadFromFile("Shader/classic_pipeline.glsl");
			m_Reload = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		m_Pipeline.Enable();
	}

	void GLRenderer::EndScene()
	{
        glFinish();
		m_Pipeline.Disable();
		SwapBuffers(m_Handle); 
	}


	BaseBuffer* GLRenderer::CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const
	{
		unsigned int VertexBuffer = 0;
		glGenBuffers(1, &VertexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));

		return new GLVertexBuffer(size, VertexBuffer);
	}

	BaseBuffer* GLRenderer::CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const
	{
		unsigned int IndexBuffer = 0;
		glGenBuffers(1, &IndexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));

		return new GLIndexBuffer(size, IndexBuffer);
	}

	BaseBuffer* GLRenderer::CreateUB(unsigned long size, unsigned long stride, unsigned long flags, int bindPoint) const
	{
		unsigned int uniformBuffer = 0;
		glGenBuffers(1, &uniformBuffer);

		glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));
		glBindBufferBase(GL_UNIFORM_BUFFER,bindPoint,uniformBuffer);

		return new GLUniformBuffer(size, uniformBuffer, bindPoint);
	}

	BaseBuffer* GLRenderer::CreateTB(unsigned long size, unsigned long stride, unsigned long flags) const
	{
		unsigned int textureBuffer = 0;
		glGenBuffers(1, &textureBuffer);

		glBindBuffer(GL_TEXTURE_BUFFER, textureBuffer);
		glBufferData(GL_TEXTURE_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));



		return new GLTextureBuffer(size, textureBuffer,NULL);
	}

	Declaration* GLRenderer::CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const
	{
		GLDeclaration* declaration = new GLDeclaration;

		std::vector<int> offset(count, 0);
		for (const TDeclarationElement* Elt = elt; Elt < elt + count; ++Elt)
		{
			GLDeclaration::TElement CurrentElement;
			CurrentElement.usage  = Elt->usage;
			CurrentElement.type   = Elt->dataType;
			CurrentElement.offset = offset[Elt->stream];

			declaration->AddElement(Elt->stream, CurrentElement);

			static const unsigned int Size[] = {4, 8, 12, 16, 4};
			offset[Elt->stream] += Size[Elt->dataType];
		}

		return declaration;
	}

	void GLRenderer::SetVB(unsigned int stream, const BaseBuffer* buffer, unsigned long stride, unsigned long minVertex, unsigned long maxVertex)
	{
		const GLVertexBuffer* VertexBuffer = static_cast<const GLVertexBuffer*>(buffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->GetBuffer());

		static const unsigned int Size[] = {1, 2, 3, 4, 4};
		static const unsigned int Type[] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE};

		const GLDeclaration::TElementArray& StreamDesc = m_CurrentDeclaration->GetStreamElements(stream);
		for (GLDeclaration::TElementArray::const_iterator i = StreamDesc.begin(); i != StreamDesc.end(); ++i)
		{
			switch (i->usage)
			{
				case ELT_USAGE_POSITION :
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_NORMAL :
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_DIFFUSE :
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_TEXCOORD0 :
					//glActiveTexture(GL_TEXTURE0);
					//glEnable(GL_TEXTURE_2D);
					//glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(3);
					glVertexAttribPointer(3, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_TEXCOORD1 :
					//glActiveTexture(GL_TEXTURE0);
					//glEnable(GL_TEXTURE_2D);
					//glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(4);
					glVertexAttribPointer(4, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_TEXCOORD2 :
					//glActiveTexture(GL_TEXTURE0);
					//glEnable(GL_TEXTURE_2D);
					//glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(5);
					glVertexAttribPointer(5, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_TEXCOORD3 :
					//glActiveTexture(GL_TEXTURE0);
					//glEnable(GL_TEXTURE_2D);
					glEnableVertexAttribArray(6);
					glVertexAttribPointer(6, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_TANGENT :
					glEnableVertexAttribArray(7);
					glVertexAttribPointer(7, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_BONE_WEIGHT :
					glEnableVertexAttribArray(8);
					glVertexAttribPointer(8, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_BONE_INDEX :
					glEnableVertexAttribArray(9);
					glVertexAttribPointer(9, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				case ELT_USAGE_BONE_COUNT :
					glEnableVertexAttribArray(10);
					glVertexAttribPointer(10, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

			}
		}
	}

	void GLRenderer::SetIB(const BaseBuffer* buffer, unsigned long stride)
	{
		const GLIndexBuffer* IndexBuffer = static_cast<const GLIndexBuffer*>(buffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->GetBuffer());

		m_IndexStride = stride;
	}

	void GLRenderer::SetDeclaration(const Declaration* declaration)
	{
		m_CurrentDeclaration = static_cast<const GLDeclaration*>(declaration);
	}

	void GLRenderer::DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count)
	{
		switch (type)
		{
			case PT_TRIANGLELIST :  glDrawArrays(GL_TRIANGLES,      firstVertex, count * 3); break;
			case PT_TRIANGLESTRIP : glDrawArrays(GL_TRIANGLE_STRIP, firstVertex, count + 2); break;
			case PT_TRIANGLEFAN :   glDrawArrays(GL_TRIANGLE_FAN,   firstVertex, count + 1); break;
			case PT_LINELIST :      glDrawArrays(GL_LINES,          firstVertex, count * 2); break; 
			case PT_LINESTRIP :     glDrawArrays(GL_LINE_STRIP,     firstVertex, count + 1); break;
			case PT_POINTLIST :     glDrawArrays(GL_POINTS,         firstVertex, count);     break;
		}
	}

	void GLRenderer::DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count)
	{
		unsigned long indicesType = (m_IndexStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
		const void*   offset      = BUFFER_OFFSET(firstIndex * m_IndexStride);
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		getPipeline()->SetParameter(MAT_MODEL,MatStack::get());
		//updateGlobalBuffer();
		getPipeline()->SetParameter("u_textureFlags",(int)m_TextureFlags);
		switch (type)
		{
			case PT_TRIANGLELIST :  glDrawElements(GL_TRIANGLES,      count, indicesType, offset); break;
			case PT_TRIANGLESTRIP : glDrawElements(GL_TRIANGLE_STRIP, count, indicesType, offset); break;
			case PT_TRIANGLEFAN :   glDrawElements(GL_TRIANGLE_FAN,   count, indicesType, offset); break;
			case PT_LINELIST :      glDrawElements(GL_LINES,          count, indicesType, offset); break; 
			case PT_LINESTRIP :     glDrawElements(GL_LINE_STRIP,     count, indicesType, offset); break;
			case PT_POINTLIST :     glDrawElements(GL_POINTS,         count, indicesType, offset); break;
			case PT_PATCHLIST :     glDrawElements(GL_PATCHES,        count, indicesType, offset); break;
		}
	}
	void GLRenderer::DrawSomething()
	{
		glBegin(GL_POLYGON);
		glColor3ub(125,125,125); glVertex3f(0,-1,-1);
		glColor3ub(255,0,0); glVertex3f(0,-1,1);
		glColor3ub(0,255,0); glVertex3f(0,1,1);
		glColor3ub(0,0,255); glVertex3f(0,1,-1);
		glEnd();
	}

	uint32 GLRenderer::ConvertColor(const Color& color) const
	{
		return color.ToABGR();
	}

	void GLRenderer::SetTexture(uint32 unit, const TextureBase* texture, TTextureType type)
	{

		if(unit > MAX_TEXTUREUNIT)
			return;
		
		if(m_TextureBind[unit] == texture)
			return; // NO CHANGE? -> return!

		const GLTexture* oGLTexture = static_cast<const GLTexture*>(texture);

        if(last_unit != unit)
        {
		    glActiveTexture(GL_TEXTURE0+unit);
            last_unit = unit;
        }

		if (texture)
		{
			glBindTexture(RGLEnum::Get(oGLTexture->GetType()), oGLTexture->GetGLTexture());
		}
		else if(m_TextureBind[unit])
		{
			glBindTexture(RGLEnum::Get(m_TextureBind[unit]->GetType()), 0);
		}

		m_TextureBind[unit] = texture;
	}

	TextureBase* GLRenderer::CreateTexture(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags) const
	{
		switch(type)
		{
		case TEXTURE_2D:
			return CreateTexture2D(size,format,flags);
		case TEXTURE_CUBE:
			return CreateTextureCube(size,format,flags);
		default:
			Logger::Log(LOGERROR,"Error on CreateTexture - unknown or unsupported TextureType : %d",(int)type);
			return NULL;
		}
	}

	TextureBase* GLRenderer::CreateTexture2D(const ivec2& size, TPixelFormat format, unsigned long flags) const
	{
		uint32 texture;
		glGenTextures(1, &texture);
		int width  = size.x;
		int height = size.y;
		int nbMipmaps = 0;
		glBindTexture(GL_TEXTURE_2D, texture);

		if(format == PXF_DEPTH)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
			nbMipmaps = 0;
		}else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			nbMipmaps = flags & TEX_NOMIPMAP ? 0 : GetNbMipLevels(size.x, size.y);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, nbMipmaps);

			if ((nbMipmaps > 0) && (HasCapability(CAP_HW_MIPMAPPING)))
				glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

		}

		for (int i = 0; i <= nbMipmaps; ++i)
		{
			glTexImage2D(GL_TEXTURE_2D, i, RGLEnum::Get(format).Internal, width, height, 0, RGLEnum::Get(format)._Format, format == PXF_DEPTH ? GL_FLOAT : GL_UNSIGNED_BYTE, NULL);

			if (width > 1)  width  /= 2;
			if (height > 1) height /= 2;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		return new GLTexture2D(size, format, nbMipmaps > 0, HasCapability(CAP_HW_MIPMAPPING), texture);
	}

	TextureBase* GLRenderer::CreateTextureCube(const ivec2& size, TPixelFormat format, unsigned long flags) const
	{
		uint32 texture;
		glGenTextures(1, &texture);
		int width  = size.x;
		int height = size.y;
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		for (int i = 0; i < 6; i++)
		{

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, RGLEnum::Get(format).Internal, width, height, 0,  RGLEnum::Get(format)._Format, GL_UNSIGNED_BYTE, NULL);
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return new GLTextureCube(size,format,false,false,texture);
	}

	void GLRenderer::SetupAlphaBlending(TBlend src, TBlend dest) const
	{
		glBlendFunc(RGLEnum::Get(src), RGLEnum::Get(dest));
	}

    void GLRenderer::SetupDepthTest(TDepth mode)
    {
        glDepthFunc(RGLEnum::Get(mode));
    }

	void GLRenderer::SetupTextureUnit(uint32 unit, TTextureOp op, TTextureArg arg1, TTextureArg arg2, const Color& constant) const
	{
		glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0 + unit);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

		if (op < TXO_ALPHA_FIRSTARG)
		{
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, RGLEnum::Get(op));
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, RGLEnum::Get(arg1));
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, RGLEnum::Get(arg2));
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);
		}
		else
		{
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, RGLEnum::Get(op));
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, RGLEnum::Get(arg1));
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, RGLEnum::Get(arg2));
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_SRC_ALPHA);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT, GL_SRC_ALPHA);
		}

		if ((arg1 == TXA_CONSTANT) || (arg2 == TXA_CONSTANT))
		{
			float color[4];
			constant.ToFloat(color);
			glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR,color);
		}
	}

	void GLRenderer::Enable(TRenderParameter param, bool value)
	{
		switch (param)
		{
			case RENDER_ZWRITE :
			{
				glDepthMask(value);
				break;
			}
			case RENDER_TRANSPARENT: /* DEPRECATED */
			{ 
                

				/*if(value)
					glEnable(GL_ALPHA_TEST);
				else glDisable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GEQUAL,0.7f);
                */
				break;
			}
            case RENDER_RENDERING:
                glDrawBuffer(value ? GL_BACK : GL_NONE);
			default :
			{
				int _value = RGLEnum::Get(param);

				if(!_value)
					break;

				if (value)
					glEnable(_value);
				else
					glDisable(_value);
			}
		}
	}

	void GLRenderer::setClipPlane(uint32 clipUnit, double* plane)
	{
		if(clipUnit > 5)
			return;

		glClipPlane(GL_CLIP_PLANE0+clipUnit,plane);
	}

	void GLRenderer::setRenderMode(TRenderMode mode)
	{

		glPolygonMode(GL_FRONT_AND_BACK,RGLEnum::Get(mode));
	}

	BaseShader* GLRenderer::CreateShader(std::string source,TShaderType type) const
	{
		
		int index;
		index = source.find_first_of("\n");
		std::string define = "";
		switch(type)
		{
		case SHADER_VERTEX:
			if(source.find("_VERTEX_") == std::string::npos)
				return NULL;
			define = "#define _VERTEX_\n";
			break;
		case SHADER_TESS_CONTROL:
			if(source.find("_TESS_CONTROL_") == std::string::npos)
				return NULL;
			define = "#define _TESS_CONTROL_\n";
			break;
		case SHADER_TESS_EVALUATION:
			if(source.find("_TESS_EVALUATION_") == std::string::npos)
				return NULL;
			define = "#define _TESS_EVALUATION_\n";
			break;
		case SHADER_GEOMETRY:
			if(source.find("_GEOMETRY_") == std::string::npos)
				return NULL;
			define = "#define _GEOMETRY_\n";
			break;
		case SHADER_PIXEL:
			if(source.find("_FRAGMENT_") == std::string::npos)
				return NULL;
			define = "#define _FRAGMENT_\n";
			break;

		}
		if(index != std::string::npos)
			source = source.substr(0,index+1)+define+source.substr(index+1,source.size()-1);
		const char* src = source.c_str();
		uint32 shader = glCreateShader(RGLEnum::Get(type));
		glShaderSource(shader, 1, (const char**)&src, NULL);
    
		glCompileShader(shader);
    
		int32 compile_status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
		int32 logsize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        
		char *log = new char[logsize+1];
		memset(log, '\0', logsize + 1);
        
		glGetShaderInfoLog(shader, logsize, &logsize, log);
		Logger::Log(LOGNORMAL, "%s", log);
       
		delete[] log;
		if(compile_status != GL_TRUE)
		{

			glDeleteShader(shader);
			return NULL;
		}
    
		return new GLShader(shader,type);
	}

	BaseShaderProgram* GLRenderer::CreateShaderProgram(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag) const
	{
		uint32 id = glCreateProgram();
		if(vertex)
			glAttachShader(id,static_cast<GLShader*>(vertex)->GetId());

		if(eval)
			glAttachShader(id,static_cast<GLShader*>(eval)->GetId());

		if(control)
			glAttachShader(id,static_cast<GLShader*>(control)->GetId());

		if(geom)
			glAttachShader(id,static_cast<GLShader*>(geom)->GetId());

		if(frag)
			glAttachShader(id,static_cast<GLShader*>(frag)->GetId());


		/* Bind engine var*/
		glBindAttribLocation(id, 0,  "in_Vertex");
		glBindAttribLocation(id, 1,  "in_Normal");
		glBindAttribLocation(id, 2,  "in_Color");
		glBindAttribLocation(id, 3,  "in_TexCoord0");
		glBindAttribLocation(id, 4,  "in_TexCoord1");
		glBindAttribLocation(id, 5,  "in_TexCoord2");
		glBindAttribLocation(id, 6,  "in_TexCoord3");
		glBindAttribLocation(id, 7,  "in_Tangent");
		glBindAttribLocation(id, 8,  "in_BoneWeight");
		glBindAttribLocation(id, 9,  "in_BoneIndex");
		glBindAttribLocation(id, 10, "in_BoneCount");
		/**/

		glLinkProgram(id);

		int32 link;

		glGetProgramiv(id, GL_LINK_STATUS, &link);

		int32 logsize;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logsize);
	
		char* log = new char[logsize + 1];

		glGetProgramInfoLog(id, logsize, &logsize, log);
		log[logsize] = '\0';

		Logger::Log(LOGNORMAL, "%s", log);

		delete[] log;

		if(link != GL_TRUE)
		{
			glDeleteProgram(id);
			return NULL;
		}

		GLShaderProgram* program = new GLShaderProgram(id);
		program->SetParameter("cameraInfoBlock",(uint32)UNIFORM_CAMERA_BIND);
        program->SetParameter("lightInfoBlock",(uint32)UNIFORM_LIGHT_BIND);
        program->UniformShaderInfo();
		return program;
	}

	const BaseShaderProgram* GLRenderer::getPipeline()
	{
		if(m_CurrentProgram)
			return m_CurrentProgram;
		else
			return m_Pipeline.GetShaderProgram();
	}

	FrameBuffer* GLRenderer::CreateFrameBuffer() const
	{
		uint32 id = 0;

		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		/*uint32 status = glCheckFrameBufferStatus(GL_FRAMEBUFFER);
		if(status != GL_FRAMEBUFFER_COMPLETE)
		{
			// need log
			glBindFrameBuffer(GL_FRAMEBUFFER,0);
			glDeleteFramebuffers(1,&id);
			return NULL;
		}*/
		//glDrawBuffer(GL_NONE);
		//glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER,0);

		return new GLFrameBuffer(id);
	}

	RenderBuffer* GLRenderer::CreateRenderBuffer(const ivec2& size, TPixelFormat format) const
	{
		uint32 id = 0;

		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER,id);
		glRenderbufferStorage(GL_RENDERBUFFER,RGLEnum::Get(format).Internal,size.x,size.y);
		glBindRenderbuffer(GL_RENDERBUFFER,0);

		return new GLRenderBuffer(id,size);
		
	}

	void GLRenderer::ReloadPipeline()
	{
		m_Reload = true;
	}

	void GLRenderer::SetCurrentProgram(const BaseShaderProgram* prog)
	{
		m_CurrentProgram = prog;
		if(m_CurrentProgram)
			m_CurrentProgram->Use(true);
		else m_Pipeline.Enable();
	}

	void GLRenderer::SetViewPort(ivec2 xy, ivec2 size)
	{
		glViewport(xy.x, xy.y, size.x, size.y);
	}

	struct vert
	{
		vec3 pos;
		vec2 tpos;
	};

	void GLRenderer::DebugCubeMap(const TextureBase* tex)
	{
		if(tex->GetType() != TEXTURE_CUBE)
			return;
		float m_fSize = 1.0f;
		vert vertex[] = 
		{	
			//X+
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},
			//X-
			{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y+
			{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y-
			{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},
			//Z+
			{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},
			//Z-
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,1)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)}
		};

		std::vector<short> indices;

		SetCurrentProgram(m_DebugPipeline[0].GetShaderProgram());
		for(uint32 i = 0; i < 6; i++)
		{

			glBegin(GL_TRIANGLES);
			glTexCoord2fv((float*)&(vertex[1+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[1+i*4].pos.x));
			glTexCoord2fv((float*)&(vertex[2+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[2+i*4].pos.x));
			glTexCoord2fv((float*)&(vertex[0+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[0+i*4].pos.x));
			glEnd();

			glBegin(GL_TRIANGLES);
			glTexCoord2fv((float*)&(vertex[1+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[1+i*4].pos.x));
			glTexCoord2fv((float*)&(vertex[3+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[3+i*4].pos.x));
			glTexCoord2fv((float*)&(vertex[2+i*4].tpos.x));
			glVertex3fv((float*)&(vertex[2+i*4].pos.x));
			glEnd();
		}
		SetCurrentProgram(NULL);
	}

	#define FRONT 1
	#define BACK  2

	void GLRenderer::SetCullFace(int face)
	{
		if(face)
			glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
		if(face == FRONT)
			glCullFace(GL_FRONT);
		else if(face == BACK)
			glCullFace(GL_BACK);
		else if(face & (FRONT | BACK))
			glCullFace(GL_FRONT_AND_BACK);
	}

}

