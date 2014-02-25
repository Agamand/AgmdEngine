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

        a_int32 Left() const;

        a_int32 Right() const;

        a_int32 Top() const;

        a_int32 Bottom() const;

        a_int32 Width() const;

        a_int32 Height() const;

        ivec2 Size() const;

        TIntersection Intersects(const ivec2& point) const;

        TIntersection Intersects(const Rectangle& rect) const;

        bool operator ==(const Rectangle& rect) const;
        bool operator !=(const Rectangle& rect) const;

        ivec2 m_Origin;
        ivec2 m_End;
    };

    std::istream& operator >>(std::ostream& stream, Rectangle& rect);
    std::ostream& operator <<(std::ostream& stream, const Rectangle& rect);

}

#endif
