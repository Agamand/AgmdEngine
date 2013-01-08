#include <AgmdPhysics\Core\Sphere.h>
#include <AgmdPhysics\Core\PhysicsMgr.h>

namespace AgmdPhysics
{
    Sphere::Sphere(PPositionPtr pos, float _fRayon) : 
    Entities(pos, TYPE_SPHERE),
    m_fRayon(_fRayon)
    {}

    bool Sphere::Collision(Sphere* s)
    {
        return false;
    }

    bool Sphere::Collision( Plane* s)
    {
        return false;
    }

    bool Sphere::Collision( Box* s)
    {
        return false;
    }

    bool Sphere::GetIntersection(Box* b, Intersection &inter)
    {
        return false;
    }

    bool Sphere::GetIntersection(Plane* p, Intersection &inter)
    {
        return false;
    }

    bool Sphere::GetIntersection(Sphere* s, Intersection &inter)
    {
        vec3 dist = m_Position->m_position - s->GetPosition()->m_position;
        float fdist = length(dist);

        if(m_fRayon + s->GetRayon() < fdist)
            return false;

        float dt = (float)PhysicsMgr::Instance().GetDT();

        vec3 v1 = (m_Position->m_position - m_vOldPosition)/dt;
        vec3 v2 = (s->GetPosition()->m_position - s->m_vOldPosition)/dt;
        vec3 v_diff = v1-v2;
        vec3 p_diff = m_vOldPosition - s->m_vOldPosition;

        float A = 2*v_diff.x*v_diff.x + 2*v_diff.y*v_diff.y + 2*v_diff.z*v_diff.z;
        float B = 2*v_diff.x*v_diff.x*p_diff.x*p_diff.x + 2*v_diff.y*v_diff.y*p_diff.x*p_diff.x + 2*v_diff.z*v_diff.z*p_diff.x*p_diff.x;
        float C = p_diff.x*p_diff.x + p_diff.y*p_diff.y + p_diff.z*p_diff.z - (m_fRayon-s->m_fRayon)*(m_fRayon-s->m_fRayon);
        float D = B*B-4*A*C;
        float t1 = 0, t2 = 0;
        float collision_t = 0;
        if(D >= 0.0f)
        {
            D = D == 0.0f ? 0.0f: sqrt(D);
            t1 = (-B+D)/(2*A);
            t2 = (-B-D)/(2*A);
        }
        else if(D < 0.0f)
            return false;

        if(t1 < t2)
            collision_t = t1;
        else collision_t = t2;

        if(collision_t > dt || collision_t < 0.0f)
            return false;

        // Calcul new force;


        

        /*

        p1*t+m_vOldPosition = p(t);
        p2*t+m_vOldPosition = p(t);
        (p1-p2)^2 = (R1+R2)^2
        ((p1-p2)*t+(m_vOldPosition-m_vOldPosition))^2 - (R1+R2)
        (x1-x2)^2+(y1-y2)^2+(z1-z2)^2-(R1+R2)^2 = 0
        x1^2
        */

        



        return true;
    }

}