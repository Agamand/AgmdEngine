/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\GUI\ASlider.h>
#include <Core\Driver.h>
#include <Core/MatStack.h>

namespace Agmd
{
    #define COIN 30

    ASlider::ASlider( AWidget* parent) :
    AWidget(parent),
    hold(false)
    {
        BuildSlider();
        m_Texture.CreateFromFile("Texture/slider.png",PXF_A8R8G8B8);
        m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/GUI/slider.glsl");
    }

    ASlider::~ASlider()
    {}


    a_uint32 ASlider::OnClick(ivec2& pos_mouse, a_uint32 mouseState)
    {
        if(!In(pos_mouse))
            return 0;
        hold = mouseState & MOUSE_LEFT;

        return 1;
    }


    a_uint32 ASlider::OnMouseOver()
    {
        return 0;
    }

    a_uint32 ASlider::OnMouseMove(ivec2& pos_diff, a_uint32 mouseState)
    {
        if(!hold)
            return 0;

        hold = mouseState & MOUSE_LEFT;
        if(hold)
        {
            float displacement = (float)pos_diff.x/(float)m_vSize.x;
            SetCursor(displacement);
        }
        return 1;
    }

    a_uint32 ASlider::OnKey(char key)
    {
        return 0;
    }

    void ASlider::OnSizeChanged()
    {
        TVertex* vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

        for(a_uint32 i = 0; i < 4; i++)
            for(a_uint32 j  = 0; j < 4; j++) 
                vertices[i*4+j].Position = vec3(0.0f+COIN*((i+1)/2)+m_vSize.x*((i)/2),0.0f+COIN*((j+1)/2)+m_vSize.y*((j)/2),0.0f);

        m_VertexBuffer.Unlock();
    }

    void ASlider::OnPosChanged()
    {
    }

    void ASlider::Draw() const
    {
        Driver &render = Driver::Get();
        render.SetCurrentProgram(m_Program);
        mat4 modelMatrix = translate(mat4(1.0f),vec3(m_vAbsolutePosition,0.0f));
        MatStack::push(modelMatrix);
        render.SetDeclaration(m_Declaration);
        render.SetVertexBuffer(0, m_VertexBuffer);
        render.SetIndexBuffer(m_IndexBuffer);

        render.SetTexture(0, m_Texture.GetTexture());
        render.SetTextureFlag(TEXTURE_UNIT_0);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 0, 24);

