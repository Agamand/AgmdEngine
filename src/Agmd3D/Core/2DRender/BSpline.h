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
        BSpline(vec2 p[], int count, int degree);
        BSpline(const a_vector<vec2>& p, int degree);
        virtual void compute(int pointIndex = -1);
        vec2 cdb(vec2* data , a_vector<float> ti,int n,float t, int r);


    private:
        a_vector<float> m_knot;
        int m_degree;
        
    };
}
#endif /* _BSPLINE_H_ */
