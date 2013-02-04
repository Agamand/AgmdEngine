/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderObject/Displayable.h>
#include <Core/SceneObject/Material.h>


namespace Agmd
{
    Displayable::Displayable(Transform* transform) : 
    m_material(NULL),
    m_transform(transform)
    {}

    Displayable::~Displayable()
    {}

    Transform& Displayable::GetTransform() 
    { 
        return *m_transform;
    }
}

