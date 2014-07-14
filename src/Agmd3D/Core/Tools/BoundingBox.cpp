/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/BoundingBox.h>

namespace Agmd
{
    BoundingBox::BoundingBox(const a_vector<vec3>& vertex_pos)
    {}

	BoundingBox::BoundingBox(const vec3 min, const vec3 max) : m_min(min),m_max(max)
	{}

    BoundingBox::BoundingBox(): m_min(0),m_max(0)
    {}

    vec3 BoundingBox::GetMin()
    {
        return m_min;
    }

    vec3 BoundingBox::GetMax()
    {
        return m_max;
    }

    BoundingBox BoundingBox::GetTransformedBoundingBox(Transform* transform)
    {
        vec4 min = vec4(m_min,1);
        vec4 max = vec4(m_max,1);
        min = transform->ModelMatrix()*min;
        max = transform->ModelMatrix()*max;

        if(min.x > max.x)
            std::swap(min.x,max.x);
        if(min.y > max.y)
            std::swap(min.y,max.y);
        if(min.z > max.z)
            std::swap(min.y,max.y);

        return BoundingBox(vec3(min),vec3(max));
    }
}
