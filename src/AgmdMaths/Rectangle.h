/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Vector2.h>
#include <iostream>
#include <CommonDefines.h>

enum TIntersection
{
    INT_IN,
    INT_OUT,
    INT_INTERSECTS
};

namespace AgmdMaths
{
    class Rectangle
    {
    public :

        Rectangle(const ivec2& start = ivec2(0, 0), const ivec2& size = ivec2(0, 0));

        Rectangle(a_int32 left, a_int32 top, a_int32 width, a_int32 height);

        void Set(a_int32 left, a_int32 top, a_int32 width, a_int32 height);

        a_int32 left() const;

        a_int32 right() const;

        a_int32 top() const;

        a_int32 bottom() const;

        a_int32 width() const;

        a_int32 height() const;

        ivec2 size() const;

        TIntersection intersects(const ivec2& point) const;

        TIntersection intersects(const Rectangle& rect) const;

        bool operator ==(const Rectangle& rect) const;
        bool operator !=(const Rectangle& rect) const;

        ivec2 m_origin;
        ivec2 m_end;
    };

    std::istream& operator >>(std::ostream& stream, Rectangle& rect);
    std::ostream& operator <<(std::ostream& stream, const Rectangle& rect);
}

#endif
