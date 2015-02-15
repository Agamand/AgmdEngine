

#include <Core/SceneNode/MeshNode.h>
#include <Core/Model/Material.h>
#include <Core/Model/Model.h>

namespace Agmd
{
    MeshNode::MeshNode(Model* basemodel, TransformPtr transform) :
    DisplayNode(transform,NULL),
    m_baseModel(basemodel)
    {
		m_type = MESH_NODE;
		m_baseBbox = m_baseModel->getBoundingBox();
		update(NULL,0,TRANSFORM_CHANGED);
	}
    MeshNode::~MeshNode()
    {}

    void MeshNode::draw() const
    {
        m_baseModel->Draw(m_transform);
    }

	bool MeshNode::isVisible(BoundingBox& bbox)
	{
		return true;
	}

    void MeshNode::render(TRenderPass pass) const
    {
		
        if(!m_material || !m_material->Enable(pass))
            return;

        draw();
        m_material->Disable();
    }

	void MeshNode::setMaterial( Material* surface_mat )
	{
		m_material = surface_mat;
	}

}