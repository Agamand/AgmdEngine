/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _CAMERANODE_H_
#define _CAMERANODE_H_

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
    class AGMD3D_EXPORT CameraNode : public SceneNode
    {
    public :
        CameraNode(Camera* cam, InputController* c = NULL, Transform* t = NULL);

        virtual ~CameraNode()
        {
        };

        virtual bool isVisible(BoundingSphere& bounds);

        virtual void findVisible(Camera* cam, RenderQueue& display,a_vector<LightNode*>& light);

        virtual bool update(Transform* transform, a_uint32 time, a_uint32 updateFlags);
        Camera* m_camera;
    protected:
    };
}


#endif /* _CAMERANODE_H_ */
