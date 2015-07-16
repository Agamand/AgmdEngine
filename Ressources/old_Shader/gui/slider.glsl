#version 330

#include <common/global_2d_uniform.glsl>

#ifdef _VERTEX_


uniform vec2 u_size;

in vec3 in_Vertex;


void main()
{
    vec3 vertex = in_Vertex;   
    gl_Position = u_matProjection * u_matModel * vec4(vertex*vec3(u_size.x,2,0)+vec3(0,8,0),1.0f);
}
#endif

#ifdef _FRAGMENT_

out vec4 out_Color;
void main()
{
    out_Color = vec4(1.0);
}
#endif