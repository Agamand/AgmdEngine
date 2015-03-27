#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/Model/Light.h>

namespace Agmd{
    class AGMD3D_EXPORT LightNode : public SceneNode
    {
    public:
        LightNode(Transform* t,Light* model): SceneNode(LIGHT_NODE,t), m_model(model) {;}
        virtual bool IsVisible(BoundingSphere&) { return true;}
        const Light* GetLightModel() const { return m_model;};

    private:
        Light* m_model;
    };
}
#endif /* _LIGHTNODE_H_ */