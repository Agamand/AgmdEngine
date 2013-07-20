/*
============================================================================
AgmdPhysics - Physics Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include <AgmdPhysics\Config\Fwd.h>
#include <AgmdPhysics\Config\Export.h>
#include <AgmdPhysics\Maths\Vector3.h>
#include <AgmdPhysics\Maths\Matrix4.h>
#include <AgmdPhysics\Core\Force.h>

#include <CommonDefines.h>

#include <vector>

namespace AgmdPhysics
{

    

    struct PHYSICS_EXPORT PPosition
    {
        PPosition(vec3 _position = vec3(0.0f), mat4 _rotation = mat4(1.0f)) :
        m_position(_position),
        m_rotation(_rotation)
        {}

        vec3 m_position;
        mat4 m_rotation;
    };

    typedef PPosition* PPositionPtr;
    typedef std::vector<Force> ForceVector;

    enum EntitieType
    {
        TYPE_UNKNOWN    = 0,
        TYPE_SPHERE        = 1,
        TYPE_PLANE        = 2,
        TYPE_BOX        = 3
    };

    class PHYSICS_EXPORT Entities
    {
    public:
        Entities(PPositionPtr pos, EntitieType _type);
        void Update(uint64 dt);
        void AddForce(Force f);
        void ClearAllForces();
        PPositionPtr GetPosition() { return m_Position; }

        bool Collision(Entities* e);
        bool GetIntersection(Entities* e, Intersection &inter);

        EntitieType GetType(){ return m_Type; }

        void SetStatic(bool _static = true) { m_bIsStatic = _static; }
        bool IsStatic() { return m_bIsStatic; }

        vec3 GetOldVelocity() {return m_vOldVelocity;}
        vec3 GetVelocity() {return m_vVelocity;}
        //vec3 GetOldVelocity() {return m_vOldVelocity;}



    protected:

        virtual bool Collision(Box* b) = 0;
        virtual bool Collision(Plane* b) = 0;
        virtual bool Collision(Sphere* b) = 0;

        virtual bool GetIntersection(Box* b, Intersection &inter) = 0;
        virtual bool GetIntersection(Plane* b, Intersection &inter) = 0;
        virtual bool GetIntersection(Sphere* b, Intersection &inter) = 0;

        float            m_fMass;            // Mass

        vec3            m_vOldPosition;        // Position
        vec3            m_vOldVelocity;        // Velocity
        vec3            m_vOldAcceleration;    // Acceleration

        PPositionPtr    m_Position;
        vec3            m_vVelocity;        // Velocity
        vec3            m_vAcceleration;    // Acceleration
        ForceVector        m_fvForces;            // All Forces;
        
        mat3            m_mInertia;            // Inertia matrix

        bool            m_bIsInCollision;
        bool            m_bIsStatic;
    private :

        EntitieType        m_Type;                // Entitie type
    };

}

#endif // ENTITIES_H