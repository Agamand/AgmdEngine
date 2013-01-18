#version 330
#include "global_uniform.glsl"
#include "global_light_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
out vec4 v_Color;


void main(){
	
	v_Color = in_Color;
	gl_Position =  u_matProjection * u_matView * u_matModel * vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

in vec4 v_Color;
out vec4 out_color;

void main()
{
	out_color = v_Color;
}
#endif