#include <AgmdPhysics\Core\Box.h>

namespace AgmdPhysics
{
    Box::Box(PPositionPtr pos) : 
    Entities(pos, TYPE_BOX)
    {}

    bool Box::Collision(Sphere* s)
    {
        return false;
    }

    bool Box::Collision( Plane* s)
    {
        return false;
    }

    bool Box::Collision( Box* s)
    {
        return false;
    }
}