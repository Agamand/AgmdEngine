
#ifndef _POINT_H_
#define _POINT_H_

#include <sstream>
#include <cmath>
namespace Test
{

    class Point
    {
    public:
        Point();
        Point(float _x,float _y);
        Point(const Point& p);

        void translate(float _x,float _y);
        void translate(const Point& point);

        float getX() const;
        float getY() const;
        void getXY(float& x, float& y) const;


        void setX(float _x);
        void setY(float _y);
        void setXY(const Point&);

        float dist(const Point& p) const
        {
            return sqrtf((p.x-x)*(p.x-x)+(p.y+y)*(p.y+y));
        }

        inline Point operator*(float a)
        {
            return Point(x*a,y*a);
        }
        
        inline Point operator/(float a)
        {
            return Point(x/a,y/a);
        }

        inline Point operator+(const Point& p) const
        {
            return Point(x+p.x,y+p.y);
        }
        inline Point& operator-(const Point& p) const
        {
            return Point(x-p.x,y-p.y);
        }
        inline Point& operator+=(const Point& p)
        {
            Point r(p);
            r+*this;
            return r;
        }
        inline Point& operator-=(const Point& p)
        {
            Point r(p);
            r-*this;
            return r;
        }
    private:
        float x,y;
    };


    inline std::ostream& operator <<(std::ostream& stream, const Point& point)
    {
        stream<<"Point("<<point.getX() <<","<<point.getY()  <<")";
        return stream;
    } 
    inline std::istream& operator <<(std::istream& stream, Point& point)
    {
        float x,y;
        stream >> x >> y;
        point.setX(x);
        point.setY(y);
        return stream;
    } 
}
#endif /* _POINT_H_ */