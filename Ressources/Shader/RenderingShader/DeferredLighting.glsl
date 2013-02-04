#version 330
#ifdef _VERTEX_


uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord0;

void main(){
	mat4 modelviewproj = u_matProjection;
	v_TexCoord0 = in_TexCoord0;
	gl_Position = modelviewproj * vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_

#include "global_light_uniform.glsl"
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 v_TexCoord0;

out vec4 out_color;

vec3 textureToNormal(vec3 tex)
{
	return tex*2-vec3(0.5);
}

vec4 dir()
{
	vec3 N = normalize(textureToNormal(texture( texture1, v_TexCoord0 ).xyz));
	vec3 L = normalize(l_dir.xyz);
	float lambertTerm = max(dot(N,L),0.0);
	return vec4(vec3(lambertTerm),1.0f);
}

vec4 point()
{
	vec3 N = normalize(textureToNormal(texture( texture1, v_TexCoord0 ).xyz));
	vec3 position = texture2D( texture2, v_TexCoord0 ).xyz;
	vec3 L = l_position.xyz-position;
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
	//alpha discard
	float alpha  = texture( texture0, v_TexCoord0 ).a;
	if(alpha < 1.0f)
		discard;
}

#endif