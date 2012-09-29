#include <Core\GUI\AWindow.h>
#include <Core\Renderer.h>

namespace Agmd
{
	#define COIN 30

	AWindow::AWindow( TextureBase* font, AWidget* parent) :
	AWidget(parent),
	hold(false),
	m_Font(font)
	{
		BuildWindow();
		m_Texture.CreateFromFile("Gui.png",PXF_A8R8G8B8);
		m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/window.glsl");
	}

	AWindow::~AWindow()
	{}


	uint32 AWindow::OnClick(ivec2 pos_mouse, uint32 mouseState)
	{
		if(!In(pos_mouse))
			return 0;
		hold = mouseState & MOUSE_LEFT;

		if(pos_mouse.x > (m_vAbsolutePosition.x+m_vSize.x+COIN) && pos_mouse.y > (m_vAbsolutePosition.y+m_vSize.y+COIN))
			extend = true;
		else extend = false;
		return 1;
	}

	uint32 AWindow::OnMouseOver()
	{
		return 0;
	}

	uint32 AWindow::OnMouseMove(ivec2 pos_diff, uint32 mouseState)
	{
		if(!hold)
			return 1;

		hold = mouseState & MOUSE_LEFT;
		if(hold)
		{
			if(!extend)
				SetPosition(m_vPosition-pos_diff);
			else 
				SetSize(m_vSize-pos_diff);
		}
		return 0;
	}

	uint32 AWindow::OnKey(char key)
	{
		return 0;
	}

	

	void AWindow::OnSizeChanged()
	{
		TVertex* vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

		for(uint32 i = 0; i < 4; i++)
			for(uint32 j  = 0; j < 4; j++) 
				vertices[i*4+j].Position = vec3(0.0f+COIN*((i+1)/2)+m_vSize.x*((i)/2),0.0f+COIN*((j+1)/2)+m_vSize.y*((j)/2),0.0f);

		m_VertexBuffer.Unlock();
	}

	void AWindow::OnPosChanged()
	{
	}

	void AWindow::Draw() const
	{
		Renderer::Get().SetCurrentProgram(m_Program);
		mat4 modelMatrix = translate(mat4(1.0f),vec3(m_vAbsolutePosition,0.0f));
		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().Enable(RENDER_TEXTURE0,false);
		Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);

		Renderer::Get().Enable(RENDER_TEXTURE1, false);
		Renderer::Get().Enable(RENDER_TEXTURE2, false);
		Renderer::Get().Enable(RENDER_TEXTURE3, false);

