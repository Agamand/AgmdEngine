#include "Rectangle.h"
namespace Test
{


    Rectangle::Rectangle() : m_topLeft(),m_width(0),m_height(0)
    {}

    Rectangle::Rectangle( const Point& p, float w, float h ) : m_topLeft(p), m_width(w), m_height(h)
    {}

    Rectangle::Rectangle( const Rectangle& r ) : m_topLeft(r.m_topLeft),m_width(r.m_width),m_height(r.m_height)
    {}

    bool Rectangle::include( const Point& p )
    {
        
        if(p.getX() > m_topLeft.getY() || p.getY() < m_topLeft.getY() || p.getX() > m_topLeft.getX()+m_width || p.getY() < m_topLeft.getY()-m_height)
            return false;
        return true;
    }

    bool Rectangle::intersect( const Circle& c )
    {
        
    }

    const Point& Rectangle::getCenter() const
    {

        return Point(-m_width/2,m_height/2)+m_topLeft;
    }

    void Rectangle::rescale( float w ,float h )
    {
        m_width = w;
        m_height = h;
    }

    void Rectangle::translate( const Point& p)
    {
        m_topLeft += p;
    }

    

}