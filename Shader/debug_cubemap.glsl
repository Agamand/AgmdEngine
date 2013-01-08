#version 330

#include "global_uniform.glsl"


#ifdef _VERTEX_

in vec3 in_Vertex;

out vec3 v_texCoord;

void main()
{
	vec3 vertex = in_Vertex*100 + vec3(0,0,200);
    gl_Position = u_matProjection*u_matView*u_matModel*vec4(vertex,1.0);
	v_texCoord = in_Vertex;
}
#endif

#ifdef _FRAGMENT_

uniform samplerCube texture0;

in vec3 v_texCoord;

out vec4 out_Color;

void main()
{
	out_Color = texture(texture0,v_texCoord);
}

#endif