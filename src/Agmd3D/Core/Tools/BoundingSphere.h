/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _BOUNDINGSPHERE_H_
#define _BOUNDINGSPHERE_H_

#include <Vector3.h>
#include <Config/Export.h>
#include <Container/Vector.h>

#include <Core/Tools/Bounding.h>

using namespace AgmdMaths;

namespace Agmd
{
    class AGMD3D_EXPORT BoundingSphere
    {
    public:
        BoundingSphere();
        BoundingSphere(const a_vector<vec3>& vertex_pos);
        BoundingSphere(const vec3& min, const vec3& max);
        BoundingSphere(const vec3& center, float radius);


        vec3 GetCenter() const { return m_center; }
        float GetRadius() const { return m_radius; }


        bool IsInFrustrum(Frustum* ft) const;

        const BoundingSphere GetTransformedBounding(const mat4& mat) const;

    private:
        vec3 m_center;
        float m_radius;
    };
}
#endif /* _BOUNDINGSPHERE_H_ */
