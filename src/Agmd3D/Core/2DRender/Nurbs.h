#ifndef _NURBS_H_
#define _NURBS_H_

#include <Core/2DRender/BaseSpline.h>
#include <Config/Export.h>
namespace Agmd
{

    class AGMD3D_EXPORT Nurbs : public BaseSpline
    {
    public:
        Nurbs(vec3 p[], int count) : BaseSpline(p,count)
        {
            compute();
        }
        Nurbs(const std::vector<vec3>& p) : BaseSpline(p)
        {
            compute();
        }
        virtual void compute();
    };
}
#endif /* _NURBS_H_ */
