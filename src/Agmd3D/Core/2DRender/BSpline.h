#ifndef _BSPLINE_H_
#define _BSPLINE_H_

#include <Core/2DRender/BaseSpline.h>
#include <Config/Export.h>
namespace Agmd
{

	class AGMD3D_EXPORT BSpline : public BaseSpline
	{
	public:
		BSpline(vec2 p[], int count, int degree) : BaseSpline(p,count), m_knot(count+degree,vec2()), m_degree(degree)
		{
			compute();
		}
		BSpline(const std::vector<vec2>& p, int degree) : BaseSpline(p), m_knot(p.size()+degree,vec2()), m_degree(degree)
		{
			compute();
		}
		virtual void compute();
		vec2 cdb(vec2* data ,std::vector<float> ti,int n,float t, int r);
	private:
		std::vector<vec2> m_knot;
		int m_degree;
	};
}
#endif /* _BSPLINE_H_ */
