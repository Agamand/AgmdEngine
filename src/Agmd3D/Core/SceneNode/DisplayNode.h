/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DISPLAYNODE_H_
#define _DISPLAYNODE_H_

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Transform.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/Tools/RenderQueue.h>
#include <Core/Tools/BoundingSphere.h>

using namespace AgmdMaths;

namespace Agmd
{
    class LightNode;

    class AGMD3D_EXPORT DisplayNode : public SceneNode
    {
    public :
        DisplayNode(Transform* t, Material* mat);

        virtual ~DisplayNode()
        {
        };

        virtual void render(TRenderPass pass) const = 0;
        virtual void draw() const = 0;

        virtual void findVisible(Camera* cam, RenderQueue& display, a_vector<LightNode*>& light);
        Material& getMaterial() const { return *m_material; }
        const BoundingSphere& getBounding() const { return m_localBounds; };
        const BoundingSphere& getGlobalBounding() const { return m_globalBounds; };

        virtual bool isVisible(BoundingSphere& bbox);
        virtual bool update(Transform* transform, a_uint32 time, a_uint32 updateFlags);
    protected:
        BoundingSphere m_baseBounds;
        BoundingSphere m_localBounds;
        BoundingSphere m_globalBounds;
        Material* m_material;
    };
}


#endif /* _DISPLAYNODE_H_ */
