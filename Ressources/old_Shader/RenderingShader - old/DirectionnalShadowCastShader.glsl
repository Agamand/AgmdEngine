#version 330
#include "global_uniform.glsl"
#ifdef _VERTEX_
in vec3 in_Vertex;

uniform mat4 depthMVP;

out vec3 v_position;
void main(){
	gl_Position =  depthMVP * u_matModel *vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

out float out_Depth;

void main(){

	out_Depth = gl_FragCoord.z;
}
#endif