/*
============================================================================
Agmd3D - 3D Engine 
2012 - 2013
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

#include <Config/Fwd.h>

#include <Utilities/Singleton.h>

#include <Matrix4.h>
#include <Plane.h>

using namespace AgmdMaths;

namespace Agmd
{
    class Frustum : public Singleton<Frustum>
    {
        MAKE_SINGLETON(Frustum);
    public:
        Frustum();
		Frustum(const mat4& clipMatrix);
        ~Frustum();

		void Setup(const mat4& clipMatrix);

        bool IsIn(const vec3& pos) const;
        bool IsIn(const BoundingBox& box) const;

    private:

        Plane m_clipPlane[6];
    };
}

#endif /* _FRUSTUM_H_ */
