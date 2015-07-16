#version 330
#ifdef _VERTEX_

uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = in_TexCoord0;
	gl_Position = u_matProjection*vec4(in_Vertex,1.0f);
}

#endif
#ifdef _FRAGMENT_
#include "global_light_uniform.glsl"

uniform sampler2D texture0; 
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 v_TexCoord;
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
    vec4 diffuse = texture( texture0, gl_TexCoord[0].xy );
    vec4 position = texture( texture1, gl_TexCoord[0].xy );
    vec4 normal = texture( texture2, gl_TexCoord[0].xy );
	out_color = lighting();
}

#endif