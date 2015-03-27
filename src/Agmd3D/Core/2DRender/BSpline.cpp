#include <Core/2DRender/BSpline.h>
#include <CommonDefines.h>

namespace Agmd
{
    
    template <typename T> T _clamp(T a, T min,T max)
    {
        return a > max ? max : (a < min ? min : a);
    }

    int findr(float  p, float u,  a_vector<float> U ) {
        a_uint32 n = (a_uint32)(U.size() - p - 1);

        if (u >= U[n]) {
            return n - 1;
        }

        if (u <= U[(a_uint32)p]) {
            return (a_uint32)p;
        }
        float low = p;
        float high = (float)n;
        int mid = (int)floorf((low + high) / 2);

        while (u < U[mid] || u >= U[mid + 1]) {

            if (u < U[mid]) {
                high = (float)mid;
            } else {
                low = (float)mid;
            }

            mid = (int)floorf((low + high) / 2);
        }
        return mid;
    }

    vec2 BSpline::cdb( vec2* data ,a_vector<float> knots,int n,float t, int r )
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

        int n = m_controlPoints.size()+m_degree+1;
        int max = n - m_degree - 1;
        if((int)m_controlPoints.size() > m_controlPointsC)
        {
            printf("\n");
            m_knot.clear();
            for ( int i = -m_degree-1, j=m_controlPoints.size(); i < j; i ++ ) {
                float knot = ( i + 1 )/(float)( j - m_degree);
                m_knot.push_back(knot);//clamp(knot,0,1));
                printf("%f ",knot);
            }
            printf("\n");
        }
        if((int)m_controlPoints.size() <= m_degree)
            return;
        if(pointIndex < 0|| (int)m_controlPoints.size() > m_controlPointsC || !m_localUpdate)
        {
            // ok Update all points
            //m_computedPoints.clear();



            /*for ( int i = 0; i <= m_degree; i ++ ) {
            knots.push_back( 0.0f );
            printf("0.0 ");
            }*/


            int max = n - m_degree - 1;
            if((int)m_controlPoints.size() > m_controlPointsC)
            {
                if(_points != NULL)
                    delete[] _points;
                _points = new vec2[(m_degree+1)*(max+1)];
            }
            //_points = new vec2[(m_degree+1)*(max+1)];
            //_points = new vec2[(m_degree+1)*(max+1)];
            int m = 10*(int)m_controlPoints.size();
            float range = m_knot[m_knot.size()-1]-m_knot[0];
            float p = 1.0f/m;

            /*for(int r = m_degree; r < n-m_degree-1; r++)
            {*/
            float r = (float)m_degree;

            for(int i = 0; i <= m; i++)
            {
                while(m_knot[(int)r+1] < i*p)
                    r++;
                if((int)m_computedPoints.size() < i+1)
                    m_computedPoints.push_back(cdb(_points,m_knot,n,i*p,(int)r));
                else m_computedPoints[i] = (cdb(_points,m_knot,n,i*p,(int)r));
            }
            /*}*/
            //delete _points;    
        }else
        {

            int max = n - m_degree - 1;
            int m = 10*m_controlPoints.size();
            float p = 1.0f/m;

            int _min = _clamp<int>(pointIndex,m_degree,m_knot.size()-1);
            int _max = _clamp<int>(pointIndex+m_degree+1,m_degree,m_knot.size()-1);
            float b = m_knot[_min];
            float e = m_knot[_max];
            int i = (int)_clamp<float>(round((float)(b/p)),0,(float)m);
            m = (int)_clamp<float>(round((float)(e/p)),0,(float)m);

            float r = (float)m_degree;
            for(; i <= m; i++)
            {
                while(m_knot[(int)r+1] < i*p)
                    r++;
                if((int)m_computedPoints.size() < i+1)
                    m_computedPoints.push_back(cdb(_points,m_knot,n,i*p,(int)r));
                else m_computedPoints[i] = (cdb(_points,m_knot,n,i*p,(int)r));
            }

        }
    }

    BSpline::BSpline( vec2 p[], int count, int degree ) : BaseSpline(p,count), m_degree(degree)
    {
        _points = new vec2[(m_degree+1)*(count+1)];
        for ( int i = -m_degree-1, j=m_controlPoints.size(); i < j; i ++ ) {
            float knot = ( i + 1 )/(float)( j - m_degree);
            m_knot.push_back(knot);
        }
        compute();
    }

    BSpline::BSpline( const a_vector<vec2>& p, int degree ) : BaseSpline(p), m_degree(degree)
    {
        _points = new vec2[(m_degree+1)*(p.size()+1)];
        for ( int i = -m_degree-1, j=m_controlPoints.size(); i < j; i ++ ) {
            float knot = ( i + 1 )/(float)( j - m_degree);
            m_knot.push_back(knot);
        }
        compute();
    }

}