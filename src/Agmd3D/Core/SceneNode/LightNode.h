#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/Model/Light.h>

namespace Agmd
{
    class AGMD3D_EXPORT LightNode : public SceneNode
    {
    public:
        LightNode(Transform* t, Light* model): SceneNode(LIGHT_NODE, t), m_model(model) { ; }
        virtual bool IsVisible(BoundingSphere&) { return true; }
        Light* GetLightModel() const { return m_model; };

        virtual void findVisible(Camera* cam, RenderQueue& display,a_vector<LightNode*>& light)
        {
            light.push_back(this);
        }

        virtual bool update(Transform* transform, a_uint32 time, a_uint32 updateFlags)
        {
            bool res = SceneNode::update(transform, time, updateFlags);
            if (updateFlags & TRANSFORM_CHANGED)
            {
                vec4 position = m_transform->modelMatrix() * vec4(0, 0, 0, 1);//position;
                vec4 dir = m_transform->modelMatrix() * vec4(0, 1, 0, 0); //direction
                m_model->SetPosition(vec3(position));
                m_model->SetDirection(normalize(vec3(dir)));
            }
            return res;
        }

    private:
        Light* m_model;
    };
}
#endif /* _LIGHTNODE_H_ */
