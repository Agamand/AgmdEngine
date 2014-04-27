#include <Core/2DRender/BaseSpline.h>
#include <vector>
namespace Agmd
{

	BaseSpline::BaseSpline( vec2 points[], int count )
	{
		for(int i = 0; i < count; i++)
			m_controlPoints.push_back(points[i]);
		compute();
	}

	BaseSpline::BaseSpline( const std::vector<vec2>& points )
	{
		for(std::vector<vec2>::const_iterator itr = points.begin(); itr !=points.end(); itr++)
			m_controlPoints.push_back(*itr);
		compute();
	}

	void BaseSpline::setUpdateListener( UpdateListener* context )
	{
		m_updateListener = context;
	}

	void BaseSpline::compute()
	{
		m_computedPoints.clear();
		for(std::vector<vec2>::iterator itr = m_controlPoints.begin(); itr !=m_controlPoints.end(); itr++)
			m_computedPoints.push_back(*itr);
	}

	void BaseSpline::updatePoint()
	{
		compute();
		if(m_updateListener)
			m_updateListener->onUpdate(m_computedPoints);
	}

	vec2* BaseSpline::getNearControlPoint( vec4 pos )
	{
		vec2* p = NULL;
		for(std::vector<vec2>::iterator itr = m_controlPoints.begin(); itr !=m_controlPoints.end(); itr++)
		{
			if(!p)
			{
				p = &(*itr);
			}else 
			{
				float l = length((*itr)-vec2(pos.x,pos.y));
				float l2 = length(*p-vec2(pos.x,pos.y));
				if(l < l2)
					p = &(*itr);
			}
		}
		return p;
	}

	void BaseSpline::addPoint(vec2& point )
	{
		m_controlPoints.push_back(point);
		updatePoint();
	}

	

}

