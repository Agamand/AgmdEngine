#version 330
#ifdef _VERTEX_
in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_texCoord0;
uniform mat4 u_matProjection;

void main(){
	v_texCoord0 = in_TexCoord0;
	gl_Position =  u_matProjection *vec4(in_Vertex,1);
}
#endif

#ifdef _FRAGMENT_
uniform mat4 depthVPBias;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2DShadow texture2;

in vec2 v_texCoord0;

out vec4 out_color;

float offset = 0.2;
vec2 offsetTable[13] = 
{
	vec2(0,0),
	vec2(0,1),
	vec2(-1,0),
	vec2(1,0),
	vec2(0,-1),
	vec2(-1,-1),
	vec2(1,1),
	vec2(-1,1),
	vec2(1,-1),
	vec2( -0.94201624, -0.39906216 ),
	vec2( 0.94558609, -0.76890725 ),
	vec2( -0.094184101, -0.92938870 ),
	vec2( 0.34495938, 0.29387760 )
};

void main(){
	vec4 shadowCoord = depthVPBias*vec4(texture(texture1,v_texCoord0).rgb,1.0f);
	shadowCoord = shadowCoord/shadowCoord.w;
	
	float bias = 0.005;
	shadowCoord.z -= bias;

    float shadow = texture(texture2,shadowCoord.xyz);
	float visibility = shadow;//(shadow < 1.0f ? 0.5f : 1.0f);//*0.25f;
	for(int i = 1; i < 5; i++)
	{
		shadow = texture(texture2,vec3(shadowCoord.xy + offsetTable[i]*offset/700.0f, shadowCoord.z));
		visibility += shadow;
	}
	for(int i = 5; i < 9; i++)
	{
		shadow = texture(texture2,vec3(shadowCoord.xy + offsetTable[i]*offset/700.0f, shadowCoord.z));
		visibility += shadow;
	}
	
	for(int i = 9; i < 13; i++)
	{
		shadow = texture(texture2,vec3(shadowCoord.xy + offsetTable[i]*offset/700.0f, shadowCoord.z));
		visibility += shadow;
	}
	
	visibility /=13.0f;
	
	vec4 color = texture(texture0,v_texCoord0);
	out_color = vec4(color.rgb*visibility,color.a);
}

#endif