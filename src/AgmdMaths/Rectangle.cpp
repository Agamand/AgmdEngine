/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Rectangle.h>


namespace AgmdMaths
{

    Rectangle::Rectangle(const ivec2& start, const ivec2& size) :
    m_origin(start),
    m_end   (start + size)
    {
    }


    Rectangle::Rectangle(a_int32 left, a_int32 top, a_int32 width, a_int32 height) :
    m_origin(left, top),
    m_end   (left + width, top + height)
    {}


    void Rectangle::Set(a_int32 left, a_int32 top, a_int32 width, a_int32 height)
    {
        VEC2SET(m_origin,left,top);
        VEC2SET(m_end,left + width,top + height);
    }


    a_int32 Rectangle::left() const
    {
        return m_origin.x;
    }


    a_int32 Rectangle::right() const
    {
        return m_end.x;
    }


    a_int32 Rectangle::top() const
    {
        return m_origin.y;
    }


    a_int32 Rectangle::bottom() const
    {
        return m_end.y;
    }


    a_int32 Rectangle::width() const
    {
        return m_end.x - m_origin.x;
    }


    a_int32 Rectangle::height() const
    {
        return m_end.y - m_origin.y;
    }

    glm::ivec2 Rectangle::size() const
    {
        return m_end - m_origin;
    }

    TIntersection Rectangle::intersects(const ivec2& point) const
    {
        if ((point.x >= m_origin.x) && (point.y >= m_origin.y) && (point.x <= m_end.x) && (point.y <= m_end.y))
            return INT_IN;
        else
            return INT_OUT;
    }

    TIntersection Rectangle::intersects(const Rectangle& rect) const
    {
        ivec2 start(glm::max(m_origin.x, rect.m_origin.x), glm::max(m_origin.y, rect.m_origin.y));
        ivec2 m_end(glm::min(m_end.x, rect.m_end.x), glm::min(m_end.y, rect.m_end.y));
        Rectangle overlap(start, m_end - start);

        if ((start.x > m_end.x) || (start.y > m_end.y))
            return INT_OUT;
        else if ((overlap == *this) || (overlap == rect))
            return INT_IN;
        else
            return INT_INTERSECTS;
    }

    bool Rectangle::operator ==(const Rectangle& rect) const
    {
        return (m_origin == rect.m_origin) && (m_end == rect.m_end);
    }

    bool Rectangle::operator !=(const Rectangle& rect) const
    {
        return !(*this == rect);
    }

    std::istream& operator >>(std::istream& stream, Rectangle& rect)
    {
        return stream >> rect.m_origin >> STREAMTOVEC2(rect.m_end);
    }

    std::ostream& operator <<(std::ostream& stream, const Rectangle& rect)
    {
        return stream << rect.m_origin << " " << VEC2TOSTREAM(rect.m_end);
    }

}
