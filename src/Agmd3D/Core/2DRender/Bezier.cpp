#include <Core/2DRender/Bezier.h>
#include <vector>

namespace Agmd
{

	vec2 dc(std::vector<std::vector<vec2>>& points,const std::vector<vec2>& points_control,float t)
	{
		

		for(int j = 1; j < points_control.size(); j++)
		{
			for(int i = 0; i < points_control.size()-j; i++)
			{
				points[j][i] = points[j-1][i]*(1-t)+points[j-1][i+1]*t;
			}
		}
		return points[points_control.size()-1][0];
	}
	void Bezier::compute()
	{
		std::vector<std::vector<vec2>> points;
		m_computedPoints.clear();
		for(int i = 0; i < m_controlPoints.size(); i++)
		{
			points.push_back(std::vector<vec2>());
			points[i].resize(m_controlPoints.size(),vec2());
		}
		for(int i = 0; i < m_controlPoints.size();i++)
			points[0][i] = m_controlPoints[i];

		int m = 50;
		float p = 1.0f/m;

		m_computedPoints.push_back(dc(points,m_controlPoints,0));
		for(int i = 1; i <= m; i++)
		{
			m_computedPoints.push_back(dc(points,m_controlPoints,i*p));
		}

	}
}

