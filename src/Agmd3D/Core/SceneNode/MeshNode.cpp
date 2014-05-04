

#include <Core/SceneNode/MeshNode.h>
#include <Core/SceneObject/Material.h>
#include <Core/SceneObject/Model.h>

namespace Agmd
{
    MeshNode::MeshNode(Model* basemodel, TransformPtr transform) :
    DisplayNode(transform,NULL),
    m_baseModel(basemodel)
    {
		
	}
    MeshNode::~MeshNode()
    {}

    void MeshNode::Draw() const
    {
        m_baseModel->Draw(m_transform);
    }

	bool MeshNode::IsVisible(BoundingBox& bbox)
	{
		return true;
	}

    void MeshNode::Render(TRenderPass pass) const
    {
		
        if(!m_material || !m_material->Enable(pass))
            return;

        Draw();
        m_material->Disable();
    }
}