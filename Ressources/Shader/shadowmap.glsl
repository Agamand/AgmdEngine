#version 330
#include "global_uniform.glsl"
#ifdef _VERTEX_
// Input vertex data, different for all executions of this shader.
in vec3 in_Vertex;

// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;

void main(){
	gl_Position =  depthMVP * u_matModel *vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_
// Ouput data
out float out_depth;


void main(){
	out_depth = gl_FragCoord.z;
}
#endif