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

namespace Agmd
{
    class BoundingBox
    {
    public:
        BoundingBox();
        ~BoundingBox();

        vec3 GetMin();
        vec3 GetMax();


    private:
        vec3 m_max;
        vec3 m_min;
    }; 
}


#endif /* _BOUNDINGBOX_H_ */
