#include <Core/2DRender/BSpline.h>

namespace Agmd
{
	/*float clamp(float a, float min,float max)
	{
		return a > max ? max : (a < min ? min : a);
	}*/
	int findr(float  p, float u,  std::vector<float> U ) {
		float n = U.size() - p - 1;

		if (u >= U[n]) {
			return n - 1;
		}

		if (u <= U[p]) {
			return p;
		}

		float low = p;
		float high = n;
		int mid = floor((low + high) / 2);

		while (u < U[mid] || u >= U[mid + 1]) {

			if (u < U[mid]) {
				high = mid;
			} else {
				low = mid;
			}

			mid = floor((low + high) / 2);
		}

		return mid;
	}
	
	vec2 BSpline::cdb( vec2* data ,std::vector<float> knots,int n,float t, int r )
	{
		int max = n - m_degree - 1;
		for(int i =  r - m_degree; i <= r; i++)
			data[i] = m_controlPoints[i];
		for(int j = 1; j <= m_degree; j++)
		{
			for(int i = r - m_degree + j ; i <= r; i++ )
				data[i+j*max] = ((t-knots[i])*data[i+(j-1)*max]+(knots[i-j+m_degree+1]-t)*data[i-1+(j-1)*max])/
				(knots[i-j+m_degree+1]-knots[i]);
		}
		return data[r+m_degree*max];
	}

	void BSpline::compute()
	{
		if(m_controlPoints.size() <= m_degree)
			return;
		m_computedPoints.clear();
		int n = m_controlPoints.size()+m_degree+1;
		std::vector<float> tt;
		for ( int i = 0; i < n; i ++ ) {
			float knot = ( i + 1 )/(float)( n - m_degree +1);
			tt.push_back(knot);
		}

		int max = n - m_degree - 1;
		vec2* _points = new vec2[(m_degree+1)*(max+1)];

		int m = 70;
		float p = 1.0f/m;

		/*for(int r = m_degree; r < n-m_degree-1; r++)
		{*/
			for(int i = 1; i <= m; i++)
			{
				m_computedPoints.push_back(cdb(_points,tt,n,i*p,findr(m_degree,i*p,tt)));
			}
		/*}*/
		delete _points;
	}

}