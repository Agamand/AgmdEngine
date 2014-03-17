#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
out vec3 texCoord0;



void main()
{
	texCoord0 = mat3(u_matView)*in_Vertex;
    gl_Position = vec4(in_Vertex,1.0f);//u_matProjection*vec4(mat3(u_matView)*vec3(in_Vertex),1.0f);
}
#endif

#ifdef _FRAGMENT_

uniform samplerCube texture0;

in vec3 texCoord0;

out vec4 out_Color;

void main()
{
	out_Color = vec4(1.0f);//vec4(texture(texture0,texCoord0).rgb,1.0f);
}
#endif