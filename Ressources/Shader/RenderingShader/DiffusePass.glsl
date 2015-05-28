#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
in vec3 in_Normal;
in vec2 in_TexCoord0;
out vec4 v_Color;
out vec2 v_texCoord0;
out vec3 v_normal;

void main(){
	
	v_Color = in_Color;
	gl_Position =  u_matProjection *  vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

in vec4 v_Color;
out vec4 out_color;

void main(){
	out_color = lightDirection();
}
#endif