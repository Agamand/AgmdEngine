/*
============================================================================
AgmdPhysics - Physics Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

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