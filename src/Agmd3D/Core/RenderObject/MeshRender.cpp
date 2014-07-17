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
            if(!m_transform)
                m_transform = new Transform();
            m_material = ResourceManager::Instance().Get<Material>("DEFAULT_MATERIAL");
        }

        MeshRender::~MeshRender()
        {}


        void MeshRender::render(TRenderPass pass) const
        {
            if(!m_material->Enable(pass))
                return;

            draw();
            m_material->Disable();
        }

        void MeshRender::draw() const
        {
            m_baseModel->Draw(m_transform);
        }

        void MeshRender::SetModel(Model*model)
        {
            m_baseModel = model;
        }

}



