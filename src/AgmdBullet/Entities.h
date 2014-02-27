/*
============================================================================
AgmdBullet - Bullet Physics API
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include <AgmdMaths\Quaternion.h>
#include <AgmdMaths\Matrix4.h>
#include <AgmdMaths\Vector3.h>

//BULLET INCLUDE
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include <CommonDefines.h>

#include <vector>

namespace Agmd
{

    

    struct PhysicsTransfo
    {
        PhysicsTransfo(vec3 _position = vec3(0.0f), quat _rotation = quat(1.0f,vec3(0.0f))) :
        m_position(_position),
        m_rotation(_rotation)
        {}

        vec3 m_position;
        quat m_rotation;
    };

    enum EntitiesType
    {
        TYPE_OBJECT,
        TYPE_COLLISION
    };


    class Entities
    {
    public:
        Entities(float _mass, btCollisionShape* _shape , PhysicsTransfo& _transfo,EntitiesType _type);
        void Prepare();
        void Update();

        EntitiesType GetType(){ return m_Type; }

        void SetMass(float _mass) { m_fMass = _mass; }
        bool IsStatic() { return m_fMass == 0; }
        void SetVelocity(vec3 _velocity); 

        btRigidBody* GetBody() { return m_Rigid; }


    private :

        void Init();

        btRigidBody* m_Rigid;

        PhysicsTransfo &m_Tranfo;
        EntitiesType m_Type;
        float m_fMass;
        btCollisionShape* m_Shape;
    };

}

#endif // ENTITIES_H