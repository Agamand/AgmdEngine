#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <Core/2DRender/BaseSpline.h>

#include <Config/Export.h>
namespace Agmd
{

	class AGMD3D_EXPORT Bezier : public BaseSpline
	{
	public:
		Bezier(vec2 p[], int count) : BaseSpline(p,count)
		{
			compute();
		}
		Bezier(const std::vector<vec2>& p) : BaseSpline(p)
		{
			compute();
		}
		virtual void compute();
	};
}
#endif /* _BEZIER_H_ */
