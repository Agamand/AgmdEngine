#ifndef _BASESPLINE_H_
#define _BASESPLINE_H_

#include <Vector2.h>
#include <vector>

#include <Config/Export.h>

/************************************************************************/
/* Spline class                                                         */
/************************************************************************/
namespace Agmd
{
	class AGMD3D_EXPORT BaseSpline
	{
	public:
		
		class UpdateListener
		{
		public:
			virtual void onUpdate(std::vector<vec2>& points) = 0;
		};
		friend class DrawablePlane;
		
		BaseSpline(vec2 points[], int count);
		
		BaseSpline(const std::vector<vec2>& points);
		
		void setUpdateListener(UpdateListener* context);

		std::vector<vec2>& getControlPoints() {
			return m_controlPoints;
		}

		std::vector<vec2>& getComputedPoints() {
			return m_computedPoints;
		}

		vec2* getLastPoint()
		{
			return &m_controlPoints[m_controlPoints.size()-1];
		}
		void updatePoint(int pointIndex = -1);
		vec2*getNearControlPoint( vec4 pos, int& pointindex, vec2* ignore=NULL );
		virtual void compute(int pointIndex = -1);
		void addPoint(vec2& p);
	protected:
		std::vector<vec2> m_controlPoints;
		std::vector<vec2> m_computedPoints;
		UpdateListener* m_updateListener;
		int m_controlPointsC;
		vec2* _points;
		bool m_localUpdate;
	};
}
#endif /* _BASESPLINE_H_ */