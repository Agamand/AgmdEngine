//==========================================================
//==========================================================

#include <Rectangle.h>


namespace AgmdMaths
{

    Rectangle::Rectangle(const ivec2& start, const ivec2& size) :
    m_Origin(start),
    m_End   (start + size)
    {

    }


    Rectangle::Rectangle(int32 left, int32 top, int32 width, int32 height) :
    m_Origin(left, top),
    m_End   (left + width, top + height)
    {}


    void Rectangle::Set(int32 left, int32 top, int32 width, int32 height)
    {
        VEC2SET(m_Origin,left,top);
        VEC2SET(m_End,left + width,top + height);
    }


    int32 Rectangle::Left() const
    {
        return m_Origin.x;
    }


    int32 Rectangle::Right() const
    {
        return m_End.x;
    }


    int32 Rectangle::Top() const
    {
        return m_Origin.y;
    }


    int32 Rectangle::Bottom() const
    {
        return m_End.y;
    }


    int32 Rectangle::Width() const
    {
        return m_End.x - m_Origin.x;
    }


    int32 Rectangle::Height() const
    {
        return m_End.y - m_Origin.y;
    }

    ivec2 Rectangle::Size() const
    {
        return m_End - m_Origin;
    }

    TIntersection Rectangle::Intersects(const ivec2& point) const
    {
        if ((point.x >= m_Origin.x) && (point.y >= m_Origin.y) && (point.x <= m_End.x) && (point.y <= m_End.y))
            return INT_IN;
        else
            return INT_OUT;
    }

    TIntersection Rectangle::Intersects(const Rectangle& rect) const
    {
        // Calcul du rectangle d'intersection
        ivec2 start(std::max(m_Origin.x, rect.m_Origin.x), std::max(m_Origin.y, rect.m_Origin.y));
        ivec2 m_End(std::min(m_End.x, rect.m_End.x), std::min(m_End.y, rect.m_End.y));
        Rectangle Overlap(start, m_End - start);

        if ((start.x > m_End.x) || (start.y > m_End.y))
            return INT_OUT;
        else if ((Overlap == *this) || (Overlap == rect))
            return INT_IN;
        else
            return INT_INTERSECTS;
    }

    bool Rectangle::operator ==(const Rectangle& rect) const
    {
        return (m_Origin == rect.m_Origin) && (m_End == rect.m_End);
    }

    bool Rectangle::operator !=(const Rectangle& rect) const
    {
        return !(*this == rect);
    }

    std::istream& operator >>(std::istream& stream, Rectangle& rect)
    {
        return stream >> rect.m_Origin >> STREAMTOVEC2(rect.m_End);
    }

    std::ostream& operator <<(std::ostream& stream, const Rectangle& rect)
    {
        return stream << rect.m_Origin << " " << VEC2TOSTREAM(rect.m_End);
    }

}
