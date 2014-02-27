/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SKINNEDMESHRENDER_H_
#define _SKINNEDMESHRENDER_H_

#include <Core/RenderObject/Displayable.h>

namespace Agmd
{
    class AGMD3D_EXPORT SkinnedMeshRender : public Displayable
    {
    public:
        SkinnedMeshRender(Transform*);
        ~SkinnedMeshRender(); 
    private:
        /*
        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        Bone m_bonebase;
        */
        TPrimitiveType  m_PrimitiveType;
    }
}

#endif // !_SKINNEDMESHRENDER_H_
