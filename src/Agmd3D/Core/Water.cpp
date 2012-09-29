#include <Core/Water.h>
#include <Core/Renderer.h>
#include <Core/MediaManager.h>
#include <Core/Scene.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

namespace Agmd
{

	Water::Water(ivec2 _size, ivec2 _poly) :
	Model(),
	size(_size),
	n_poly(_poly)
	{
		m_PrimitiveType = PT_TRIANGLELIST;
		generate();
		m_program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/water.glsl");
		//m_program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/waterTexture.glsl");
		fbo[0] = Renderer::Get().CreateFrameBuffer();
		fbo[1] = Renderer::Get().CreateFrameBuffer();
		ivec2 size = Renderer::Get().GetScreen();
		m_RefractionMap = Renderer::Get().CreateTexture(size,  PXF_A8R8G8B8);
		m_ReflectionMap = Renderer::Get().CreateTexture(size,  PXF_A8R8G8B8);
		m_MirrorTex = Renderer::Get().CreateRenderBuffer(size, PXF_DEPTH);
		fbo[0]->setTexture(m_RefractionMap,COLOR_ATTACHMENT);
		fbo[1]->setTexture(m_ReflectionMap,COLOR_ATTACHMENT);
		fbo[1]->setRender(m_MirrorTex, DEPTH_ATTACHMENT);


	}

	Water::~Water()
	{

	}

	void Water::generate()
	{

		std::vector<TVertex> vertices;
		std::vector<TIndex> index;

		float x_2 = size.x/2.0f;
		float y_2 = size.y/2.0f;

		vec2 polysize = vec2(size);
		polysize /= n_poly;

		for(int i = 0; i <= n_poly.x; i++)
		{
			for(int j = 0; j <= n_poly.y; j++)
			{
				TVertex vertex;
				vertex.color = -1;
				vertex.normal = vec3(0.0f,0.0f,1.0f);
				vertex.position = vec3(i*polysize.x-x_2,j*polysize.y-y_2,0.0f);
				vertex.texCoords = vec2(i/((float)n_poly.x),j/((float)n_poly.y));
				vertex.boneCount = 0;
				vertices.push_back(vertex);
			}
		}

		uint32 npoly = n_poly.x*n_poly.y;


		for(int i = 0; i < n_poly.x;i++)
		{
			for(int j = 0; j < n_poly.y; j++)
			{
				int _i = SELECT(i+1, n_poly.x+1), _j = SELECT(j+1, n_poly.y+1);
				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);

				index.push_back(i*(n_poly.y+1)+j);
				index.push_back(_i*(n_poly.y+1)+_j);
				index.push_back(i*(n_poly.y+1)+_j);
			}
		}

		Generate(G_TANGENT,&vertices[0], vertices.size(), &index[0], index.size());

		TDeclarationElement elements[] =
		{
			{0, ELT_USAGE_POSITION,  ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_NORMAL,    ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_DIFFUSE,   ELT_TYPE_COLOR},
			{0, ELT_USAGE_TEXCOORD0, ELT_TYPE_FLOAT2},
			{0, ELT_USAGE_TANGENT,   ELT_TYPE_FLOAT4}
		};
		m_Declaration = Renderer::Get().CreateVertexDeclaration(elements);

		m_VertexBuffer = Renderer::Get().CreateVertexBuffer(vertices.size(), 0, &vertices[0]);
		m_IndexBuffer  = Renderer::Get().CreateIndexBuffer(index.size(), 0, &index[0]);


	}

	void Water::Render() const
	{
		GenerateRefraction();
		GenerateReflection();

		mat4 modelMatrix = m_position.ModelMatrix();
		mat3 normalMatrix = mat3(modelMatrix);

		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().LoadMatrix(MAT_NORMAL, normalMatrix);

	/*	Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);
		Renderer::Get().DrawIndexedPrimitives(m_PrimitiveType, 0, m_IndexBuffer.GetCount());*/
	}

	void Water::GenerateRefraction() const
	{
		fbo[0]->Clear();
		fbo[0]->Bind();

		mat4 view = Renderer::Get().GetMatView();
		vec4 normal = view*vec4(0,0,-1,0);
		vec4 pos = view*vec4(m_position.m_position,1.0);

		double plane[] = {normal.x,normal.y,normal.z,normal.x*pos.x + normal.y*pos.y + normal.z*pos.z};
		Renderer::Get().setClipPlane(0,plane);
		
		//Renderer::Get().Enable(RENDER_CLIP_PLANE0,true);
		if(scene)
			scene->Draw(SC_DRAW_MODEL | SC_DRAW_TERRAIN);
		Renderer::Get().Enable(RENDER_CLIP_PLANE0,false);
		fbo[0]->UnBind();
	}

	void Water::GenerateReflection() const
	{
		fbo[1]->Clear();
		fbo[1]->Bind();


		mat4 view = Renderer::Get().GetMatView();
		view = scale(view,vec3(1,1,-1));
		vec4 normal = view*vec4(0,0,1,0);
		vec4 pos = view*vec4(m_position.m_position,1.0);

		double plane[] = {normal.x,normal.y,normal.z,normal.x*pos.x + normal.y*pos.y + normal.z*pos.z};
		Renderer::Get().setClipPlane(0,plane);
		Renderer::Get().SetMatView(view);


		Renderer::Get().Enable(RENDER_CLIP_PLANE0,true);

		if(scene)
			scene->Draw(SC_DRAW_MODEL | SC_DRAW_TERRAIN);

		Renderer::Get().Enable(RENDER_CLIP_PLANE0,false);
		fbo[1]->UnBind();
		view = scale(view,vec3(1,1,-1));
		Renderer::Get().SetMatView(view);
	}

	void Water::SetScene(Scene* sc)
	{
		scene = sc;
	}

}
