
#include "Point.h"
namespace Test
{

Point::Point() : x(0.f),y(0.f)
{}

Point::Point(float _x,float _y) :  x(_x),y(_y)
{} 

Point::Point(const Point& p): x(p.x),y(p.y)
{

}

void Point::translate(float _x,float _y)
{
    x +=_x;
    y +=_y;
}

void Point::translate(const Point& point)
{
    x +=point.x;
    y +=point.y;
}

float Point::getX() const
{
    return x;
}

float Point::getY() const
{
    return y;
}

void Point::getXY(float& x, float& y) const
{
    x = this->x;
    y = this->y;
}

void Point::setX(float _x)
{
    x = _x;
}

void Point::setY(float _y)
{
    y = _y;
}


void Point::setXY(const Point& point)
{
    x = point.x;
    y = point.y;
}

}
