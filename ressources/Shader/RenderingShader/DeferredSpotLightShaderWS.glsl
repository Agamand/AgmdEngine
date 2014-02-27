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

uniform sampler2DShadow texture3;

uniform mat4 depthVPBias;

in vec2 v_TexCoord0;

out vec4 out_color;

#define PI 3.14159265359
uniform float u_offset = 0.4f;
uniform float u_bias = -0.005f;


vec2 offsetTable[13] = vec2[]
(
	vec2(0,0),
	vec2(0,1),
	vec2(-1,0),
	vec2(1,0),
	vec2(0,-1),
	vec2(cos(-3*PI/4),sin(-3*PI/4)),
	vec2(cos(PI/4),sin(PI/4)),
	vec2(cos(3*PI/4),sin(3*PI/4)),
	vec2(cos(-PI/4),sin(-PI/4)),
	vec2( -0.94201624, -0.39906216 ),
	vec2( 0.94558609, -0.76890725 ),
	vec2( -0.094184101, -0.92938870 ),
	vec2( 0.34495938, 0.29387760 )
);

vec3 textureToNormal(vec3 tex)
{
	return tex*2-vec3(0.5);
}

vec3 getColor(float a)
{
	return vec3(clamp(cos(4*PI/3*a-4/3*PI),0,1),clamp(cos(4*PI/3*a-2*PI/3),0,1),clamp(cos(4*PI/3*a),0,1));
	//return vec3(clamp(cos(4*PI/3*a),0,1),clamp(cos(4*PI/3*a+2*PI/3),0,1),clamp(cos(4*PI/3*a+4/3*PI),0,1));
}

void main()
{
	vec4 shadowCoord = depthVPBias*vec4(texture(texture2,v_TexCoord0).rgb,1.0);

	float offset = u_bias;//0.005f;
	shadowCoord.z += offset;
    float shadow = textureProj(texture3, shadowCoord,0);
	float visibility = shadow;
	if(visibility < 1.0f)
	{
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 5; i++)
			{
				shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*u_offset*j/700.0f*shadowCoord.w, 0, 0.0f));
				visibility += shadow;
			}
			for(int i = 5; i < 9; i++)
			{
				shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*u_offset*j/700.0f*shadowCoord.w, 0, 0.0f));
				visibility += shadow;
			}
			
			for(int i = 9; i < 13; i++)
			{
				shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*u_offset*j/700.0f*shadowCoord.w, 0, 0.0f));
				visibility += shadow;
			}
			
		}
		visibility /=13*4+1;
	}
	
	
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
		float Att = 1.0f;// - dist/(l_range);
		if(Att < 0.0f)
			Att = 0.0f;
		
		float spotAtt = 0.0;
		if (spotEffect > l_innerAngle) {
			spotAtt = 1.0;
		}else if(spotEffect > l_outerAngle)
		{
			spotAtt = pow(2.0f,clamp((spotEffect - l_outerAngle) / (l_innerAngle - l_outerAngle), 0.0, 1.0)) - 1.0f;
			spotAtt = clamp((spotEffect - l_outerAngle) / (l_innerAngle - l_outerAngle), 0.0, 1.0);
		}
		lighting = lambertTerm*spotAtt*Att;
	}
	
	
	vec4 color = texture(texture0, v_TexCoord0);
	if(color.a < 1.0f)
		discard;
	out_color =  vec4(color);//vec4(vec3(lighting*visibility),color.a);
}

#endif