#include <Core\SkyBox.h>
#include <Core\Renderer.h>

namespace Agmd
{

	SkyBox::SkyBox(float size) :
	Sky(size)
	{
		Generate();
	}

	SkyBox::~SkyBox()
	{}

	void SkyBox::Render() const
	{

	}

	void SkyBox::SetTexture(Texture tex, uint32 index)
	{
		//Renderer::Get().
	}
	
	void SkyBox::Generate()
	{
		TVertex vertex[] = 
		{	
			//Z+
			{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},
			//Z-
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,1)},
			//X-
			{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y+
			{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//X+
			{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,1)},
			//Y-
			{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)}
		};

		std::vector<TIndex> indices;

		for(uint32 i = 0; i < 6; i++)
		{
			indices.push_back(0);
			indices.push_back(0);
			indices.push_back(0);

			indices.push_back(0);
			indices.push_back(0);
			indices.push_back(0);
		}








		//m_VertexBuffer = Renderer::Get().CreateVertexBuffer(
	}

}