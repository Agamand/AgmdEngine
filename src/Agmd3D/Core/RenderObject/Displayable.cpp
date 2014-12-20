/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderObject/Displayable.h>
#include <Core/Model/Material.h>


namespace Agmd
{
    Displayable::Displayable(Transform* transform) : 
    m_material(NULL),
    m_transform(transform)
    {}

    Displayable::~Displayable()
    {}

    Transform& Displayable::getTransform() 
    { 
        return *m_transform;
    }

	Material* Displayable::getMaterial() const
	{
		return m_material;
	}

	void Displayable::setMaterial( Material* val )
	{
		m_material = val;
	}


}

