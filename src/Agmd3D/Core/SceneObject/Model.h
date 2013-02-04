/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef MODEL_H
#define MODEL_H

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Texture/Texture.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Quaternion.h>
#include <Transform.h>

#include <vector>

using namespace AgmdMaths;

namespace Agmd
{

    enum GenerateType
    {
        G_NONE = 0x0,
        G_NORMAL = 0x1,
        G_TANGENT = 0x2,
        G_ALL = G_NORMAL | G_TANGENT
    };

    class AGMD3D_EXPORT Model : public Resource
    {
    public :
        struct TVertex
        {
            vec3     position;
            vec3     normal;
            uint32   color;
            vec2     texCoords;
            vec4     tangent;
        };
        typedef unsigned short TIndex;

        Model(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, TPrimitiveType type = PT_TRIANGLELIST);

        void Draw(const Transform* transform) const;


    protected:
        void Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount);

        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        TPrimitiveType  m_PrimitiveType;
        
    };

    typedef SmartPtr<Model, ResourceCOM> TModelPtr;

}


#endif // MODEL_H