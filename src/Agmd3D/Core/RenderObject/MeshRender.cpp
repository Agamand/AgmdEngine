/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderObject/MeshRender.h>
#include <Core/SceneObject/Material.h>
#include <Core/SceneObject/Model.h>
#include <Core/ResourceManager.h>

namespace Agmd
{
        MeshRender::MeshRender(Model* basemodel, Transform* transform) :
        Displayable(transform),
        m_baseModel(basemodel)
        {
            if(!transform)
                transform = new Transform();
            m_material = ResourceManager::Instance().Get<Material>("DEFAULT_MATERIAL");
        }

        MeshRender::~MeshRender()
        {}


        void MeshRender::Render(TRenderPass pass) const
        {
            if(!m_material->Enable(pass))
                return;

            Draw();
            m_material->Disable();
        }

        void MeshRender::Draw() const
        {
            m_baseModel->Draw(m_transform);
        }

}



