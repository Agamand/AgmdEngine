

#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_



#include "Point.h"
namespace Test
{
    class Circle;
    class Rectangle
    {
    public:
        friend class Test::Point;
        Rectangle();
        Rectangle(const Point&, float, float);
        Rectangle(const Rectangle&);
        bool include(const Point& p);
        bool intersect(const Circle& c);
        const Point& getCenter() const;
        void rescale(float,float);
        void translate(const Point&);

        const Point& getTopLeft() const { return m_topLeft; }
        void setTopLeft(const Point& val) { m_topLeft = val; }

        float getHeight() const { return m_height; }
        void setHeight(float val) { m_height = val; }

        float getWidth() const { return m_width; }
        void setWidth(float val) { m_width = val; }
        inline Point operator+(const Rectangle& r ) const;
        inline Point operator-(const Rectangle& r ) const;
        inline Point operator*(float a ) const;
        inline Point operator/(float a ) const;


    private:
        Point m_topLeft;
        float m_width, m_height;

    };
}

#endif /* _RECTANGLE_H_ */