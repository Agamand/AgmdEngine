#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;
out vec4 v_Color;
out vec2 v_texCoord0;

void main(){
	
	v_Color = in_Color;
	gl_Position =  u_matProjection * u_matView * u_matModel * vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

in vec4 v_Color;
out vec4 out_color;

void main(){
	out_color = v_Color;
}
#endif