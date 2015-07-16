#version 330
#include "global_uniform.glsl"
#ifdef _VERTEX_
in vec3 in_Vertex;

uniform mat4 depthMVP;

out vec3 v_position;
void main(){
    v_position = (u_matModel *vec4(in_Vertex,1)).xyz;
	gl_Position =  depthMVP * u_matModel *vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

//out float out_Depth;
in vec3 v_position;
layout(location = 0) out vec3 out_Color;
void main(){

	out_Color = v_position;
}
#endif
