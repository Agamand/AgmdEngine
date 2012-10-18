#include <Core\SkyBox.h>
#include <Core\Renderer.h>
#include <Core\MediaManager.h>

namespace Agmd
{

	SkyBox::SkyBox(float size) :
	Sky(size)
	{
		Generate();
		m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/skybox.glsl");
	}

	SkyBox::~SkyBox()
	{}

	void SkyBox::Render() const
	{

		mat4 modelMatrix = mat4(1.0f);


		Renderer::Get().SetCurrentProgram(m_Program);

		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().SetVertexBuffer(0,m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);

		for(int i = 0; i < 6; i++)
		{
			if(m_Texture[i].GetTexture())
			{
				Renderer::Get().Enable(TRenderParameter(RENDER_TEXTURE0),true);
				Renderer::Get().SetTexture(0,m_Texture[i].GetTexture());
			}
			else Renderer::Get().Enable(TRenderParameter(RENDER_TEXTURE0),false);

			Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST,6*i,6);
		}

		Renderer::Get().SetCurrentProgram(NULL);
	}

	void SkyBox::SetTexture(Texture tex, uint32 index)
	{
		m_Texture[index] = tex;
	}
	
	void SkyBox::Generate()
	{
		TVertex vertex[] = 
		{	
			//Z+
			{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},
			//Z-
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,1)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},
			//X-
			{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y+
			{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//X+
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y-
			{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)}
		};

		std::vector<TIndex> indices;

		for(uint32 i = 0; i < 6; i++)
		{
			indices.push_back(1+i*4);
			indices.push_back(2+i*4);
			indices.push_back(0+i*4);

			indices.push_back(1+i*4);
			indices.push_back(3+i*4);
			indices.push_back(2+i*4);
		}

		TDeclarationElement Elements[] =
		{
			{0, ELT_USAGE_POSITION,		ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_TEXCOORD0,	ELT_TYPE_FLOAT2}
		};

		m_Declaration = Renderer::Get().CreateVertexDeclaration(Elements);

		m_VertexBuffer = Renderer::Get().CreateVertexBuffer(4*6,0,vertex);
		m_IndexBuffer = Renderer::Get().CreateIndexBuffer(6*6,0,&indices[0]);
	}

}
