#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;

uniform mat4 depthMVP;
uniform samplerCube texture0;
void main(){

	vec3 normal = normalize((u_matModel * vec4(in_Vertex,1)).xyz);//normalize(mat3(u_matModel) * in_Normal);
	vec4 pos = vec4(normal,1.0f);
	float displacement = texture(texture0,pos.xyz).r;
	pos += vec4(normal*displacement*0.005,0);
	gl_Position =  u_matViewProjection* pos;
}
#endif

#ifdef _FRAGMENT_

out float out_depth;

void main(){
	out_depth = gl_FragCoord.z;
}
#endif