/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/Frustum.h>
#include <Core/Tools/BoundingSphere.h>

#include <Core/Tools/BoundingBox.h>

namespace Agmd
{
    Frustum::Frustum()
    {
    }

    Frustum::Frustum(const mat4& clipMatrix)
    {
        Setup(clipMatrix);
    }

    Frustum::~Frustum()
    {
    }

    void Frustum::Setup(const mat4& clipMatrix)
    {
        const float* clip = &clipMatrix[0][0];

        m_clipPlane[0] = Plane(clip[3] - clip[0], clip[7] - clip[4],
                               clip[11] - clip[8], (clip[15] - clip[12]));

        m_clipPlane[1] = Plane(clip[3] + clip[0], clip[7] + clip[4],
                               clip[11] + clip[8], clip[15] + clip[12]);

        m_clipPlane[2] = Plane(clip[3] + clip[1], clip[7] + clip[5],
                               clip[11] + clip[9], clip[15] + clip[13]);

        m_clipPlane[3] = Plane(clip[3] - clip[1], clip[7] - clip[5],
                               clip[11] - clip[9], clip[15] - clip[13]);

        m_clipPlane[4] = Plane(clip[3] - clip[2], clip[7] - clip[6],
                               clip[11] - clip[10], clip[15] - clip[14]);

        m_clipPlane[5] = Plane(clip[3] + clip[2], clip[7] + clip[6],
                               clip[11] + clip[10], clip[15] + clip[14]);
        for (int i = 0; i < 6; i++)
            m_clipPlane[i].normalize();
    }

    bool Frustum::IsIn(const vec3& pos) const
    {
        for (int i = 0; i < 6; i++)
            if (!(m_clipPlane[i].distanceToPoint(pos) > 0.0f))
                return false;
        return true;
    }

    bool Frustum::IsIn(const BoundingSphere& box) const
    {
        float radius = box.GetRadius(),
            distance;
        for (int i = 0; i < 6; i++)
        {
            float distance = m_clipPlane[i].distanceToPoint(box.GetCenter());
            if (distance < -radius)
                return false;
        }
        return true;
        //         vec3 max,min;
        //         max = box.GetMin();
        //         min = box.GetMax();
        // 
        //         if( IsIn( vec3(min.x, min.y, min.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(max.x, min.y, min.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(min.x, max.y, min.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(max.x, max.y, min.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(min.x, min.y, max.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(max.x, min.y, max.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(min.x, max.y, max.z)) )
        //             return true;
        // 
        //         if( IsIn( vec3(max.x, max.y, max.z)) )
        //             return true;
        // 
        //         return false;
    }

    bool Frustum::IsIn(const BoundingBox& bounds) const
    {
        int out, in;

        vec3 _min = bounds.GetMin(), _max = bounds.GetMax();

        vec3 corners[8] = {
            _min,
            vec3(_min.x, _min.y, _max.z),
            vec3(_max.x, _min.y, _max.z),
            vec3(_max.x, _min.y, _min.z),
            _max,
            vec3(_min.x, _max.y, _max.z),
            vec3(_min.x, _max.y, _min.z),
            vec3(_max.x, _max.y, _min.z)
        };

        for (int i = 0; i < 6; i++)
        {
            out = 0;
            in = 0;
            for (int k = 0; k < 8 && (in == 0 || out == 0); k++)
            {
                // is the corner outside or inside
                if (m_clipPlane[i].distanceToPoint(corners[k]) < 0)
                    out++;
                else
                    in++;
            }
            //if all corners are out
            if (!in)
                return false;
        }
        return true;
    }
}
