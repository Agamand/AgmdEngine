#include <Core/2DRender/BaseSpline.h>
#include <Core/Model/GeometryFactory.h>
#include <Container/Vector.h>
#include <CommonDefines.h>
namespace Agmd
{

	BaseSpline::BaseSpline( vec2 points[], int count ) : _points(NULL),m_localUpdate(false)
	{
		for(int i = 0; i < count; i++)
			m_controlPoints.push_back(points[i]);
		m_controlPointsC = count;
		compute();
	}

	BaseSpline::BaseSpline( const a_vector<vec2>& points ) :_points(NULL),m_localUpdate(false)
	{
		for(a_uint32 i = 0,len = points.size(); i < len; i++)
			m_controlPoints.push_back(points[i]);
		m_controlPointsC = m_controlPoints.size();
		compute();
	}

	void BaseSpline::setUpdateListener( UpdateListener* context )
	{
		m_updateListener = context;
	}

	void BaseSpline::compute( int pointIndex /*= -1*/ )
	{
		m_computedPoints.clear();
		if(m_controlPoints.size() < 3)
		{
			for(a_uint32 i = 0,len = m_controlPoints.size(); i < len; i++)
				m_computedPoints.push_back(m_controlPoints[i]);
			return;
		}
		GeometryFactory::jarvis(m_controlPoints,m_computedPoints);
		
	}

	void BaseSpline::updatePoint( int pointIndex  /*= -1*/)
	{
		compute(pointIndex);
		if(m_updateListener)
			m_updateListener->onUpdate(m_computedPoints);
	}

	vec2* BaseSpline::getNearControlPoint( vec4 pos, int& pointindex, vec2* ignore/*=NULL */ )
	{
		vec2* p = NULL;
		int i = 0;
		for(a_uint32 j = 0,len = m_controlPoints.size(); j < len; j++)
		{
			vec2* itr = &m_controlPoints[j];
			if(&(*itr) == ignore)
				continue;
			if(!p)
			{
				pointindex = i;
				p = itr;
			}else 
			{
				float l = length((*itr)-vec2(pos.x,pos.y));
				float l2 = length(*p-vec2(pos.x,pos.y));
				if(l < l2)
				{
					p = itr;
					pointindex = i;
				}
			}
			i++;
		}
		return p;
	}

	void BaseSpline::addPoint(vec2& point )
	{
		m_controlPoints.push_back(point);

		updatePoint();
		m_controlPointsC = m_controlPoints.size();
	}

	bool BaseSpline::isClosed() const
	{
		if(m_computedPoints.size() < 2)
			return false;
		vec2 close = m_computedPoints[0]-m_computedPoints[m_computedPoints.size()-1];
		return length(close) < 0.01f;
	}

	

}

