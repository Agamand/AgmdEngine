#include <Core/2DRender/BaseSpline.h>
#include <Core/Model/GeometryFactory.h>
#include <Container/Vector.h>
#include <CommonDefines.h>

namespace Agmd
{
    BaseSpline::BaseSpline(const vec3* points, int count) : _points(NULL), m_localUpdate(false)
    {
        for (int i = 0; i < count; i++)
            m_controlPoints.push_back(points[i]);
        m_controlPointsC = count;
        compute();
    }

    BaseSpline::BaseSpline(const a_vector<vec3>& points) : _points(NULL), m_localUpdate(false)
    {
        for (a_uint32 i = 0, len = points.size(); i < len; i++)
            m_controlPoints.push_back(points[i]);
        m_controlPointsC = m_controlPoints.size();
        compute();
    }

    void BaseSpline::addUpdateListener(UpdateListener* context)
    {
        m_updateListener.emplace_back(context);
    }

    void BaseSpline::compute(int pointIndex /*= -1*/)
    {
        m_computedPoints.clear();
        //         if(m_controlPoints.size() < 3)
        //         {
        for (a_uint32 i = 0, len = m_controlPoints.size(); i < len; i++)
            m_computedPoints.push_back(m_controlPoints[i]);
        return;
        //}
        //GeometryFactory::jarvis(m_controlPoints,m_computedPoints);
    }

    void BaseSpline::compute(a_vector<vec3>& out, int size)
    {
        //         if(m_controlPoints.size() < 3)
        //         {

        float pas = m_controlPoints.size() / (float)size;
        for (a_uint32 i = 0; i <= size; i++)
        {
            float cur = i * pas;
            a_uint32 a = (a_uint32)cur, b = a + 1;
            float t = cur - a;
            vec3 p1 = m_controlPoints[a], p2 = m_controlPoints[b];
            vec3 d = p2 - p1;
            out.push_back(p1 + d * t);
        }
        //}
        //GeometryFactory::jarvis(m_controlPoints,m_computedPoints);
    }

    void BaseSpline::updatePoint(int pointIndex /*= -1*/)
    {
        compute(pointIndex);
        for (auto i = 0; i < m_updateListener.size(); i++)
            m_updateListener[i]->onUpdate(m_computedPoints);
    }

    vec3* BaseSpline::getNearControlPoint(vec4 pos, int& pointindex, vec3* ignore/*=NULL */)
    {
        vec3* p = NULL;
        int i = 0;
        for (a_uint32 j = 0, len = m_controlPoints.size(); j < len; j++)
        {
            vec3* itr = &m_controlPoints[j];
            if (&(*itr) == ignore)
                continue;
            if (!p)
            {
                pointindex = i;
                p = itr;
            }
            else
            {
                float l = length((*itr) - vec3(pos));
                float l2 = length(*p - vec3(pos));
                if (l < l2)
                {
                    p = itr;
                    pointindex = i;
                }
            }
            i++;
        }
        return p;
    }

    void BaseSpline::addPoint(vec3& point)
    {
        m_controlPoints.push_back(point);

        updatePoint();
        m_controlPointsC = m_controlPoints.size();
    }

    bool BaseSpline::isClosed() const
    {
        if (m_computedPoints.size() < 2)
            return false;
        vec3 close = m_computedPoints[0] - m_computedPoints[m_computedPoints.size() - 1];
        return length(close) < 0.01f;
    }
}
