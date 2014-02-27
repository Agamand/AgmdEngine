/*
============================================================================
AgmdBullet - Bullet Physics API
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef AGMDPHYSICS_H
#define AGMDPHYSICS_H

#include <AgmdUtilities\Utilities\Singleton.h>
#include <AgmdMaths\Matrix4.h>
#include <AgmdMaths\Vector3.h>

//BULLET INCLUDE
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include <CommonDefines.h>

#include <vector>


namespace Agmd
{
    
    class Entities;

    typedef std::vector<Entities*> EntitiesVector;

    class PhysicsMgr : public Singleton<PhysicsMgr>
    {
    MAKE_SINGLETON(PhysicsMgr);
    public:
        PhysicsMgr();

        void Update(a_uint64 dt);
        void Add(Entities* _entities);
        void Remove(Entities* _entities);

        void SetGravity(vec3 g);

        void DebugDraw();

        a_uint64 GetDT() { return m_uidt; }

        btRigidBody* createRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);

    private:
        EntitiesVector m_evEntities;
        btDynamicsWorld* m_World;
        btScalar m_defaultContactProcessingThreshold;
        a_uint64 m_uidt;
    };

}

#endif

