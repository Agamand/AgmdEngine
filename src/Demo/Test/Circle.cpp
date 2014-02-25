
#include "Circle.h"


namespace Test
{
Circle::Circle(): m_center(),m_radius(1.f)
{}

Circle::Circle(const Point& _center, float _radius) : m_center(_center),m_radius(_radius)
{}

// copy ctor
Circle::Circle(const Circle& c) : m_center(c.m_center), m_radius(c.m_radius)
{}

bool Circle::include( const Point& p ) const
{
    
    return m_center.dist(p) <= m_radius;
}

bool Circle::intersect(const Circle& c) const
{
    return m_center.dist(c.m_center) <= m_radius+c.m_radius;
}

void Circle::rescale(float f)
{
    m_radius *= f;
}
void Circle::translate(const Point& p)
{
    m_center.translate(p);
}
}

