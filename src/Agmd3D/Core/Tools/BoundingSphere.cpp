/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/BoundingSphere.h>
#include <CommonDefines.h>
namespace Agmd
{

    BoundingSphere::BoundingSphere(const a_vector<vec3>& vertex_pos) :  m_center(0),m_radius(0)
    {
        if(!vertex_pos.size())
            return;
        vec3 _min,_max;
        _min = _max = vertex_pos[0];
        for(a_uint32 i = 1,len = vertex_pos.size(); i < len; i++ )
        {
            _min.x = min(_min.x,vertex_pos[i].x);
            _min.y = min(_min.y,vertex_pos[i].y);
            _min.z = min(_min.z,vertex_pos[i].z);

            _max.x = max(_max.x,vertex_pos[i].x);
            _max.y = max(_max.y,vertex_pos[i].y);
            _max.z = max(_max.z,vertex_pos[i].z);
        }

        m_center = _min+(_max-_min)/2.f;
        m_radius = length((_max-_min)/2.f);

    }
    BoundingSphere::BoundingSphere(const vec3& _min, const vec3& _max): m_center(_min+(_max-_min)/2.f),m_radius(length((_max-_min)/2.f))
    {}

    BoundingSphere::BoundingSphere(const vec3& center, float radius) : m_center(center),m_radius(radius)
    {}

    BoundingSphere::BoundingSphere(): m_center(0),m_radius(0)
    {}

    const BoundingSphere BoundingSphere::GetTransformedBounding( const mat4& mat ) const
    {
        vec4 points[2] = {
            vec4(m_center,1),
            vec4(m_center+vec3(0,0,1)*m_radius,1)
        };
         for(a_uint8 i = 0; i < 2; i++)
             points[i] = mat*points[i];
        return BoundingSphere(vec3(points[0]),length(vec3(points[1]-points[0])));
    }

    bool BoundingSphere::IsInFrustrum( Frustum* ft ) const
    {
        throw std::exception("The method or operation is not implemented.");
    }


}
