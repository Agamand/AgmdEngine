/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/GUI/ASlider.h>
#include <Core/Driver.h>
#include <Core/MatStack.h>
#include <Core/Tools/Fast2DSurface.h>

namespace Agmd
{
    #define COIN 30

    ASlider::ASlider( AWidget* parent) :
    AWidget(parent),
	hold(false),
	m_transform(new Transform()),
	m_value(&m_cursor),
	m_max(1.0f),
	m_min(0)
    {
        BuildSlider();
        //m_Texture.CreateFromFile("Texture/slider.png",PXF_A8R8G8B8);
        m_Program.LoadFromFile("Shader/gui/slider.glsl");
		m_ProgramCursor.LoadFromFile("Shader/gui/slider_cursor.glsl");
    }

    ASlider::~ASlider()
    {}


    a_uint32 ASlider::OnClick(ivec2& pos_mouse, a_uint32 mouseState)
    {
        if(!In(pos_mouse))
            return 0;
        hold = mouseState & MOUSE_LEFT;
		if(hold)
		{
			SetCursor((pos_mouse-m_vAbsolutePosition).x/(float)m_vSize.x);
		}
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
            float displacement = -(float)pos_diff.x/(float)m_vSize.x;
            SetCursor(m_cursor+displacement);
        }
        return 1;
    }

    a_uint32 ASlider::OnKey(char key)
    {
        return 0;
    }

    void ASlider::OnSizeChanged()
    {

    }

    void ASlider::OnPosChanged()
    {
		m_transform->SetPosition(vec3(m_vAbsolutePosition,0));
		m_transform->Update(NULL);
    }

    void ASlider::Draw() const
    {
        Driver &render = Driver::Get();
		render.SetCurrentProgram(m_Program.GetShaderProgram());
		render.SetCurrentTransform(m_transform);
		m_Program.SetParameter("u_size",vec2(m_vSize.x,0.2));
		Fast2DSurface::Instance().Draw();
		render.SetCurrentProgram(m_ProgramCursor.GetShaderProgram());
		m_Program.SetParameter("u_size",vec2(m_vSize.x,m_cursor));
		Fast2DSurface::Instance().Draw();
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

    void ASlider::BuildSlider()
    {

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
		*m_value = (m_max-m_min)*m_cursor+m_min;
    }

	void ASlider::setValue( float* value,float min,float max )
	{
		m_value = value;
		m_min = min;
		m_max = max;
		m_cursor = (*m_value-m_min)/(m_max-m_min);
	}

}