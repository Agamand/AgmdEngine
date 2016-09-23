/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Model/IcosahedronModel.h>

#include <list>
#include <stack>

namespace Agmd
{
    /*
        BASE ICOSAGEDRON
    */
#define X .525731112119133606f
#define Z .850650808352039932f
#define VERTEX_COUNT 12
#define TRIANGLE_COUNT 20


    typedef glm::detail::tvec3<a_uint16> ui16vec;

    struct Triangle
    {
        Triangle(ui16vec _index, a_uint8 _sublevel): index(_index), sublevel(_sublevel)
        {
        }

        ui16vec index;
        a_uint8 sublevel;
    };


    vec3 base_vertex[VERTEX_COUNT] =
    {
        vec3(-X, 0, Z),
        vec3(X, 0, Z),
        vec3(-X, 0, -Z),
        vec3(X, 0, -Z),
        vec3(0, Z, X),
        vec3(0, Z, -X),
        vec3(0, -Z, X),
        vec3(0, -Z, -X),
        vec3(Z, X, 0),
        vec3(-Z, X, 0),
        vec3(Z, -X, 0),
        vec3(-Z, -X, 0)
    };

    Triangle base_icosahdron[] = {
        Triangle(ui16vec(0, 4, 1), 0),
        Triangle(ui16vec(0, 9, 4), 0),
        Triangle(ui16vec(9, 5, 4), 0),
        Triangle(ui16vec(4, 5, 8), 0),
        Triangle(ui16vec(4, 8, 1), 0),
        Triangle(ui16vec(8, 10, 1), 0),
        Triangle(ui16vec(8, 3, 10), 0),
        Triangle(ui16vec(5, 3, 8), 0),
        Triangle(ui16vec(5, 2, 3), 0),
        Triangle(ui16vec(2, 7, 3), 0),
        Triangle(ui16vec(7, 10, 3), 0),
        Triangle(ui16vec(7, 6, 10), 0),
        Triangle(ui16vec(7, 11, 6), 0),
        Triangle(ui16vec(11, 0, 6), 0),
        Triangle(ui16vec(0, 1, 6), 0),
        Triangle(ui16vec(6, 1, 10), 0),
        Triangle(ui16vec(9, 0, 11), 0),
        Triangle(ui16vec(9, 11, 2), 0),
        Triangle(ui16vec(9, 2, 5), 0),
        Triangle(ui16vec(7, 2, 11), 0)
    };


    void createIcosahedron(int subDiv, /*out*/ std::vector<Model::TVertex>& vertices, std::vector<Model::TIndex>& indices)
    {
        Color c[] = {Color::red,Color::blue,Color::green};
        for (a_uint8 i = 0; i < VERTEX_COUNT; ++i)
        {
            Model::TVertex vertex;
            vertex.color = c[i % 3].ToABGR();//-1;// it's white :D
            vertex.position = base_vertex[i];
            vertex.normal = normalize(vertex.position);
            vertices.push_back(vertex);
        }
        std::list<Triangle> triangles(base_icosahdron, base_icosahdron + TRIANGLE_COUNT);
        while (!triangles.empty())
        {
            Triangle v = *triangles.begin();
            triangles.pop_front();
            if (v.sublevel >= subDiv)
            {
                for (a_uint8 i = 0; i < 3; i++)
                    indices.push_back(v.index[i]);
            }
            else //so tesselate !
            {
                vec3 p1 = vertices[v.index[0]].position, p2 = vertices[v.index[1]].position, p3 = vertices[v.index[2]].position;
                a_uint32 index_offset = vertices.size();

                vec3 new_point[3] = {p1 + (p2 - p1) / 2.0f,p2 + (p3 - p2) / 2.0f,p3 + (p1 - p3) / 2.0f};

                //vec3 np1 = p1 + (p2-p1)/2.0f,np2=p2 + (p3-p2)/2.0f,np3 = p3 + (p1-p3);

                // add points to vertex
                for (a_uint8 j = 0; j < 3; ++j)
                {
                    Model::TVertex vertex;
                    vertex.color = -1;// it's white :D
                    vertex.position = normalize(new_point[j]);
                    vertex.normal = normalize(vertex.position);
                    vertices.push_back(vertex);
                }

                triangles.push_back(Triangle(ui16vec(v.index[0], index_offset, index_offset + 2), v.sublevel + 1));
                triangles.push_back(Triangle(ui16vec(index_offset, v.index[1], index_offset + 1), v.sublevel + 1));
                triangles.push_back(Triangle(ui16vec(index_offset + 2, index_offset + 1, v.index[2]), v.sublevel + 1));
                triangles.push_back(Triangle(ui16vec(index_offset, index_offset + 1, index_offset + 2), v.sublevel + 1));
            }
        }
    }

    Icosahedron::Icosahedron(a_uint8 subdiv /*= 0*/):
        m_subdiv(subdiv > MAX_SUBDIV ? MAX_SUBDIV : (subdiv < 0 ? 0 : subdiv))
    {
        std::vector<TVertex> vertices;
        std::vector<TIndex> indices;

        createIcosahedron(m_subdiv, vertices, indices);
        GenerateBuffer(&vertices[0], vertices.size(), &indices[0], indices.size());
        m_bounding = BoundingSphere(vec3(0, 0, 0), 1);
    }

    void Icosahedron::setSubdiv(a_uint8 sd)
    {
        if (sd == m_subdiv || sd < 0 || sd > MAX_SUBDIV)
            return;


        m_subdiv = sd;
        std::vector<TVertex> vertices;
        std::vector<TIndex> indices;
        createIcosahedron(m_subdiv, vertices, indices);
        GenerateBuffer(&vertices[0], vertices.size(), &indices[0], indices.size());
    }

    a_uint8 Icosahedron::getSubdiv() const
    {
        return m_subdiv;
    }
}
