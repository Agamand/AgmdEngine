#ifndef SPHERE_H
#define SPHERE_H

#include <AgmdPhysics\Core\Entities.h>
#include <AgmdPhysics\Config\Export.h>
#include <AgmdPhysics\Config\Fwd.h>

namespace AgmdPhysics
{
    class PHYSICS_EXPORT Sphere : public Entities
    {
    public:
        //friend Entities;
        Sphere(PPositionPtr pos, float _fRayon);

        virtual bool Collision(Box* b);
        virtual bool Collision(Plane* b);
        virtual bool Collision(Sphere* b);

        virtual bool GetIntersection(Box* b, Intersection &inter);
        virtual bool GetIntersection(Plane* b, Intersection &inter);
        virtual bool GetIntersection(Sphere* b, Intersection &inter);

        float GetRayon() {return m_fRayon;}

    private:
        float m_fRayon;
    };
}


#endif //SPHERE_H