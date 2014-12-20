/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Model/SkyBox.h>
#include <Core/Driver.h>
#include <Core/MediaManager.h>
#include <Core/MatStack.h>
#include <Core/Shader/BaseShaderProgram.h>

namespace Agmd
{

    SkyBox::SkyBox()
    {
        m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/skybox.glsl");
		Generate();
    }

    SkyBox::~SkyBox()
    {}

	

    void SkyBox::Render() const
    {
		Draw();
    }

    void SkyBox::Draw() const
    {
		Driver& render = Driver::Get();
		render.SetCurrentProgram(m_Program);
		//render.SetCullFace(0);
		render.SetCurrentTransform(NULL);
		Driver::Get().SetDeclaration(m_Declaration);
		Driver::Get().SetVertexBuffer(0,m_VertexBuffer);
		Driver::Get().SetIndexBuffer(m_IndexBuffer);
		Driver::Get().SetTexture(0,m_Texture.GetTexture());
		Driver::Get().DrawIndexedPrimitives(PT_TRIANGLELIST,0,36);

		render.SetCurrentProgram(NULL);
    }

    void SkyBox::SetTexture(Texture tex)
    {
        m_Texture = tex;
    }

	void SkyBox::Generate()
	{
		TVertex vertex[] = 
		{    
			//Z+
			{vec3(1.f,1.f,1.f)},{vec3(1.f,-1.f,1.f)},{vec3(-1.f,1.f,1.f)},{vec3(-1.f,-1.f,1.f)},
			//Z-
			{vec3(-1.f,-1.f,-1.f),},{vec3(1.f,-1.f,-1.f)},{vec3(-1.f,1.f,-1.f)},{vec3(1.f,1.f,-1.f)},
			//X-
			{vec3(-1.f,-1.f,-1.f)},{vec3(-1.f,1.f,-1.f)},{vec3(-1.f,-1.f,1.f)},{vec3(-1.f,1.f,1.f)},
			//Y+
			{vec3(-1.f,1.f,-1.f)},{vec3(1.f,1.f,-1.f)},{vec3(-1.f,1.f,1.f)},{vec3(1.f,1.f,1.f)},
			//X+
			{vec3(1.f,1.f,-1.f)},{vec3(1.f,-1.f,-1.f)},{vec3(1.f,1.f,1.f)},{vec3(1.f,-1.f,1.f)},
			//Y-
			{vec3(1.f,-1.f,-1.f)},{vec3(-1.f,-1.f,-1.f)},{vec3(1.f,-1.f,1.f)},{vec3(-1.f,-1.f,1.f)}
		};

		a_vector<TIndex> indices;

		for(a_uint32 i = 0; i < 6; i++)
		{
			indices.push_back(1+i*4);
			indices.push_back(0+i*4);
			indices.push_back(2+i*4);

			indices.push_back(1+i*4);
			indices.push_back(2+i*4);
			indices.push_back(3+i*4);
		}

		TDeclarationElement Elements[] =
		{
			{0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT3}
		};

		m_Declaration = Driver::Get().CreateVertexDeclaration(Elements);

		m_VertexBuffer = Driver::Get().CreateVertexBuffer(4*6,0,vertex);
		m_IndexBuffer = Driver::Get().CreateIndexBuffer(6*6,0,&indices[0]);
	}

}
