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
uniform vec3 u_cameraPosition;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2DShadow texture3;

uniform mat4 depthVPBias;

in vec2 v_TexCoord0;

out vec4 out_color;
uniform float u_bias = -0.005f;
uniform float u_offset = 0.0f;

#define PI 3.14159265359
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


void main()
{
	float offset= 0.001f;
	vec4 shadowCoord = depthVPBias*vec4(texture(texture2,v_TexCoord0).rgb,1.0f);
	shadowCoord = shadowCoord/shadowCoord.w;
	
	float bias = 0.0005;
	shadowCoord.z += u_bias;
    float shadow = textureProj(texture3, shadowCoord,0);
	float visibility = shadow;
	for(int j = 0; j < 4; j++)
	{
		for(int i = 0; i < 5; i++)
		{
			shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*offset*j/1.0f*shadowCoord.w,0, 0.0f));
			visibility += shadow;	
		}
		for(int i = 5; i < 9; i++)
		{
			shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*offset*j/1.0f*shadowCoord.w,0, 0.0f));
			visibility += shadow;
		}
		
		for(int i = 9; i < 13; i++)
		{
			shadow = textureProj(texture3,shadowCoord + vec4(offsetTable[i]*offset*j/1.0f*shadowCoord.w,0, 0.0f));
			visibility += shadow;
		}
		
	}	

	visibility /=13*4+1;
	//visibility /=13.0f;
	float lighting = 0.0f;
	//alpha discard
	vec4 color = texture(texture0, v_TexCoord0);
	vec3 _color = color.rgb*0.1f; //ambient
	//if(visibility > 0.0f)
	{
		vec3 N = normalize(textureToNormal(texture( texture1, v_TexCoord0 ).xyz));
		vec3 L = -normalize(l_dir.xyz);
		float lambertTerm = max(dot(N,L),0.0);
		lambertTerm = clamp(lambertTerm,0,1);
		lighting = lambertTerm*visibility;
		if(lambertTerm > 0)
		{
			vec3 position = texture(texture2,v_TexCoord0).xyz;
			_color += color.rgb*lambertTerm; //diffuse
			vec3 eye = normalize(position-u_cameraPosition);
			vec3 _reflect = reflect(L,N);
			float specular = pow( max(dot(_reflect, eye), 0.0), 100);
			_color += color.rgb*specular;
		}
	}
	
	

	

	if(color.a < 1.0f)
		discard;
	out_color = vec4(_color.rgb*lighting,color.a);
}

#endif