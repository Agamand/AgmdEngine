#version 330
#ifdef _VERTEX_


uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord0;

void main(){
	v_TexCoord0 = in_TexCoord0;
	gl_Position = u_matProjection * vec4(in_Vertex,1);
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


void main()
{
	vec3 N = normalize(textureToNormal(texture( texture1, v_TexCoord0 ).xyz));
	vec3 L = normalize(l_dir.xyz);
	float lambertTerm = max(dot(N,L),0.0);
	
	//alpha discard
	vec4 color = texture(texture0, v_TexCoord0);
	if(color.a < 1.0f)
		discard;
	out_color = vec4(color.rgb,color.a);
}

#endif