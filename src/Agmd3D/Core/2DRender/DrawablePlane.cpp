#include <Core/2DRender/DrawablePlane.h>
#include <Core/Enums.h>
#include <Core/2DRender/Bezier.h>
#include <Core/2DRender/BSpline.h>
#define GRAB_DISTANCE 5.0f
#include <Core/GUI/GUIMgr.h>
namespace Agmd
{
	float clamp(float a, float min,float max)
	{
		return a > max ? max : (a < min ? min : a);
	}
	void DrawablePlane::OnClick( int click,int state, const vec2& pos, bool up )
	{
		
		if(state == MOUSE_LEFT && !up && (key == MAJ))
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			vec2* point = NULL;
			BaseSpline* spline = NULL;
			int pointIndex = 0;
			for(std::vector<LineRenderer*>::iterator itr = m_render.begin(); itr != m_render.end(); itr++)
			{
				BaseSpline* spl = (*itr)->getSpline();
				int pi;
				vec2* p = spl->getNearControlPoint(_pos,pi);
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
				pointIndex = pi;
			}
			if(point && spline)
			{
				m_selectedPoint = point;
				m_selectedSpline = spline;
				m_pointIndex = pointIndex;
			}
		}

		if(m_selectedPoint && m_selectedSpline && click & MOUSE_RIGHT)
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			vec2* point = NULL;
			BaseSpline* spline = NULL;
			int pointIndex = 0;
			for(std::vector<LineRenderer*>::iterator itr = m_render.begin(); itr != m_render.end(); itr++)
			{
				BaseSpline* spl = (*itr)->getSpline();
				int pi;
				vec2* p = spl->getNearControlPoint(_pos,pi,m_selectedPoint);
				if(!p)
					continue;
				float l = length((*p)-vec2(_pos.x,_pos.y));
				if(l > GRAB_DISTANCE)
					continue;
				if(p == m_selectedPoint)
					continue;
				if(point)
				{
					float l2 = length((*point)-vec2(_pos.x,_pos.y));
					if(l2 <= l)
						continue;
				}
				point = p;
				spline = spl;
				pointIndex = pi;
			}
			if(point && spline)
			{
				*m_selectedPoint = *point;
				m_selectedSpline->updatePoint(m_pointIndex);
			}
		}

		if(state == MOUSE_LEFT && !up && (key == CTRL))
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			m_bufferPoint.push_back(vec2(_pos.x,_pos.y));
			if(!m_selectedSpline)
			{
				//for(int i  =0 ; i < m_slider.size(); i++)
					//m_slider[i]->setEnable(false);
				BSpline* sp;
				m_selectedSpline = sp = new BSpline(m_bufferPoint,floor(degree));
				m_selectedPoint = m_selectedSpline->getLastPoint();
				m_render.push_back(new LineRenderer(m_selectedSpline));
				
			/*	if(sp->m_knot.size() > m_slider.size())
				{
					for(int i = m_slider.size(), j = sp->m_knot.size(); i < j; i++ )
					{


						ASlider* slider = new ASlider(NULL);
						slider->setLabel(StringBuilder("t")(i).operator std::string());
						GUIMgr::Instance().AddWidget(slider);
						slider->SetPosition(1300,750-i*35);
						slider->SetSize(200,20);
						slider->setUpdateCallBack(this);
						m_slider.push_back(slider);
					}

				}
				for(int i =0, j = sp->m_knot.size(); i < j; i++ )
				{
					m_slider[i]->setEnable(true);
					m_slider[i]->setValue(&sp->m_knot[i],-5,5);
				}*/
			}
			else if(m_selectedPoint)
			{
				m_selectedPoint = NULL;
			}else
			{
				m_selectedSpline->addPoint(vec2(_pos.x,_pos.y));
				m_selectedPoint = m_selectedSpline->getLastPoint();
				BSpline* sp = static_cast<BSpline*>(m_selectedSpline);
				int id = sp->m_knot.size()-1;
				/*if(sp->m_knot.size() > m_slider.size())
				{
					ASlider* slider = new ASlider(NULL);
					slider->setLabel(StringBuilder("t")(id).operator std::string());
					GUIMgr::Instance().AddWidget(slider);
					slider->SetPosition(1300,750-id*35);
					slider->SetSize(200,20);
					slider->setUpdateCallBack(this);
					m_slider.push_back(slider);
				}
				for(int i = 0, j = sp->m_knot.size(); i < j; i++ )
				{
					m_slider[i]->setEnable(true);
					m_slider[i]->setValue(&sp->m_knot[i],-5,5);
				}*/
			}
		}

		if(!up)
			return;
		if(click == MOUSE_LEFT && !(key & CTRL))
		{
			m_selectedPoint = NULL;
			m_selectedSpline = NULL;
		}
		if(click & MOUSE_RIGHT)
			rightDown = true;
		else rightDown = false;
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
		if(key == 'L' && m_render.size() && !up)
		{
			BSpline* spline  = static_cast<BSpline*>(m_render[m_render.size()-1]->getSpline());
			spline->m_knot.clear();
			for ( int i = -spline->m_degree-1, j=spline->m_controlPoints.size(); i < j; i ++ ) {
				float knot = ( i + 1 )/(float)( j - spline->m_degree);
				spline->m_knot.push_back(clamp(knot,0,1));
			}
			spline->updatePoint();
			/*for(int i =0, j = spline->m_knot.size(); i < j; i++ )
			{
				m_slider[i]->setEnable(true);
				m_slider[i]->setValue(&spline->m_knot[i],-5,5);
			}*/
		}
		if(key == 'U' && !up && m_render.size())
			m_render[m_render.size()-1]->getSpline()->m_localUpdate = !m_render[m_render.size()-1]->getSpline()->m_localUpdate;
			
		if(key == 'M' && m_render.size() && !up)
		{
			BSpline* spline  = static_cast<BSpline*>(m_render[m_render.size()-1]->getSpline());
			spline->m_knot.clear();
			for ( int i = -spline->m_degree-1, j=spline->m_controlPoints.size(); i < j; i ++ ) {
				float knot = ( i + 1 )/(float)( j - spline->m_degree);
				spline->m_knot.push_back(knot);//clamp(knot,0,1));
			}
			spline->updatePoint();
			/*for(int i =0, j = spline->m_knot.size(); i < j; i++ )
			{
				m_slider[i]->setEnable(true);
				m_slider[i]->setValue(&spline->m_knot[i],-5,5);
			}*/
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
	/*	for(int i  =0 ; i < m_slider.size(); i++)
			m_slider[i]->setEnable(false);*/
	}

	void DrawablePlane::OnMouseMotion( const vec2& pos )
	{
		if(m_selectedPoint && m_selectedSpline && !rightDown)
		{
			vec4 _pos(pos.x,pos.y,0,1);
			_pos = m_reverse_projection*_pos;
			*m_selectedPoint = vec2(_pos.x,_pos.y);
			m_selectedSpline->updatePoint(m_pointIndex);
		}
	}

	DrawablePlane::DrawablePlane( ivec2 pixelSize, vec2 repere ) : m_pixelSize(pixelSize), m_repere(repere),m_selectedPoint(NULL),m_selectedSpline(NULL),m_pointIndex(0),key(0),degree(3.0f)
	{
	
		Driver& driver = Driver::Get();
		m_frame = driver.CreateFrameBuffer();
		m_texture.Create(m_pixelSize,PXF_A8R8G8B8,TEXTURE_2D);
		m_frame->SetTexture(m_texture,COLOR_ATTACHMENT);
		m_projection = ortho(-m_repere.x,m_repere.x,-m_repere.y,m_repere.y);
		m_reverse_projection = inverse(m_projection);
	}

	vec2 DrawablePlane::getPositionFromScreenSpace(vec2 pos)
	{
		vec4 _pos = vec4(pos,0,1);
		_pos = m_reverse_projection*_pos;
		return vec2(_pos);
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

	void DrawablePlane::valueUpdate( float value,float cursor )
	{
		if(m_render.size() <= 0)
			return;
		m_render[m_render.size()-1]->getSpline()->updatePoint();

	}


}


