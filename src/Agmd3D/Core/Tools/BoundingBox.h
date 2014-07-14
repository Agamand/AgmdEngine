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
#include <Container/Vector.h>

using namespace AgmdMaths;

namespace Agmd
{
    class BoundingBox
    {
    public:
        BoundingBox(const a_vector<vec3>& vertex_pos);
		BoundingBox(const vec3, const vec3);
        BoundingBox();

        vec3 GetMin();
        vec3 GetMax();

        BoundingBox GetTransformedBoundingBox(Transform*);


    private:
        vec3 m_max;
        vec3 m_min;
    }; 
}


#endif /* _BOUNDINGBOX_H_ */
