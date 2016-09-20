#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <Core/2DRender/BaseSpline.h>

#include <Config/Export.h>

namespace Agmd
{
    class AGMD3D_EXPORT Bezier : public BaseSpline
    {
    public:
        Bezier(vec3 p[], int count) : BaseSpline(p, count)
        {
            compute();
        }

        Bezier(const std::vector<vec3>& p) : BaseSpline(p)
        {
            compute();
        }

        virtual void compute(int pointIndex = -1);
    };
}
#endif /* _BEZIER_H_ */
