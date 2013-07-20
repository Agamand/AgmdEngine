/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DISPLAYABLE_H_
#define _DISPLAYABLE_H_

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Transform.h>

using namespace AgmdMaths;

namespace Agmd
{

    class AGMD3D_EXPORT SceneNode
    {
    public :
        SceneNode(Transform*);
        virtual ~SceneNode();

        virtual void Render(TRenderPass pass) const = 0;
        virtual void Draw() const = 0;

        Transform& GetTransform();

    protected:

        Transform* m_transform;
        Material* m_material;
    };

}


#endif /* _SCENENODE_H_ */