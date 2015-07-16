#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;



void main(){
	gl_Position = u_matViewProjection * u_matModel * vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

out float out_depth;

void main(){
	out_depth = gl_FragCoord.z;
}
#endif