
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point.h"
namespace Test
{
class Circle
{
public:
    friend class Point;


    Circle();
    Circle(const Point& center, float radius);

    // copy ctor
    Circle(const Circle& c);
    bool include(const Point& p) const;
    bool intersect(const Circle& p) const;
    void rescale(float f);
    void translate(const Point& p);

    float getRadius() const {return m_radius;} 
    const Point& getCenter() const { return m_center;}

private:
    Point m_center;
    float m_radius;

};
inline std::ostream& operator <<(std::ostream& stream, const Circle& c)
{
    stream<<"Circle(Center:"<<c.getCenter() <<", Radius: "<<c.getRadius()  <<")";
    return stream;
}
}
#endif /* _CIRCLE_H_ */