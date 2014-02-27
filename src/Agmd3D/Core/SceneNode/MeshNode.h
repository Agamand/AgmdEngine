/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MESHNODE_H_
#define _MESHNODE_H_

#include <Core/SceneNode/DisplayNode.h>

namespace Agmd
{
    class AGMD3D_EXPORT MeshNode : public DisplayNode
    {
    public:
        MeshNode(Model* basemodel, Transform* transform = NULL);
        virtual ~MeshNode();

        virtual void Render(TRenderPass pass) const;
        virtual void Draw() const;
		virtual bool IsVisible(BoundingBox& bbox);
    private:
        Model* m_baseModel;
    };
}

#endif /*  _MESHSCENENODE_H_ */
