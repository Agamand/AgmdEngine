#include <Renderer\OpenGL\GlRenderer.h>
#include <Renderer\OpenGL\GlTexture.h>
#include <Renderer\OpenGL\GlShader.h>
#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlEnums.h>
#include <Renderer\OpenGL\GlFrameBuffer.h>
#include <Renderer\OpenGL\GlRenderBuffer.h>
#include <Utilities\Color.h>
#include <Utilities\PixelUtils.h>
#include <Matrix4.h>
#include <gl\GLU.h>
#include <Cg/cgGL.h>
#include <Debug/New.h>

SINGLETON_IMPL(Agmd::GLRenderer)

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
	PFNGLGETACTIVEUNIFORMPROC         GLRenderer::glGetActiveUniform;
	PFNGLGETUNIFORMLOCATIONPROC       GLRenderer::glGetUniformLocation;
	PFNGLGETACTIVEATTRIBPROC          GLRenderer::glGetActiveAttrib;
	PFNGLGETATTRIBLOCATIONPROC        GLRenderer::glGetAttribLocation;
	PFNGLUSEPROGRAMPROC               GLRenderer::glUseProgram;
	PFNGLUNIFORM1IPROC				  GLRenderer::glUniform1i;
	PFNGLUNIFORM2IPROC				  GLRenderer::glUniform2i;
	PFNGLUNIFORM3IPROC				  GLRenderer::glUniform3i;
	PFNGLUNIFORM4IPROC				  GLRenderer::glUniform4i;
	PFNGLUNIFORM1FPROC				  GLRenderer::glUniform1f;
	PFNGLUNIFORM2FPROC				  GLRenderer::glUniform2f;
	PFNGLUNIFORM3FPROC				  GLRenderer::glUniform3f;
    PFNGLUNIFORM4FPROC				  GLRenderer::glUniform4f;
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
	PFNGLFRAMEBUFFERRENDERBUFFERPROC  GLRenderer::glFramebufferRenderbuffer;
	PFNGLFRAMEBUFFERTEXTUREPROC       GLRenderer::glFramebufferTexture;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC   GLRenderer::glCheckFramebufferStatus;

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
	m_RenderFlags       (0),
	m_Reload			(false),
	m_CurrentProgram    (NULL)
	{}

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
	}

	std::string GLRenderer::GetRendererDesc() const
	{
		return std::string("OpenGL ") + reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}

	void GLRenderer::Setup(HWND Hwnd)
	{
		/*if (bFullscreen)
		{
			// Paramètres
			DEVMODE ScreenSettings;
			memset(&ScreenSettings, 0, sizeof(DEVMODE));
			ScreenSettings.dmSize       = sizeof(DEVMODE);
			ScreenSettings.dmPelsWidth  = 1024;
			ScreenSettings.dmPelsHeight = 768;
			ScreenSettings.dmBitsPerPel = 32;
			ScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Passage en plein écran
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

		// Récupération des extensions supportées
		m_Extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

		// Chargement des extensions
		LoadExtensions();

		// States par défaut
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glDepthRange(1.0, 0.0);
		glClearStencil(0x00);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		//Initialise le shader pipeline

		/*BaseShader* vertex = CreateShader(VertexPipeline,SHADER_VERTEX);
		BaseShader* fragment = CreateShader(FragmentPipeline,SHADER_PIXEL);
		BaseShader* eval = CreateShader(tessEval,SHADER_TESS_EVALUATION);
		BaseShader* control = CreateShader(tessControl,SHADER_TESS_CONTROL);
		BaseShader* geo = CreateShader(geom,SHADER_GEOMETRY);

		m_Pipeline.Create(vertex, eval, control, geo, fragment);*/
		m_Pipeline.LoadFromFile("Shader/classic_pipeline.glsl");
		m_Pipeline.SetParameter("TessLevelInner",1.0f);
		m_Pipeline.SetParameter("TessLevelOuter",1.0f);

		//delete vertex;
		//delete fragment;
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

	void GLRenderer::LoadExtensions()
	{
		LOAD_EXTENSION(glBindBuffer);
		LOAD_EXTENSION(glDeleteBuffers);
		LOAD_EXTENSION(glGenBuffers);
		LOAD_EXTENSION(glBufferData);
		LOAD_EXTENSION(glBufferSubData);
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
		LOAD_EXTENSION(glGetActiveUniform);
		LOAD_EXTENSION(glGetUniformLocation);
		LOAD_EXTENSION(glGetActiveAttrib);
		LOAD_EXTENSION(glGetAttribLocation);
		LOAD_EXTENSION(glUseProgram);
		LOAD_EXTENSION(glUniform1i);
		LOAD_EXTENSION(glUniform2i);
		LOAD_EXTENSION(glUniform3i);
		LOAD_EXTENSION(glUniform4i);
		LOAD_EXTENSION(glUniform1f);
		LOAD_EXTENSION(glUniform2f);
		LOAD_EXTENSION(glUniform3f);
		LOAD_EXTENSION(glUniform4f);
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
		LOAD_EXTENSION(glFramebufferRenderbuffer);
		LOAD_EXTENSION(glFramebufferTexture);
		LOAD_EXTENSION(glCheckFramebufferStatus);
	}

	void GLRenderer::InitScene()
	{
		if(m_Reload)
		{
			m_Pipeline.ReloadFromFile("Shader/classic_pipeline.glsl");
			m_Pipeline.SetParameter("TessLevelInner",1.0f);
			m_Pipeline.SetParameter("TessLevelOuter",1.0f);
			m_Reload = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		m_Pipeline.Enable();
	}

	void GLRenderer::EndScene()
	{
		m_Pipeline.Disable();
		SwapBuffers(m_Handle); 
	}


	BaseBuffer* GLRenderer::CreateVB(unsigned long size, unsigned long stride, unsigned long flags) const
	{
		// Création du buffer
		unsigned int VertexBuffer = 0;
		glGenBuffers(1, &VertexBuffer);

		// Remplissage
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));

		return new GLVertexBuffer(size, VertexBuffer);
	}

	BaseBuffer* GLRenderer::CreateIB(unsigned long size, unsigned long stride, unsigned long flags) const
	{
		// Création du buffer
		unsigned int IndexBuffer = 0;
		glGenBuffers(1, &IndexBuffer);

		// Remplissage
		glBindBuffer(GL_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * stride, NULL, RGLEnum::BufferFlags(flags));

		return new GLIndexBuffer(size, IndexBuffer);
	}

	Declaration* GLRenderer::CreateDeclaration(const TDeclarationElement* elt, std::size_t count) const
	{
		// Création de la déclaration OpenGL
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
				// Position
				case ELT_USAGE_POSITION :
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_VERTEX_ARRAY);
					//glVertexPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Normale
				case ELT_USAGE_NORMAL :
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_NORMAL_ARRAY);
					//glNormalPointer(Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Couleur diffuse
				case ELT_USAGE_DIFFUSE :
					glEnableVertexAttribArray(2);
					glVertexAttribPointer(2, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_COLOR_ARRAY);
					//glColorPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Coordonnées de texture 0
				case ELT_USAGE_TEXCOORD0 :
					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(3);
					glVertexAttribPointer(3, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					//glTexCoordPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Coordonnées de texture 1
				case ELT_USAGE_TEXCOORD1 :
					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(4);
					glVertexAttribPointer(4, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					
					//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					//glTexCoordPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Coordonnées de texture 2
				case ELT_USAGE_TEXCOORD2 :
					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glClientActiveTexture(GL_TEXTURE0);
					glEnableVertexAttribArray(5);
					glVertexAttribPointer(5, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					//glTexCoordPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					break;

				// Coordonnées de texture 3
				case ELT_USAGE_TEXCOORD3 :
					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glClientActiveTexture(GL_TEXTURE0);
					glVertexAttribPointer(6, Size[i->type], Type[i->type], GL_FALSE, stride, BUFFER_OFFSET(i->offset + minVertex * stride));
					//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					//glTexCoordPointer(Size[i->type], Type[i->type], stride, BUFFER_OFFSET(i->offset + minVertex * stride));
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
		glColor4f(1, 1, 1, 1);
		
		for (int i = 0; i < 4; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glDisable(GL_TEXTURE_2D);
		}

		m_CurrentDeclaration = static_cast<const GLDeclaration*>(declaration);
	}

	void GLRenderer::DrawPrimitives(TPrimitiveType type, unsigned long firstVertex, unsigned long count) const
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

	void GLRenderer::DrawIndexedPrimitives(TPrimitiveType type, unsigned long firstIndex, unsigned long count) const
	{
		unsigned long indicesType = (m_IndexStride == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
		const void*   offset      = BUFFER_OFFSET(firstIndex * m_IndexStride);
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		switch (type)
		{
			case PT_TRIANGLELIST :  glDrawElements(GL_TRIANGLES,      count, indicesType, offset); break;
			case PT_TRIANGLESTRIP : glDrawElements(GL_TRIANGLE_STRIP, count, indicesType, offset); break;
			case PT_TRIANGLEFAN :   glDrawElements(GL_TRIANGLE_FAN,   count, indicesType, offset); break;
			case PT_LINELIST :      glDrawElements(GL_LINES,          count, indicesType, offset); break; 
			case PT_LINESTRIP :     glDrawElements(GL_LINE_STRIP,     count, indicesType, offset); break;
			case PT_POINTLIST :     glDrawElements(GL_POINTS,         count,     indicesType, offset); break;
			case PT_PATCHLIST :     glDrawElements(GL_PATCHES,        count*3,     indicesType, offset); break;
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

	void GLRenderer::SetTexture(uint32 unit, const TextureBase* texture) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		const GLTexture* oGLTexture = static_cast<const GLTexture*>(texture);

		if (texture)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, oGLTexture->GetGLTexture());
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	TextureBase* GLRenderer::CreateTexture(const ivec2& size, TPixelFormat format, unsigned long flags) const
	{
		uint32 texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		int nbMipmaps = flags & TEX_NOMIPMAP ? 0 : GetNbMipLevels(size.x, size.y);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, nbMipmaps);

		if ((nbMipmaps > 0) && (HasCapability(CAP_HW_MIPMAPPING)))
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

		int width  = size.x;
		int height = size.y;
		for (int i = 0; i <= nbMipmaps; ++i)
		{
			glTexImage2D(GL_TEXTURE_2D, i, RGLEnum::Get(format).Internal, width, height, 0, RGLEnum::Get(format)._Format, GL_UNSIGNED_BYTE, NULL);

			if (width > 1)  width  /= 2;
			if (height > 1) height /= 2;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		return new GLTexture(size, format, nbMipmaps > 0, HasCapability(CAP_HW_MIPMAPPING), texture);
	}

	void GLRenderer::SetupAlphaBlending(TBlend src, TBlend dest) const
	{
		glBlendFunc(RGLEnum::Get(src), RGLEnum::Get(dest));
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
			case RENDER_TRANSPARENT:
			{
				if(value)
					glEnable(GL_ALPHA_TEST);
				else glDisable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GEQUAL,0.7f);
				break;
			}
			case RENDER_TEXTURE0:
			case RENDER_TEXTURE1:
			case RENDER_TEXTURE2:
			case RENDER_TEXTURE3:
			case RENDER_TEXTURE4:
			case RENDER_TEXTURE5:
				if(value)
					m_RenderFlags |= 1 << (param - RENDER_TEXTURE0 + 1);
				else 
					m_RenderFlags &= ~(1 << (param - RENDER_TEXTURE0 + 1));
				if(m_CurrentProgram)
					m_CurrentProgram->SetParameter("RenderFlags",(int)m_RenderFlags);
				else m_Pipeline.SetParameter("RenderFlags",(int)m_RenderFlags);
				break;
			case RENDER_CLIP_PLANE0:
			case RENDER_CLIP_PLANE1:
			case RENDER_CLIP_PLANE2:
			case RENDER_CLIP_PLANE3:
			case RENDER_CLIP_PLANE4:
			case RENDER_CLIP_PLANE5:
				if(value)
					glEnable(GL_CLIP_PLANE0+param - RENDER_CLIP_PLANE0);
				else
					glDisable(GL_CLIP_PLANE0+param - RENDER_CLIP_PLANE0);

				break;
			default :
			{
				if (value)
					glEnable(RGLEnum::Get(param));
				else
					glDisable(RGLEnum::Get(param));
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
		uint32 shader = glCreateShader(RGLEnum::Get(type));
		const char* src = source.c_str();
		glShaderSource(shader, 1, (const char**)&src, NULL);
    
		glCompileShader(shader);
    
		int32 compile_status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
		if(compile_status != GL_TRUE)
		{
			int32 logsize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        
			char *log = new char[logsize+1];
			memset(log, '\0', logsize + 1);
        
			glGetShaderInfoLog(shader, logsize, &logsize, log);
			//Logger::Log(LOGNORMAL, "Impossible de compiler le shader :\n%s\n", log);
       
			delete log;
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

		if(link != GL_TRUE)
		{
			int32 errorsize;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &errorsize);
	
			char* error = new char[errorsize + 1];

			glGetProgramInfoLog(id, errorsize, &errorsize, error);
			error[errorsize] = '\0';

			delete[] error;
			return NULL;
		}

		return new GLShaderProgram(id);
	}

	BaseShaderProgram* GLRenderer::getPipeline()
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

	void GLRenderer::SetCurrentProgram(BaseShaderProgram* prog)
	{
		m_CurrentProgram = prog;
		if(m_CurrentProgram)
		{
			m_CurrentProgram->Use(true);
		}
		else m_Pipeline.Enable();

		_LoadMatrix(MAT_PROJECTION,m_MatProjection);
		_LoadMatrix(MAT_VIEW,m_MatView);
	}
}

