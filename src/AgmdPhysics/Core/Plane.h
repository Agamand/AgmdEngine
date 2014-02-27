/*
============================================================================
AgmdPhysics - Physics Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef PLANE_H
#define PlANE_H

#include <AgmdPhysics\Core\Entities.h>
#include <AgmdPhysics\Config\Export.h>
#include <AgmdPhysics\Config\Fwd.h>

namespace AgmdPhysics
{
    class PHYSICS_EXPORT Plane : public Entities
    {
    public:
        Plane(PPositionPtr pos);

        virtual bool Collision(Box* b);
        virtual bool Collision(Plane* b);
        virtual bool Collision(Sphere* b);
    private:
    };
}


#endif //SPHERE_H