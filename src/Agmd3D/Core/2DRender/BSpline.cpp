#include <Core/2DRender/BSpline.h>

namespace Agmd
{
	float clamp(float a, float min,float max)
	{
		return a > max ? max : (a < min ? min : a);
	}
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

	void BSpline::compute( int pointIndex /*= -1*/ )
	{
		if(m_controlPoints.size() <= m_degree)
			return;
		int n = m_controlPoints.size()+m_degree+1;
		int max = n - m_degree - 1;

		if(pointIndex < 0|| true)
		{
			// ok Update all points
			//m_computedPoints.clear();
			
			std::vector<float> knots;
			printf("\n");
			for ( int i = 0; i <= m_degree; i ++ ) {
				knots.push_back( 0.0f );
				printf("0.0 ");
			}
			for ( int i = 0, j=m_controlPoints.size(); i < j; i ++ ) {
				float knot = ( i + 1 )/(float)( j - m_degree);
				knots.push_back(clamp(knot,0,1));
				printf("%f ",knot);
			}
			printf("\n");

			int max = n - m_degree - 1;
			vec2* _points = new vec2[(m_degree+1)*(max+1)];

			int m = 10*m_controlPoints.size();
			float p = 1.0f/m;

			/*for(int r = m_degree; r < n-m_degree-1; r++)
			{*/
				for(int i = 0; i <= m; i++)
				{
					if(m_computedPoints.size() < i+1)
						m_computedPoints.push_back(cdb(_points,knots,n,i*p,findr(m_degree,i*p,knots)));
					else m_computedPoints[i] = (cdb(_points,knots,n,i*p,findr(m_degree,i*p,knots)));
				}
			/*}*/
			delete _points;
		}else
		{
			std::vector<float> knots;
			printf("\n");
			for ( int i = 0; i <= m_degree; i ++ ) {
				knots.push_back( 0.0f );
				printf("0.0 ");
			}
			for ( int i = 0, j=m_controlPoints.size(); i < j; i ++ ) {
				float knot = ( i + 1 )/(float)( j - m_degree);
				knots.push_back(clamp(knot,0,1));
				printf("%f ",knot);
			}
			printf("\n");
			vec2* _points = new vec2[(m_degree+1)*(max+1)];
			// update point around m_controlPoint[pointIndex]
			for(int i = 0; i <= m; i++)
			{
				if(m_computedPoints.size() < i+1)
					m_computedPoints.push_back(cdb(_points,knots,n,i*p,findr(m_degree,i*p,knots)));
				else m_computedPoints[i] = (cdb(_points,knots,n,i*p,findr(m_degree,i*p,knots)));
			}


		}
	}

}