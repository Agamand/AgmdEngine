#version 330



#ifdef _VERTEX_

#include "global_uniform.glsl"

in vec3 in_Vertex;
in vec3 in_Normal;
out vec3 v_Normal;
out vec3 v_Position;

void main(){
	mat4 modelviewproj = u_matProjection * u_matView * u_matModel;
	v_Normal = mat3(u_matModel) * in_Normal;
	v_Position = (u_matModel * vec4(in_Vertex,1)).xyz;
	gl_Position = modelviewproj * vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

#include "global_light_uniform.glsl"

in vec3 v_Normal;
in vec3 v_Position;
out vec4 out_color;

vec3 normalToTexture(vec3 normal)
{
	vec3 n = normalize(normal);
	return vec3(0.5) + n/2;
}

vec4 dir()
{
	vec3 N = normalize(v_Normal);
	vec3 L = normalize(l_dir.xyz);
	float lambertTerm = max(dot(N,L),0.0);
	return vec4(vec3(lambertTerm),1.0f);
}

vec4 point()
{
	vec3 N = normalize(v_Normal);
	vec3 L = l_position.xyz-v_Position;
	float dist = length(L);
	L = normalize(L);
	float lambertTerm = max(dot(N,L),0.0);
	return vec4(vec3(lambertTerm),1.0f);
}

vec4 spot()
{
	return vec4(0);
}

vec4 lighting()
{
	switch(l_type)
	{
		case 0:
			return dir();
		case 1:
			return point();
		case 2:
			return spot();
		default:
			return vec4(1);
	}

}

void main()
{
	out_color = lighting();
}

#endif