/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Matrix4.h>
#include <Core/Model/Model.h>
#include <Core/Model/Material.h>
#include <Core/Driver.h>
#include <Debug/Exception.h>
#include <Debug/New.h>
#include <Core/MatStack.h>
#include <Core/ResourceManager.h>
#include <Vector3.h>
#include <Core/Tools/BoundingSphere.h>
#include <CommonDefines.h>

/** DEBUG **/

#include <Renderer/OpenGL/GlDriver.h>

/** **/
namespace Agmd
{
    Model::Model()
    {}
    Model::Model(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, TPrimitiveType type) :
    m_PrimitiveType(type),m_indexed(true), m_maxDraw(-1)
    {
        vec3 _max, _min;
        if(verticesCount > 0)
        {
            _max = _min = vertices[0].position;

            for(a_uint32 i = 1; i < verticesCount;i++)
            {
                _min.x = min(_min.x,vertices[i].position.x);
                _min.y = min(_min.y,vertices[i].position.y);
                _min.z = min(_min.z,vertices[i].position.z);

                _max.x = max(_max.x,vertices[i].position.x);
                _max.y = max(_max.y,vertices[i].position.y);
                _max.z = max(_max.z,vertices[i].position.z);
            }

             m_bounding = BoundingSphere(_min,_max);
        }
        Generate(G_NORMAL,vertices,verticesCount,indices,indicesCount);
        GenerateBuffer(vertices,verticesCount,indices,indicesCount,type);
    }

    Model::Model( TVertex* vertices, a_uint32 verticesCount,TPrimitiveType type/*= PT_TRIANGLELIST*/ ) : m_PrimitiveType(type),m_indexed(false)
    {
        vec3 _max, _min;
        if(verticesCount > 0)
        {
            _max = _min = vertices[0].position;

            for(a_uint32 i = 1; i < verticesCount;i++)
            {
                _min.x = min(_min.x,vertices[i].position.x);
                _min.y = min(_min.y,vertices[i].position.y);
                _min.z = min(_min.z,vertices[i].position.z);

                _max.x = max(_max.x,vertices[i].position.x);
                _max.y = max(_max.y,vertices[i].position.y);
                _max.z = max(_max.z,vertices[i].position.z);
            }

            m_bounding = BoundingSphere(_min,_max);
        }
        GenerateBuffer(vertices,verticesCount,type);
    }
    void Model::GenerateBuffer(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, TPrimitiveType type)
    {
        m_PrimitiveType = type ,m_indexed =true;
        Assert(vertices != NULL);
        Assert(indices  != NULL);

        //Generate(G_NORMAL,vertices,verticesCount,indices,indicesCount);
       // Generate((GenerateType)((G_TANGENT)), vertices, verticesCount, indices, indicesCount);

        TDeclarationElement Elements[] =
        {
            {0, ELT_USAGE_POSITION,     ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_NORMAL,       ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_DIFFUSE,      ELT_TYPE_COLOR},
            {0, ELT_USAGE_TEXCOORD0,    ELT_TYPE_FLOAT2},
            {0, ELT_USAGE_TANGENT,      ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_BINORMAL,     ELT_TYPE_FLOAT3}
        };

        //m_Declaration it's smartptr -> auto delete :D 
//         m_VertexBuffer.Release();
//         m_IndexBuffer.Release();
        if(!m_Declaration)
            m_Declaration = Driver::Get().CreateVertexDeclaration(Elements, sizeof(TVertex));

        m_VertexBuffer = Driver::Get().CreateVertexBuffer(verticesCount, 0, vertices);
        m_IndexBuffer  = Driver::Get().CreateIndexBuffer(indicesCount, 0, indices);
    
    }
    void Model::GenerateBuffer(TVertex* vertices, a_uint32 verticesCount,TPrimitiveType type)
    {
        Assert(vertices != NULL);
        m_PrimitiveType = type ,m_indexed =false;
        //Generate(G_TANGENT, vertices, verticesCount);

        TDeclarationElement Elements[] =
        {
            {0, ELT_USAGE_POSITION,     ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_NORMAL,       ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_DIFFUSE,      ELT_TYPE_COLOR},
            {0, ELT_USAGE_TEXCOORD0,    ELT_TYPE_FLOAT2},
            {0, ELT_USAGE_TANGENT,      ELT_TYPE_FLOAT3},
            {0, ELT_USAGE_BINORMAL,     ELT_TYPE_FLOAT3}

        };
        m_Declaration = Driver::Get().CreateVertexDeclaration(Elements, sizeof(TVertex));

        m_VertexBuffer = Driver::Get().CreateVertexBuffer(verticesCount, 0, vertices);
    }





    void Model::Draw(const Transform* transform) const
    {
        if(!m_VertexBuffer.GetBuffer())
            return;
        if(transform)
            Driver::Get().SetCurrentTransform(transform);
        Driver::Get().SetDeclaration(m_Declaration);
        Driver::Get().SetVertexBuffer(0, m_VertexBuffer);
        if(m_indexed)
        {
            Driver::Get().SetIndexBuffer(m_IndexBuffer);
            Driver::Get().DrawIndexedPrimitives(m_PrimitiveType,0,m_IndexBuffer.GetCount());
        }else
            Driver::Get().DrawPrimitives(m_PrimitiveType,0,m_VertexBuffer.GetCount());
        
    }

