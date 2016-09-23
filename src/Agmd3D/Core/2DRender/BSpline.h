#ifndef _BSPLINE_H_
#define _BSPLINE_H_

#include <Core/2DRender/BaseSpline.h>
#include <Config/Export.h>

namespace Agmd
{
    class AGMD3D_EXPORT BSpline : public BaseSpline
    {
    public:
        friend class DrawablePlane;
        BSpline(const vec3* p, int count, int degree);
        BSpline(const a_vector<vec3>& p, int degree);
        virtual void compute(int pointIndex = -1);
        vec3 cdb(vec3* data, a_vector<float> ti, int n, float t, int r);
        virtual void compute(a_vector<vec3>& out, int size);

    private:
        a_vector<float> m_knot;
        int m_degree;
    };
}
#endif /* _BSPLINE_H_ */
