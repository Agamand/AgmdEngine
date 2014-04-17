/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\GUI\AWindow.h>
#include <Core\Renderer.h>
#include <Core/MatStack.h>

namespace Agmd
{
    #define COIN 30

    AWindow::AWindow( AWidget* parent) :
    AWidget(parent),
    hold(false),
    m_transform(new Transform())
    {
        BuildWindow();
        m_Texture.CreateFromFile("Texture/Gui.png",PXF_A8R8G8B8);
        m_Program = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/window.glsl");
    }

    AWindow::~AWindow()
    {}


    a_uint32 AWindow::OnClick(ivec2& pos_mouse, a_uint32 mouseState)
    {
        if(!In(pos_mouse))
            return 0;
        hold = mouseState & MOUSE_LEFT;

        if(pos_mouse.x > (m_vAbsolutePosition.x+m_vSize.x+COIN) && pos_mouse.y > (m_vAbsolutePosition.y+m_vSize.y+COIN))
            extend = true;
        else extend = false;
        return 1;
    }

    void AWindow::SetBackground(Texture& bg)
    {
        m_Background = bg;
    }

    a_uint32 AWindow::OnMouseOver()
    {
        return 0;
    }

    a_uint32 AWindow::OnMouseMove(ivec2& pos_diff, a_uint32 mouseState)
    {
        if(!hold)
            return 0;

        hold = mouseState & MOUSE_LEFT;
        if(hold)
        {
            if(!extend)
                SetPosition(m_vPosition-pos_diff);
            else 
                SetSize(m_vSize-pos_diff);
        }
        return 1;
    }

    a_uint32 AWindow::OnKey(char key)
    {
        return 0;
    }

    void AWindow::OnSizeChanged()
    {
        TVertex* vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

        for(a_uint32 i = 0; i < 4; i++)
            for(a_uint32 j  = 0; j < 4; j++) 
                vertices[i*4+j].Position = vec3(0.0f+COIN*((i+1)/2)+m_vSize.x*((i)/2),0.0f+COIN*((j+1)/2)+m_vSize.y*((j)/2),0.0f);

        m_VertexBuffer.Unlock();
    }

    void AWindow::OnPosChanged()
    {
		m_transform->SetPosition(vec3(m_vAbsolutePosition,0));
		m_transform->Update(NULL);
    }

    void AWindow::Draw() const
    {
        Driver &render = Driver::Get();
        render.SetCurrentProgram(m_Program);
        render.SetCurrentTransform(m_transform);
        
        render.SetDeclaration(m_Declaration);
        render.SetVertexBuffer(0, m_VertexBuffer);
        render.SetIndexBuffer(m_IndexBuffer);

        render.SetTexture(0, m_Texture.GetTexture());
        render.SetTextureFlag(TEXTURE_UNIT_0);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 0, 24);

        render.SetTextureFlag(TEXTURE_UNIT_1);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 24, 12);

        render.SetTextureFlag(TEXTURE_UNIT_2);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 36, 12);

        if(m_Background.GetTexture())
        {
            render.GetCurrentProgram()->SetParameter("u_size",(vec2)m_vSize);
            render.SetTexture(1, m_Background.GetTexture());
            render.SetTextureFlag(TEXTURE_UNIT_3);
        }else render.SetTextureFlag(0);
        render.DrawIndexedPrimitives(PT_TRIANGLELIST, 48, 6);
        render.SetCurrentProgram(NULL);
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
            | |         | |    | y
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
                vertex.TexCoords1 = texc[j+i*4].t1;
                vertex.TexCoords2 = texc[j+i*4].t2;
                vertex.TexCoords3 = texc[j+i*4].t3;
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

    bool AWindow::In(ivec2& pos)
    {

        if(pos.x < (m_vAbsolutePosition.x) || pos.y < (m_vAbsolutePosition.y) || pos.x > (m_vAbsolutePosition.x+m_vSize.x+COIN*2) || pos.y > (m_vAbsolutePosition.y+m_vSize.y+COIN*2) )
            return false;

        return true;
    }
}