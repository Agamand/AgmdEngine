/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/SceneObject/SkyBox.h>
#include <Core/Renderer.h>
#include <Core/MediaManager.h>
#include <Core/MatStack.h>
#include <Core/Shader/BaseShaderProgram.h>

namespace Agmd
{

    SkyBox::SkyBox(float size)
    {
        Generate();
        m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/skybox.glsl");
    }

    SkyBox::~SkyBox()
    {}

    void SkyBox::Render() const
    {
        ivec2 screen = Renderer::Get().GetScreen();
        float fov = (float)screen.x/(float)screen.y;
        mat4 proj;
        if(fov > 1.0f)
            proj = ortho(0.0f,1.0f,0.5f-1.0f/fov/2,0.5f+1.0f/fov/2);
        else
            proj = ortho(0.5f-1.0f*fov/2,0.5f+1.0f*fov/2,0.0f,1.0f);

        proj = ortho(0.0f,1.0f,0.0f,1.0f);

        Renderer::Get().SetCurrentProgram(m_Program);
        Renderer::Get().GetCurrentProgram()->SetParameter("u_matProjectionSkybox",proj);
        Draw();
        Renderer::Get().SetCurrentProgram(NULL);
    }

    void SkyBox::Draw() const
    {
        mat4 modelMatrix = mat4(1.0f);
        MatStack::push(modelMatrix);

        Renderer::Get().SetDeclaration(m_Declaration);
        Renderer::Get().SetVertexBuffer(0,m_VertexBuffer);
        Renderer::Get().SetIndexBuffer(m_IndexBuffer);
        Renderer::Get().SetTextureFlag(TEXTURE_UNIT_0);
        Renderer::Get().SetTexture(0,m_Texture.GetTexture());
        Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST,6,6);
/*
        for(int i = 0; i < 6; i++)
        {
            
            Renderer::Get().SetTexture(0,m_Texture[i].GetTexture());
            Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST,6*i,6);
        }*/

        MatStack::pop();
    }

    void SkyBox::SetTexture(Texture tex, a_uint32 index)
    {
        m_Texture = tex;
        //m_Texture[index] = tex;
    }
    
    void SkyBox::Generate()
    {
        TVertex vertex[] =
        {
            {vec3(1.0f,1.0f,0.0f)},
            {vec3(1.0f,0.0f,0.0f)},
            {vec3(0.0f,1.0f,0.0f)},
            {vec3(0.0f,0.0f,0.0f)}
        };

        std::vector<TIndex> indices;

        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(2);

        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);

        TDeclarationElement Elements[] =
        {
            {0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT3}
        };
        m_Declaration = Renderer::Get().CreateVertexDeclaration(Elements);
        m_VertexBuffer = Renderer::Get().CreateVertexBuffer(4,0,vertex);
        m_IndexBuffer = Renderer::Get().CreateIndexBuffer(6,0,&indices[0]);

    /*    TVertex vertex[] = 
        {    
            //Z+
            {vec3(m_fSize/2,m_fSize/2,m_fSize/2),vec2(1,0)},{vec3(m_fSize/2,-m_fSize/2,m_fSize/2),vec2(1,1)},{vec3(-m_fSize/2,m_fSize/2,m_fSize/2),vec2(0,0)},{vec3(-m_fSize/2,-m_fSize/2,m_fSize/2),vec2(0,1)},
            //Z-
            {vec3(-m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(0,0)},{vec3(m_fSize/2,-m_fSize/2,-m_fSize/2),vec2(1,0)},{vec3(-m_fSize/2,m_fSize/2,-m_fSize/2),vec2(0,1)},{vec3(m_fSize/2,m_fSize/2,-m_fSize/2),vec2(1,1)},
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
            indices.push_back(0+i*4);
            indices.push_back(2+i*4);

            indices.push_back(1+i*4);
            indices.push_back(2+i*4);
            indices.push_back(3+i*4);
        }

        TDeclarationElement Elements[] =
        {
            {0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_TEXCOORD0,    ELT_TYPE_FLOAT2}
        };

        m_Declaration = Renderer::Get().CreateVertexDeclaration(Elements);

        m_VertexBuffer = Renderer::Get().CreateVertexBuffer(4*6,0,vertex);
        m_IndexBuffer = Renderer::Get().CreateIndexBuffer(6*6,0,&indices[0]);*/
    }

}