		Renderer::Get().SetTexture(0, m_Texture.GetTexture());
		Renderer::Get().Enable(RENDER_TEXTURE0, true);
		Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 0, 24);
		Renderer::Get().Enable(RENDER_TEXTURE0, false);

		Renderer::Get().SetTexture(1, m_Texture.GetTexture());
		Renderer::Get().Enable(RENDER_TEXTURE1, true);
		Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 24, 12);
		Renderer::Get().Enable(RENDER_TEXTURE1, false);

		Renderer::Get().SetTexture(2, m_Texture.GetTexture());
		Renderer::Get().Enable(RENDER_TEXTURE2, true);
		Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 36, 12);
		Renderer::Get().Enable(RENDER_TEXTURE2, false);

		if(m_Font)
		{
			Renderer::Get().SetTexture(3, m_Font);
			Renderer::Get().Enable(RENDER_TEXTURE3, true);
		}
		Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 48, 6);
		Renderer::Get().Enable(RENDER_TEXTURE3, false);
		Renderer::Get().SetCurrentProgram(NULL);
	}

	
	#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

	struct texcoord
	{
		vec2 t0;
		vec2 t1;
		vec2 t2;
		vec2 t3;
	};

	void AWindow::BuildWindow()
	{
		/*			     
			 _____________
		   1|_|_________|_|2_
			| |         | | ^
			| |         | |	| y
			|_|_________|_| v
		   3|_|_________|_|4
			  |<------->|<>|
				  x      w = 5
		*/
		TDeclarationElement Decl[] =
		{
			{0, ELT_USAGE_POSITION,  ELT_TYPE_FLOAT3},
			{0, ELT_USAGE_DIFFUSE,   ELT_TYPE_COLOR},
			{0, ELT_USAGE_TEXCOORD0, ELT_TYPE_FLOAT2},
			{0, ELT_USAGE_TEXCOORD1, ELT_TYPE_FLOAT2},
			{0, ELT_USAGE_TEXCOORD2, ELT_TYPE_FLOAT2},
			{0, ELT_USAGE_TEXCOORD3, ELT_TYPE_FLOAT2}
		};

		static texcoord texc[] =
		{
			{vec2(0.0f,1.0f),	vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.0f,0.75f),	vec2(0.0f,0.0f),  vec2(1.0f,0.75f), vec2(0.0f,0.0f)},
			{vec2(0.25f,1.0f),	vec2(0.0f,0.0f),  vec2(0.0f,0.75f), vec2(0.0f,0.0f)},
			{vec2(0.25f,0.75f),	vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.25f,1.0f),	vec2(0.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.25f,0.75f),	vec2(0.0f,0.5f),  vec2(1.0f,0.5f),  vec2(0.0f,1.0f)},
			{vec2(0.5f,1.0f),	vec2(0.0f,0.5f),  vec2(0.0f,0.5f),  vec2(0.0f,0.0f)},
			{vec2(0.5f,0.75f),	vec2(0.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.5f,1.0f),	vec2(1.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.5f,0.75f),	vec2(1.0f,0.5f),  vec2(0.0f,0.5f),  vec2(1.0f,1.0f)},
			{vec2(0.75f,1.0f),	vec2(1.0f,0.5f),  vec2(1.0f,0.5f),  vec2(1.0f,0.0f)},
			{vec2(0.75f,0.75f),	vec2(1.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.75f,1.0f),	vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
			{vec2(0.75f,0.75f),	vec2(0.0f,0.0f),  vec2(0.0f,0.75f), vec2(0.0f,0.0f)},
			{vec2(1.0f,1.0f),	vec2(0.0f,0.0f),  vec2(1.0f,0.75f), vec2(0.0f,0.0f)},
			{vec2(1.0f,0.75f),	vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)}
		};

		m_Declaration = Renderer::Get().CreateVertexDeclaration(Decl);

		std::vector<TVertex> vertices;
		std::vector<TIndex> indices;

		TVertex vertex;

		vertex.Diffuse = -1;
		
		for(uint32 i = 0; i < 4; i++)
			for(uint32 j  = 0; j < 4; j++)
			{
				vertex.Position = vec3(0.0f+COIN*((i+1)/2)+m_vSize.x*((i)/2),0.0f+COIN*((j+1)/2)+m_vSize.y*((j)/2),0.0f);
				vertex.TexCoords0 = texc[j+i*4].t0;
				vertex.TexCoords1 = texc[j+i*4].t1;
				vertex.TexCoords2 = texc[j+i*4].t2;
				vertex.TexCoords3 = texc[j+i*4].t3;
				vertices.push_back(vertex);
			}

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(4);
		indices.push_back(1);
		indices.push_back(5);
		indices.push_back(4);

		indices.push_back(8);
		indices.push_back(9);
		indices.push_back(12);
		indices.push_back(9);
		indices.push_back(13);
		indices.push_back(12);

		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(6);
		indices.push_back(3);
		indices.push_back(7);
		indices.push_back(6);

		indices.push_back(10);
		indices.push_back(11);
		indices.push_back(14);
		indices.push_back(11);
		indices.push_back(15);
		indices.push_back(14);

		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(8);
		indices.push_back(5);
		indices.push_back(8);
		indices.push_back(9);

		indices.push_back(6);
		indices.push_back(7);
		indices.push_back(10);
		indices.push_back(7);
		indices.push_back(11);
		indices.push_back(10);

		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(5);
		indices.push_back(2);
		indices.push_back(6);
		indices.push_back(5);

		indices.push_back(9);
		indices.push_back(10);
		indices.push_back(13);
		indices.push_back(10);
		indices.push_back(13);
		indices.push_back(14);

		indices.push_back(5);
		indices.push_back(6);
		indices.push_back(9);
		indices.push_back(6);
		indices.push_back(9);
		indices.push_back(10);

		m_VertexBuffer = Renderer::Get().CreateVertexBuffer<TVertex>(vertices.size(), BUF_DYNAMIC,&vertices[0]);
		m_IndexBuffer = Renderer::Get().CreateIndexBuffer((int)indices.size(), 0, &indices[0]);

	}

	bool AWindow::In(ivec2 pos)
	{

		if(pos.x < (m_vAbsolutePosition.x) || pos.y < (m_vAbsolutePosition.y) || pos.x > (m_vAbsolutePosition.x+m_vSize.x+COIN*2) || pos.y > (m_vAbsolutePosition.y+m_vSize.y+COIN*2) )
			return false;

		return true;
	}
}