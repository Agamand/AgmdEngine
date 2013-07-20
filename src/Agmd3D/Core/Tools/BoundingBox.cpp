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
    BoundingBox::BoundingBox(const std::vector<vec3>& vertex_pos, TransformPtr transform)
    {

    }

    BoundingBox::~BoundingBox()
    {
    }

    vec3 BoundingBox::GetMin()
    {
        return m_min;
    }

    vec3 BoundingBox::GetMax()
    {
        return m_max;
    }

    const std::pair<vec3,vec3> BoundingBox::GetTransformedBoundingBox()
    {
        vec4 min = vec4(m_min,1);
        vec4 max = vec4(m_max,1);
        min = m_transform->ModelMatrix()*min;
        max = m_transform->ModelMatrix()*max;

        if(min.x > max.x)
            std::swap(min.x,max.x);
        if(min.y > max.y)
            std::swap(min.y,max.y);
        if(min.z > max.z)
            std::swap(min.y,max.y);

        return std::pair<vec3,vec3>(vec3(min),vec3(max));
    }
}
