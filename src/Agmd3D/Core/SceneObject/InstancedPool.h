/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _INSTANCEDPOOL_H_
#define _INSTANCEDPOOL_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/SceneObject/InstancedMesh.h>

namespace Agmd
{
    class InstancedPool
    {
    public:
        InstancedPool(Model* model = NULL);
        InstancedPool(std::string& name);
        InstancedPool();

    private:
        Model* model;
    }
}

#endif