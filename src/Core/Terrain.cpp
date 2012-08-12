#include <Core\Terrain.h>
#include <Core\Renderer.h>
#include <vector>

#define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

namespace Agmd
{

	Terrain::Terrain(ivec2 _size, ivec2 _poly, std::string diffuse, std::string _heightmap) :
	Model(),
	size(_size),
	n_poly(_poly)
	{
		m_PrimitiveType = PT_TRIANGLELIST;
		if(diffuse.length() != 0)
			m_Texture.CreateFromFile(diffuse, PXF_A8R8G8B8);
		if(_heightmap.length() != 0)
			heightmap.CreateFromFile(_heightmap, PXF_A8R8G8B8);
		generate();
	}

	Terrain::~Terrain()
	{

	}

	void Terrain::generate()
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

	void Terrain::Render() const
	{
		mat4 modelMatrix = m_rot*m_pos;
		mat3 normalMatrix = mat3(modelMatrix);
		Renderer::Get().LoadMatrix(MAT_MODEL,modelMatrix);
		Renderer::Get().LoadMatrix(MAT_NORMAL, normalMatrix);

		if(m_Texture.GetTexture())
		{
			Renderer::Get().Enable(RENDER_TEXTURE0,true);
			Renderer::Get().SetTexture(0, m_Texture.GetTexture());
		}else Renderer::Get().Enable(RENDER_TEXTURE0,false);

		if(heightmap.GetTexture())
		{
			Renderer::Get().Enable(RENDER_TEXTURE5,true);
			Renderer::Get().SetTexture(5, heightmap.GetTexture());
		}else Renderer::Get().Enable(RENDER_TEXTURE5,false);

		Renderer::Get().SetDeclaration(m_Declaration);
		Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
		Renderer::Get().SetIndexBuffer(m_IndexBuffer);
		Renderer::Get().DrawIndexedPrimitives(m_PrimitiveType, 0, m_IndexBuffer.GetCount());
	}

}
