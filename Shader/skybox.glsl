#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_

uniform mat4 u_matProjectionSkybox;
in vec3 in_Vertex;
out vec3 texCoord0;



void main()
{
    gl_Position = u_matProjectionSkybox*vec4(in_Vertex*100,1.0);
	
	texCoord0 = mat3(u_matView)*in_Vertex;
}
#endif

#ifdef _FRAGMENT_

uniform samplerCube texture0;

in vec3 texCoord0;

out vec4 out_Color;

void main()
{
	out_Color = vec4(1.0);
	/*if((u_textureFlags & 1 ) != 0)
		out_Color = vec4(texture(texture0, texCoord0).rgb,1.0f);*/
}
#endif