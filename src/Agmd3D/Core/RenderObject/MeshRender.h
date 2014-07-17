/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MESHRENDER_H_
#define _MESHRENDER_H_

#include <Core/RenderObject/Displayable.h>

namespace Agmd
{
    class AGMD3D_EXPORT MeshRender : public Displayable
    {
    public:
        MeshRender(Model* basemodel, Transform* transform = NULL);
        virtual ~MeshRender();

        virtual void render(TRenderPass pass) const;
        virtual void draw() const;

        void SetModel(Model*);

    protected:
        Model* m_baseModel;
    };
}

#endif // !_MESHRENDER_H_
