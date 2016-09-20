#ifndef _BASESPLINE_H_
#define _BASESPLINE_H_

#include <Vector2.h>
#include <Container/Vector.h>

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
            virtual void onUpdate(a_vector<vec3>& points) = 0;
        };

        friend class DrawablePlane;

        BaseSpline(const vec3* points, int count);

        BaseSpline(const a_vector<vec3>& points);

        void addUpdateListener(UpdateListener* context);

        a_vector<vec3>& getControlPoints()
        {
            return m_controlPoints;
        }

        a_vector<vec3>& getComputedPoints()
        {
            return m_computedPoints;
        }

        vec3* getLastPoint()
        {
            return &m_controlPoints[m_controlPoints.size() - 1];
        }

        void updatePoint(int pointIndex = -1);
        vec3* getNearControlPoint(vec4 pos, int& pointindex, vec3* ignore = NULL);
        virtual void compute(int pointIndex = -1);
        virtual void compute(a_vector<vec3>& out, int size);
        void addPoint(vec3& p);
        bool isClosed() const;
    protected:
        a_vector<vec3> m_controlPoints;
        a_vector<vec3> m_computedPoints;
        a_vector<UpdateListener*> m_updateListener;
        int m_controlPointsC;
        vec3* _points;
        bool m_localUpdate;
    };
}
#endif /* _BASESPLINE_H_ */
