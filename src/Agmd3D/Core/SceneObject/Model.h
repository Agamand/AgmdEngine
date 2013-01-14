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
#include <Core/SceneObject/Displayable.h>
#include <Utilities/SmartPtr.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Quaternion.h>

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

    class AGMD3D_EXPORT Model : public Displayable, public Resource
    {
    public :
        struct TVertex
        {
            vec3     position;
            vec3     normal;
            uint32   color;
            vec2     texCoords;
            vec4     tangent;
            vec4     boneWeight;
            vec4     boneIndices;
            float    boneCount;
        };

        struct Joint
        {
            std::string     m_Name;
            int32           m_ParentID;
            vec3            m_Pos;
            quat            m_Orient;
        };
        
        typedef std::vector<Joint> JointVector;
        typedef std::vector<mat4> Mat4Vector;
        typedef unsigned short TIndex;

        Model(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, TPrimitiveType type = PT_TRIANGLELIST);
        Model(Model* m);

        virtual void Render(TRenderPass pass) const;
        virtual void Draw() const;

        void SetTextureUnit(Texture tex, uint32 unit, uint32 renderpass = 0);
        void DisableTextureUnit(uint32 unit, uint32 renderpass = 0); 


    protected:

        Model();

        void Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount);

        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        TPrimitiveType  m_PrimitiveType;
        JointVector     m_vJoints;
        Mat4Vector        m_vmBindPose;
        Mat4Vector        m_vmInversedBindPose;
        bool            m_bHasBone;
        
    };

    typedef SmartPtr<Model, ResourceCOM> TModelPtr;

}


#endif // MODEL_H