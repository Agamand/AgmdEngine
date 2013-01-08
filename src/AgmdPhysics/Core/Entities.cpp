#include <AgmdPhysics\Core\Entities.h>
#include <AgmdPhysics\Core\Sphere.h>
#include <AgmdPhysics\Core\Box.h>
#include <AgmdPhysics\Core\Plane.h>
#include <AgmdPhysics\Core\PhysicsMgr.h>

namespace AgmdPhysics
{
    Entities::Entities(PPositionPtr pos, EntitieType _type) : 
    m_Position(pos),
    m_bIsInCollision(false),
    m_Type(_type),
    m_bIsStatic(false)
    {}

    void Entities::Update(uint64 dt)
    {
        m_vOldAcceleration    = m_vAcceleration;
        m_vOldVelocity        = m_vVelocity;
        m_vOldPosition        = m_Position->m_position;

        // Apply Force
        vec3 forceSum(0.0f);
        vec3 momentSum(0.0f);
        std::size_t size = m_fvForces.size();
        for(std::size_t i = 0; i < size; i++)
        {
            forceSum += m_fvForces[i].GetForce();
            momentSum += dot(m_fvForces[i].GetForce(),m_fvForces[i].GetAppPoint());
        }
        
        m_vAcceleration = forceSum/m_fMass;
        m_vVelocity = m_vAcceleration*(float)dt + m_vOldVelocity;
        m_Position->m_position = 0.5f*m_vAcceleration*(float)dt*(float)dt + m_vOldVelocity*(float)dt + m_vOldPosition;
    }

    void Entities::AddForce(Force f)
    {
        m_fvForces.push_back(f);
    }

    void Entities::ClearAllForces()
    {
        m_fvForces.clear();
    }

    bool Entities::Collision(Entities* e)
    {
        switch(e->GetType())
        {
        case TYPE_SPHERE:
            return Collision(static_cast<Sphere*>(e));
        case TYPE_PLANE:
            return Collision(static_cast<Plane*>(e));
        case TYPE_BOX:
            return Collision(static_cast<Box*>(e));
        /*
        case TYPE_UNKNOWN:
            return Collision(static_cast<Unknown*>(e));
        */
        default:
            return false;
        }
    }

    bool Entities::GetIntersection(Entities* e, Intersection &inter)
    {
        switch(e->GetType())
        {
        case TYPE_SPHERE:
            return GetIntersection(static_cast<Sphere*>(e), inter);
        case TYPE_PLANE:
            return GetIntersection(static_cast<Plane*>(e), inter);
        case TYPE_BOX:
            return GetIntersection(static_cast<Box*>(e), inter);
        /*
        case TYPE_UNKNOWN:
            return Collision(static_cast<Unknown*>(e));
        */
        default:
            return false;
        }
    }
}