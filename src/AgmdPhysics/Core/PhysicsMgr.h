/*
============================================================================
AgmdPhysics - Physics Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef AGMDPHYSICS_H
#define AGMDPHYSICS_H

#include <AgmdPhysics\Utilities\Singleton.h>
#include <AgmdPhysics\Core\Entities.h>
#include <AgmdPhysics\Core\Force.h>
#include <CommonDefines.h>

#include <vector>


namespace AgmdPhysics
{
    typedef std::vector<Entities*> EntitiesVector;

    struct CollisionInfo
    {
        vec3 collisionVelocity;
        vec3 collisionPos;
        uint64 t;
    };

    struct Intersection
    {
        Entities* entities_A;
        Entities* entities_B;
        CollisionInfo info_A;
        CollisionInfo info_B;
    };

    typedef std::vector<Intersection> IntersectionVector;

    class PhysicsMgr : public Singleton<PhysicsMgr>
    {
    MAKE_SINGLETON(PhysicsMgr);
    public:
        PhysicsMgr();

        void Update(uint64 dt);
        void TestCollision(Entities* ent);
        void Add(Entities* _entities);
        void Remove(Entities* _entities);

        uint64 GetDT() { return m_uidt; }

    private:
        EntitiesVector m_evEntities;
        IntersectionVector m_ivIntersection;
        Force m_fcGlobalForce;
        uint64 m_uidt;
    };

}

#endif