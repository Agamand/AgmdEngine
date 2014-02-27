/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _INSTANCEDMESH_H_
#define _INSTANCEDMESH_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/SceneObject/Displayable.h>


namespace Agmd
{
    class AGMD3D_EXPORT InstancedMesh : public Displayable
    {
    public:
        InstancedMesh(Model* model = NULL);
        InstancedMesh(std::string name);
        virtual ~InstancedMesh();
        
        virtual void Render() const;

    private:
        Model* model;
    }
}

#endif