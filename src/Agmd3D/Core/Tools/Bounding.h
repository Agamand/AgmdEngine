/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _BOUNDING_H_
#define _BOUNDING_H_

#include <Vector3.h>
#include <Config/Export.h>
#include <Container/Vector.h>

using namespace AgmdMaths;


namespace Agmd
{
    class Frustum;

    class AGMD3D_EXPORT Bounding
    {
    public:
        virtual const Bounding GetTransformedBounding(const mat4& mat) const { return *this; }
        virtual bool IsInFrustrum(Frustum* ft) const { return true; }
    };
}
#endif /* _BOUNDING_H_ */
