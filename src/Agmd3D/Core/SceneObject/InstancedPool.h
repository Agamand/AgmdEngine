#ifndef _INSTANCEDPOOL_H_
#define _INSTANCEDPOOL_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/InstancedMesh.h>
#include

namespace Agmd
{
    class InstancedPool
    {
    public:
        InstancedPool(Model* model = NULL);
        InstancedPool(std::string name);
        virtual InstancedMesh();

    private:
        Model* model;
    }
}

#endif