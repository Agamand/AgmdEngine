

#include <Core/SceneNode/MeshSceneNode.h>
#include <Core/SceneObject/Material.h>
#include <Core/SceneObject/Model.h>

namespace Agmd
{
    MeshSceneNode::MeshSceneNode(Model* basemodel, TransformPtr transform) :
    SceneNode(transform),
    m_baseModel(basemodel)
    {}
    MeshSceneNode::~MeshSceneNode()
    {}

    void MeshSceneNode::Draw() const
    {
        m_baseModel->Draw(m_transform);
    }

    void MeshSceneNode::Render(TRenderPass pass) const
    {
        if(!m_material->Enable(pass))
            return;

        Draw();
        m_material->Disable();
    }
}