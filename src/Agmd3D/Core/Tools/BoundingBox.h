/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <Vector3.h>
#include <Transform.h>
#include <vector>

using namespace AgmdMaths;

namespace Agmd
{
    class BoundingBox
    {
    public:
        BoundingBox(const std::vector<vec3>& vertex_pos, TransformPtr transform);
        ~BoundingBox();

        vec3 GetMin();
        vec3 GetMax();

        const std::pair<vec3,vec3> GetTransformedBoundingBox();


    private:
        vec3 m_max;
        vec3 m_min;
        TransformPtr m_transform;
    }; 
}


#endif /* _BOUNDINGBOX_H_ */
