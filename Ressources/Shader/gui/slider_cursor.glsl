#version 330

#include <common/global_2d_uniform.glsl>

#ifdef _VERTEX_


uniform vec2 u_size;

in vec3 in_Vertex;


void main()
{
    vec3 vertex = in_Vertex;
    gl_Position = u_matProjection * u_matModel * vec4(vertex*vec3(10,20,0)-vec3(5,0,0)+u_size.y*vec3(u_size.x,0,0),1.0f);
}
#endif

#ifdef _FRAGMENT_

out vec4 out_Color;
void main()
{
    out_Color = vec4(1);
}
#endif