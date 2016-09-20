/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _AMODEL_H_
#define _AMODEL_H_

#include <Config/Fwd.h>
#include <Core/Enums.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Quaternion.h>
#include <Transform.h>

#include <Core/Tools/BoundingSphere.h>

#include <vector>

using namespace AgmdMaths;

namespace Agmd
{
    /* Interface for rendering */
    class AGMD3D_EXPORT AModel
    {
    public:
        virtual void Draw(const Transform* transform) const = 0;
        const BoundingSphere& getBounding() const { return m_bounding; }
    protected:

        BoundingSphere m_bounding;
    };
}


#endif /* _AMODEL_H_ */