        render.SetTexture(1, m_Texture.GetTexture());
        render.SetTextureFlag(TEXTURE_UNIT_1);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 24, 12);

        render.SetTexture(2, m_Texture.GetTexture());
        render.SetTextureFlag(TEXTURE_UNIT_2);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 36, 12);


        if(m_Font.GetTexture())
        {
            render.GetCurrentProgram()->SetParameter("u_size",(vec2)m_vSize);
            render.SetTexture(3, m_Font.GetTexture());
            render.SetTextureFlag(TEXTURE_UNIT_3);
        }else render.SetTextureFlag(0);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 48, 6);
        render.SetCurrentProgram(NULL);
        MatStack::pop();
    }

    
    #define SELECT(i, size) ((i) >= ((int)size) ? (i)%((int)size) : (i))

    struct texcoord
    {
        vec2 t0;
        vec2 t1;
        vec2 t2;
        vec2 t3;
    };

    void ASlider::BuildSlider()
    {
        /*                 
             _____________
           1|_|_________|_|2_
            | |         | | ^
            | |         | | | y
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
            {vec2(0.0f,1.0f),    vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.0f,0.75f),    vec2(0.0f,0.0f),  vec2(1.0f,0.75f), vec2(0.0f,0.0f)},
            {vec2(0.25f,1.0f),    vec2(0.0f,0.0f),  vec2(0.0f,0.75f), vec2(0.0f,0.0f)},
            {vec2(0.25f,0.75f),    vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.25f,1.0f),    vec2(0.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.25f,0.75f),    vec2(0.0f,0.5f),  vec2(1.0f,0.5f),  vec2(0.0f,0.0f)},
            {vec2(0.5f,1.0f),    vec2(0.0f,0.5f),  vec2(0.0f,0.5f),  vec2(0.0f,1.0f)},
            {vec2(0.5f,0.75f),    vec2(0.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.5f,1.0f),    vec2(1.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.5f,0.75f),    vec2(1.0f,0.5f),  vec2(0.0f,0.5f),  vec2(1.0f,0.0f)},
            {vec2(0.75f,1.0f),    vec2(1.0f,0.5f),  vec2(1.0f,0.5f),  vec2(1.0f,1.0f)},
            {vec2(0.75f,0.75f),    vec2(1.0f,0.75f), vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.75f,1.0f),    vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)},
            {vec2(0.75f,0.75f),    vec2(0.0f,0.0f),  vec2(0.0f,0.75f), vec2(0.0f,0.0f)},
            {vec2(1.0f,1.0f),    vec2(0.0f,0.0f),  vec2(1.0f,0.75f), vec2(0.0f,0.0f)},
            {vec2(1.0f,0.75f),    vec2(0.0f,0.0f),  vec2(0.0f,0.0f),  vec2(0.0f,0.0f)}
        };

        m_Declaration = Driver::Get().CreateVertexDeclaration(Decl);

        std::vector<TVertex> vertices;
        std::vector<TIndex> indices;

        TVertex vertex;

        vertex.Diffuse = -1;
        
        for(a_uint32 i = 0; i < 4; i++)
            for(a_uint32 j  = 0; j < 4; j++)
            {
                vertex.Position = vec3(0.0f+COIN*((i+1)/2)+m_vSize.x*((i)/2),0.0f+COIN*((j+1)/2)+m_vSize.y*((j)/2),0.0f);
                vertex.TexCoords0 = texc[j+i*4].t0;
                vertices.push_back(vertex);
            }

        indices.push_back(0);
        indices.push_back(4);
        indices.push_back(1);
        indices.push_back(1);
        indices.push_back(4);
        indices.push_back(5);

        indices.push_back(8);
        indices.push_back(12);
        indices.push_back(9);
        indices.push_back(9);
        indices.push_back(12);
        indices.push_back(13);

        indices.push_back(2);
        indices.push_back(6);
        indices.push_back(3);
        indices.push_back(3);
        indices.push_back(6);
        indices.push_back(7);

        indices.push_back(10);
        indices.push_back(14);
        indices.push_back(11);
        indices.push_back(11);
        indices.push_back(14);
        indices.push_back(15);

        indices.push_back(4);
        indices.push_back(8);
        indices.push_back(5);
        indices.push_back(5);
        indices.push_back(8);
        indices.push_back(9);

        indices.push_back(6);
        indices.push_back(10);
        indices.push_back(7);
        indices.push_back(7);
        indices.push_back(10);
        indices.push_back(11);

        indices.push_back(1);
        indices.push_back(5);
        indices.push_back(2);
        indices.push_back(2);
        indices.push_back(5);
        indices.push_back(6);

        indices.push_back(9);
        indices.push_back(13);
        indices.push_back(10);
        indices.push_back(10);
        indices.push_back(13);
        indices.push_back(14);

        indices.push_back(5);
        indices.push_back(9);
        indices.push_back(6);
        indices.push_back(6);
        indices.push_back(9);
        indices.push_back(10);

        m_VertexBuffer = Driver::Get().CreateVertexBuffer<TVertex>(vertices.size(), BUF_DYNAMIC,&vertices[0]);
        m_IndexBuffer = Driver::Get().CreateIndexBuffer((int)indices.size(), 0, &indices[0]);

    }

    bool ASlider::In(ivec2& pos)
    {

        if(pos.x < (m_vAbsolutePosition.x) || pos.y < (m_vAbsolutePosition.y) || pos.x > (m_vAbsolutePosition.x+m_vSize.x) || pos.y > (m_vAbsolutePosition.y+m_vSize.y) )
            return false;

        return true;
    }

    void ASlider::SetCursor(float value)
    {
        if(value > 1.0f)
            m_cursor = 1.0f;
        else if(value < 0.0f)
            m_cursor = 0.0f;
        else m_cursor = value;
    }
}