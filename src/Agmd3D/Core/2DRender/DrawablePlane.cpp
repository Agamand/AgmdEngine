#include <Core/2DRender/DrawablePlane.h>
#include <Core/Enums.h>
#include <Core/2DRender/Bezier.h>
#include <Core/2DRender/BSpline.h>
#define GRAB_DISTANCE 5.0f
namespace Agmd
{
	void DrawablePlane::OnClick( int click,int state, const vec2& pos, bool up )
	{
		
		if(state == MOUSE_LEFT && !up && (key == MAJ))
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			vec2* point = NULL;
			BaseSpline* spline = NULL;
			for(std::vector<LineRenderer*>::iterator itr = m_render.begin(); itr != m_render.end(); itr++)
			{
				BaseSpline* spl = (*itr)->getSpline();
				vec2* p = spl->getNearControlPoint(_pos);
				if(!p)
					continue;
				float l = length((*p)-vec2(_pos.x,_pos.y));
				if(l > GRAB_DISTANCE)
					continue;
				if(point)
				{
					float l2 = length((*point)-vec2(_pos.x,_pos.y));
					if(l2 <= l)
						continue;
				}
				point = p;
				spline = spl;
			}
			if(point && spline)
			{
				m_selectedPoint = point;
				m_selectedSpline = spline;
			}
		}

		if(state == MOUSE_LEFT && !up && (key == CTRL))
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			m_bufferPoint.push_back(vec2(_pos.x,_pos.y));
			if(!m_selectedSpline)
			{
				m_selectedSpline = new BSpline(m_bufferPoint,3);
				m_selectedPoint = m_selectedSpline->getLastPoint();
				m_render.push_back(new LineRenderer(m_selectedSpline));
			}
			else if(m_selectedPoint)
			{
				m_selectedPoint = NULL;
			}else
			{
				m_selectedSpline->addPoint(vec2(_pos.x,_pos.y));
				m_selectedPoint = m_selectedSpline->getLastPoint();
			}
		}

		if(!up)
			return;
		if(click == MOUSE_LEFT && !(key & CTRL))
		{
			m_selectedPoint = NULL;
			m_selectedSpline = NULL;
		}
	}

	void DrawablePlane::OnKey( char key, bool up )
	{
		if(key == 17) //ctrl
		{
			this->key = !up ? this->key | CTRL : this->key & ~CTRL ;
			//flush
			if(up)
			{
				m_selectedPoint = NULL;
				m_selectedSpline = NULL;
				m_bufferPoint.clear();
			}
		}
		if(key == 16) //MAJ
			this->key = !up ? this->key | MAJ : this->key & ~MAJ ;
		if(key == 'C')
			clear();
	}

	void DrawablePlane::clear()
	{
		m_selectedPoint = NULL;
		m_selectedSpline = NULL;
		m_render.clear();
	}

	void DrawablePlane::OnMouseMotion( const vec2& pos )
	{
		if(m_selectedPoint && m_selectedSpline)
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			*m_selectedPoint = vec2(_pos.x,_pos.y);
			m_selectedSpline->updatePoint();
		}
	}

	DrawablePlane::DrawablePlane( ivec2 pixelSize, vec2 repere ) : m_pixelSize(pixelSize), m_repere(repere),m_selectedPoint(NULL),m_selectedSpline(NULL),key(0)
	{
	
		Driver& driver = Driver::Get();
		m_frame = driver.CreateFrameBuffer();
		m_texture.Create(m_pixelSize,PXF_A8R8G8B8,TEXTURE_2D);
		m_frame->SetTexture(m_texture,COLOR_ATTACHMENT);
		m_projection = ortho(-m_repere.x,m_repere.x,-m_repere.y,m_repere.y);
		m_reverse_projection = inverse(m_projection);
	}

	void DrawablePlane::render()
	{
		m_frame->Bind();
		m_frame->Clear(CLEAR_COLOR);
		Driver::Get().Enable(RENDER_POINTSIZE_SHADER,true);
		for(std::vector<LineRenderer*>::iterator itr = m_render.begin(); itr != m_render.end(); itr++)
			(*itr)->draw(m_projection);
		for(std::vector<LineRenderer*>::iterator itr = m_render.begin(); itr != m_render.end(); itr++)
			(*itr)->drawPoints(m_projection);
		m_frame->UnBind();
	}


}


