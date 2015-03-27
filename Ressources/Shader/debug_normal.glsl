#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord0;
in vec4 in_Tangent;

out vec3 tangent;
out vec3 binormal;

out VertexNormal
{
    vec3 normal;
    vec3 pos;
    vec3 tangent;
    vec3 binormal;
} VertexN;

uniform sampler2D texture5;
uniform sampler2D texture4;


vec3 _lightDir = vec3(1.0,1.0,1.0);

void main()
{
    vec3 vertex = in_Vertex;

    vec2 texCoord0 = in_TexCoord0;
    VertexN.normal = mat3(u_matModel)*in_Normal;
    VertexN.tangent = mat3(u_matModel)* in_Tangent.xyz;
    VertexN.binormal = cross(VertexN.normal, VertexN.tangent) * in_Tangent.w;

    if((u_textureFlags & 64 ) != 0)
    {
        vec4 dv = texture( texture5, texCoord0);
        float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
        float du = 2.0f;
        vertex = vertex + in_Normal * df * du; 
    }
    mat3 mtangent = mat3(VertexN.tangent.x, VertexN.binormal.x, VertexN.normal.x,
                         VertexN.tangent.y, VertexN.binormal.y, VertexN.normal.y,
                         VertexN.tangent.z, VertexN.binormal.z, VertexN.normal.z);
                         
    vec4 pos =  u_matModel * vec4(vertex,1.0f);
    
    gl_Position = u_matProjection * u_matView * pos;
    VertexN.pos = vec3(pos);
}

#endif

#ifdef _GEOMETRY_

#extension GL_geometry_shader4 : enable
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

out vec4 color;

in VertexNormal
{
    vec3 normal;
    vec3 pos;
    vec3 tangent;
    vec3 binormal;
} VertexNormal[];


void drawLine( vec4 _color, vec3 from, vec3 to )
{
    color = _color;
    gl_Position = u_matProjection * u_matView * vec4( from, 1.0 );
    EmitVertex();

    color = _color;
    gl_Position = u_matProjection * u_matView * vec4( to, 1.0 );
    EmitVertex();

    EndPrimitive();
}

void main( void )
{
    for( int i = 0 ; i < gl_VerticesIn ; i++ )
    {
        drawLine(vec4(1,0,0,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].normal);
        //drawLine(vec4(0,1,0,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].tangent);
        //drawLine(vec4(0,0,1,1),VertexNormal[i].pos, VertexNormal[i].pos + VertexNormal[i].binormal);
    }
    EndPrimitive ();
}
#endif

#ifdef _FRAGMENT_

in vec4 color;
out vec4 out_Color;

void main()
{
    out_Color = color;
}

#endif