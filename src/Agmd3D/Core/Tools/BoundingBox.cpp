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
    BoundingBox::BoundingBox()
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
}
