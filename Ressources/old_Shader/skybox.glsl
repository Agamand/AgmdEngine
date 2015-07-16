#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
out vec3 texCoord0;



void main()
{
	texCoord0 = in_Vertex;//vec3(in_Vertex.x,-in_Vertex.y,in_Vertex.z)
	texCoord0.y = -texCoord0.y;
    gl_Position = (u_matProjectionView*vec4(in_Vertex,0.0f)).xyww;
}
#endif

#ifdef _FRAGMENT_

uniform samplerCube texture0;

in vec3 texCoord0;

out vec4 out_Color;

void main()
{
	out_Color = vec4(texture(texture0,texCoord0).rgb,1.0f);
}
#endif