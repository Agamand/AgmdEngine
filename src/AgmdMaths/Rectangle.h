//==========================================================
//==========================================================

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Vector2.h>
#include <iostream>
#include <AgmdDefines.h>

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

        Rectangle(int32 left, int32 top, int32 width, int32 height);

        void Set(int32 left, int32 top, int32 width, int32 height);

        int32 Left() const;

        int32 Right() const;

        int32 Top() const;

        int32 Bottom() const;

        int32 Width() const;

        int32 Height() const;

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
