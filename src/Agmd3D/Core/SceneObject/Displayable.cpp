/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/SceneObject/Displayable.h>
#include <Core/SceneObject/Material.h>


namespace Agmd
{
    Displayable::Displayable() : 
    m_material(NULL)
    {}

    Displayable::~Displayable()
    {}

    Transform& Displayable::GetTransform() 
    { 
        return m_transform;
    }
}