    void Model::Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount)
    {
        a_vector<vec3> normal(verticesCount,vec3(0.0f));
        a_vector<vec3> tangent(verticesCount,vec3(0.0f));
        a_vector<vec3> binormal(verticesCount,vec3(0.0f));
        //normal.resize(verticesCount,vec3(0.0f));

        //tangent.resize(verticesCount,vec4(0.0f));

        if(!type)
            return;
        int nFaces = indicesCount/3;
        // For all face calc Normal and Tangent
//         for(int i = 0; i < nFaces; i++)
//         {
//             vec3 edge1(vertices[indices[i*3+1]].position-vertices[indices[i*3]].position);
//             vec3 edge2(vertices[indices[i*3+2]].position-vertices[indices[i*3]].position);
//             vec3 _normal = cross(edge1,edge2);
//             _normal = normalize(_normal);
// 
//             if(type & G_NORMAL)
//             {
//                 vec3 _normal = cross(edge1,edge2);
//                 normal[indices[i*3]] += _normal;
//                 normal[indices[i*3+1]] += _normal;
//                 normal[indices[i*3+2]] += _normal;
//             }
//             
//             if(type & G_TANGENT) // and Binormal
//             {
//                 vec2 texEdge1(vertices[indices[i*3+1]].texCoords-vertices[indices[i*3]].texCoords);
//                 vec2 texEdge2(vertices[indices[i*3+2]].texCoords-vertices[indices[i*3]].texCoords);
// 
//                 vec3 t;
//                 vec3 b;
// 
//                 float det = (texEdge1.x * texEdge2.y) - (texEdge1.y * texEdge2.x);
// 
//                 if (det < 0.001f)
//                 {
//                     t = vec3(1.0f, 0.0f, 0.0f);
//                     b = vec3(0.0f, 1.0f, 0.0f);
//                 }
//                 else
//                 {
//                     det = 1.0f / det;
// 
//                     t.x = (texEdge2.y * edge1.x - texEdge1.y * edge2.x) * det;
//                     t.y = (texEdge2.y * edge1.y - texEdge1.y * edge2.y) * det;
//                     t.z = (texEdge2.y * edge1.z - texEdge1.y * edge2.z) * det;
// 
//                     b.x = (-texEdge2.x * edge1.x + texEdge1.x * edge2.x) * det;
//                     b.y = (-texEdge2.x * edge1.y + texEdge1.x * edge2.y) * det;
//                     b.z = (-texEdge2.x * edge1.z + texEdge1.x * edge2.z) * det;
// 
//                     t = normalize(t);
//                     b = normalize(b);
//                 }
// 
//                 vec3 bitangent = cross(_normal, t);
//                 float handedness = (dot(bitangent, b) < 0.0f) ? -1.0f : 1.0f;
// 
//                 tangent[indices[i*3]] += vec4(t,handedness);
//                 tangent[indices[i*3+1]] += vec4(t,handedness);
//                 tangent[indices[i*3+2]] += vec4(t,handedness);
//             }
//         }
        // For all face calc Normal and Tangent
        for(int i = 0; i < nFaces; i++)
        {
            vec3 edge1(vertices[indices[i*3+1]].position-vertices[indices[i*3]].position);
            vec3 edge2(vertices[indices[i*3+2]].position-vertices[indices[i*3]].position);
            vec3 _normal = cross(edge1,edge2);
            _normal = normalize(_normal);

            if(type & G_NORMAL)
            {
               
                normal[indices[i*3]] += _normal;
                normal[indices[i*3+1]] += _normal;
                normal[indices[i*3+2]] += _normal;
            }
            if(type & G_TANGENT)
            {
                vec2 texEdge1(vertices[indices[i*3+1]].texCoords-vertices[indices[i*3]].texCoords);
                vec2 texEdge2(vertices[indices[i*3+2]].texCoords-vertices[indices[i*3]].texCoords);
                float coef = 1/ (texEdge1.x * texEdge2.y - texEdge2.x * texEdge1.y);
                

                vec3 _tangent, _binormal;
                _tangent.x += coef * ((edge1.x * texEdge2.y)  + (edge2.x * -texEdge1.y));
                _tangent.y += coef * ((edge1.y * texEdge2.y)  + (edge2.y * -texEdge1.y));
                _tangent.z += coef * ((edge1.z * texEdge2.y)  + (edge2.z * -texEdge1.y));
                tangent[indices[i*3]]    += _tangent;
                tangent[indices[i*3+1]]  += _tangent;
                tangent[indices[i*3+2]]  += _tangent;

                _binormal = cross(_normal,_tangent);

                binormal[indices[i*3]]    +=_binormal;
                binormal[indices[i*3+1]]  +=_binormal;
                binormal[indices[i*3+2]]  +=_binormal;
            }
        }

        for(a_uint32 i = 0; i < normal.size(); i++)
        {
            if(type & G_NORMAL)
            {
                normal[i] = normalize(normal[i]);
                vertices[i].normal = normal[i];
            }
            if(type & G_TANGENT)
            {
                vertices[i].binormal =  normalize(binormal[i]);
                vertices[i].tangent = normalize(tangent[i]);
            }
        }

    }

    void Model::Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount)
    {
        a_vector<vec3> normal(verticesCount,vec3(0.0f));
        a_vector<vec3> tangent(verticesCount,vec3(0.0f));
        a_vector<vec3> binormal(verticesCount,vec3(0.0f));

        if(!type)
            return;
        int nFaces = verticesCount/3;
        // For all face calc Normal and Tangent
        for(int i = 0; i < nFaces; i++)
        {
            vec3 edge1(vertices[i*3+1].position-vertices[i*3].position);
            vec3 edge2(vertices[i*3+2].position-vertices[i*3].position);
            vec3 _normal = cross(edge1,edge2);
            _normal = normalize(_normal);

            if(type & G_NORMAL)
            {
               
                normal[i*3] += _normal;
                normal[i*3+1] += _normal;
                normal[i*3+2] += _normal;
            }

//             if(type & G_TANGENT)
//             {
//                 vec2 texEdge1(vertices[i*3+1].texCoords-vertices[i*3].texCoords);
//                 vec2 texEdge2(vertices[i*3+2].texCoords-vertices[i*3].texCoords);
// 
//                 vec3 t;
//                 vec3 b;
// 
//                 float det = (texEdge1.x * texEdge2.y) - (texEdge1.y * texEdge2.x);
// 
//                 if (det < 0.001f)
//                 {
//                     t = vec3(1.0f, 0.0f, 0.0f);
//                     b = vec3(0.0f, 1.0f, 0.0f);
//                 }
//                 else
//                 {
//                     det = 1.0f / det;
// 
//                     t.x = (texEdge2.y * edge1.x - texEdge1.y * edge2.x) * det;
//                     t.y = (texEdge2.y * edge1.y - texEdge1.y * edge2.y) * det;
//                     t.z = (texEdge2.y * edge1.z - texEdge1.y * edge2.z) * det;
// 
//                     b.x = (-texEdge2.x * edge1.x + texEdge1.x * edge2.x) * det;
//                     b.y = (-texEdge2.x * edge1.y + texEdge1.x * edge2.y) * det;
//                     b.z = (-texEdge2.x * edge1.z + texEdge1.x * edge2.z) * det;
// 
//                     t = normalize(t);
//                     b = normalize(b);
//                 }
// 
//                 vec3 bitangent = cross(_normal, t);
//                 float handedness = (dot(bitangent, b) < 0.0f) ? -1.0f : 1.0f;
// 
//                 tangent[i*3] += vec4(t,handedness);
//                 tangent[i*3+1] += vec4(t,handedness);
//                 tangent[i*3+2] += vec4(t,handedness);
//             }
            if(type & G_TANGENT)
            {
                vec2 texEdge1(vertices[i*3+1].texCoords-vertices[i*3].texCoords);
                vec2 texEdge2(vertices[i*3+2].texCoords-vertices[i*3].texCoords);
                float coef = 1/ (texEdge1.x * texEdge2.y - texEdge2.x * texEdge1.y);

                vec3 _tangent, _binormal;
                _tangent.x += coef * ((edge1.x * texEdge2.y)  + (edge2.x * -texEdge1.y));
                _tangent.y += coef * ((edge1.y * texEdge2.y)  + (edge2.y * -texEdge1.y));
                _tangent.z += coef * ((edge1.z * texEdge2.y)  + (edge2.z * -texEdge1.y));
                tangent[i*3]    += _tangent;
                tangent[i*3+1]  += _tangent;
                tangent[i*3+2]  += _tangent;

               _binormal = cross(_normal,_tangent);

               binormal[i*3]    +=_binormal;
               binormal[i*3+1]  +=_binormal;
               binormal[i*3+2]  +=_binormal;
            }
        }

        for(a_uint32 i = 0; i < normal.size(); i++)
        {
            if(type & G_NORMAL)
            {
                normal[i] = normalize(normal[i]);
                vertices[i].normal = normal[i];
            }
            if(type & G_TANGENT)
            {
                vertices[i].binormal =  normalize(binormal[i]);
                vertices[i].tangent =  normalize(tangent[i]);
            }
        }

    }

    void Model::Export( TVertex*& vertices,TIndex*& index,int& vcount, int& icount)
    {
        vcount = m_VertexBuffer.GetCount();
        icount = m_IndexBuffer.GetCount();
        vertices = new TVertex[vcount];
        index = new TIndex[icount];
        TVertex* v = m_VertexBuffer.Lock();
        std::memcpy(vertices,v,vcount*sizeof(TVertex));
        m_VertexBuffer.Release();
        TIndex* i = m_IndexBuffer.Lock();
        std::memcpy(index,i,icount*sizeof(TIndex));
        m_IndexBuffer.Release();
    }

    void Model::setMaxDraw( int param1 )
    {
        m_maxDraw = param1;
    }




}