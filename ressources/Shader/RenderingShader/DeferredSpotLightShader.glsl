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
	vec3 N = normalize(texture( texture1, v_TexCoord0 ).xyz);
	vec3 position = texture2D( texture2, v_TexCoord0 ).xyz;
	vec3 L = l_position.xyz-position;
	float dist = length(L);
	L = normalize(L);
	float lambertTerm = max(dot(N,L),0.0);
	float lighting = 0.0f;
	if( lambertTerm > 0.0f)
	{
		float spotEffect = dot(normalize(l_dir.xyz),L);
		float Att = dist > l_range ? 0.0f : 1.0f - dist/(l_range);
		float spotAtt = 0.0;
		if (spotEffect > l_innerAngle) {
			spotAtt = 1.0;
		}else if(spotEffect > l_outerAngle)
		{
			//spotAtt = pow(2.0f,clamp((spotEffect - l_outerAngle) / (l_innerAngle - l_outerAngle), 0.0, 1.0)) - 1.0f;
			spotAtt = clamp((spotEffect - l_outerAngle) / (l_innerAngle - l_outerAngle), 0.0, 1.0);
		}
		lighting = lambertTerm*spotAtt*Att;
	}
	
	
	//alpha discard
	vec4 color = texture(texture0, v_TexCoord0);
	if(color.a < 1.0f)
		discard;
	out_color = vec4(vec3(lighting),color.a);
}

#endif