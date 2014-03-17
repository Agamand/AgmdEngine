#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;

uniform mat4 depthMVP;
uniform samplerCube texture0;
float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main(){

	float scale = 1.f;
	vec3 normal = normalize((u_matModel * vec4(in_Vertex,1)).xyz);//normalize(mat3(u_matModel) * in_Normal);
	vec4 pos = vec4(normal*scale,1.0f);
	float displacement = rgb2grayscale(texture(texture0,pos.xyz).rgb);
	displacement = clamp(displacement,0.0f,1.f);
	pos += vec4(normal*displacement*0.05*scale,0);
	gl_Position =  u_matViewProjection* pos;
}
#endif

#ifdef _FRAGMENT_

out float out_depth;

void main(){
	out_depth = gl_FragCoord.z;
}
#endif