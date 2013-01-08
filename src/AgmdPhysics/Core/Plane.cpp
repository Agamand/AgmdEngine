#include <AgmdPhysics\Core\Plane.h>

namespace AgmdPhysics
{
    Plane::Plane(PPositionPtr pos) : 
    Entities(pos, TYPE_PLANE)
    {}

    bool Plane::Collision(Sphere* s)
    {
        return false;
    }

    bool Plane::Collision( Plane* s)
    {
        return false;
    }

    bool Plane::Collision( Box* s)
    {
        return false;
    }
}