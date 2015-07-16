#version 330

#include "global_uniform.glsl"
//#define DEBUG_TEXCOORD
#ifdef _VERTEX_


in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec4 in_Tangent;

out vec3 tangent;
out vec3 binormal;

out vec4 color;
out vec2 texCoord0;
out vec3 normal;
out vec3 lightDir;
out vec3 eye;
out vec4 v_shadowCoord;

uniform float du = 20.0f;
uniform sampler2D texture5;

vec3 _lightDir = vec3(1.0,1.0,1.0);

uniform vec3 light;
uniform mat4 depthMVP = mat4(1.0);

void ApplyShadow()
{
	v_shadowCoord = depthMVP*u_matModel*vec4(in_Vertex,1.0);
}

void main()
{
	vec3 vertex = in_Vertex;

	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	normal = mat3(u_matModel)*in_Normal;
	lightDir = light;
	tangent = mat3(u_matModel) * in_Tangent.xyz;
	binormal = cross(normal, tangent) * in_Tangent.w;
	vec4 pos = u_matView * u_matModel * vec4(in_Vertex, 1.0f);
	eye = -(pos.xyz / pos.w);
	if((u_textureFlags & 32) != 0)
	{
		vec4 dv = texture2D( texture5, texCoord0);
		float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
		vertex = vertex + in_Normal * df * du; 
	}
	gl_Position = u_matProjection * u_matView * u_matModel * vec4(vertex,1.0f);
	
	/*DEBUG*/
	//gl_Position = u_matProjection * u_matView * u_matModel * vec4(10*texCoord0.x,0.0,10*texCoord0.y,1.0);
	ApplyShadow();
}
#endif


#ifdef _FRAGMENT_

in vec3 tangent;
in vec3 binormal;

in vec4 color;
in vec2 texCoord0;
in vec3 normal;
in vec3 lightDir;
in vec3 eye;
in vec4 v_shadowCoord;

layout(location = 0) out vec4 out_Color;
uniform sampler2D texture0;
uniform int RenderFlags;
uniform sampler2D texture4;
uniform sampler2D texture5;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);
float offset = 0.4;
vec2 offsetTable[9] = 
{
	vec2(0,0),
	vec2(-offset,offset),
	vec2(0,offset),
	vec2(offset,offset),
	vec2(-offset,0),
	vec2(offset,0),
	vec2(-offset,-offset),
	vec2(0,-offset),
	vec2(offset,-offset)
};

void directLight()
{
	mat3 mtangent = mat3(tangent.x , binormal.x , normal.x,
						 tangent.y, binormal.y, normal.y,
						 tangent.z  , binormal.z  , normal.z);
	mat3 inv_mtangent = inverse(mtangent);
						 
	vec3 _eye = eye;
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	if((u_textureFlags & 16 ) != 0)
	{
		//L = mtangent*L;
		normalize(L);
		N = normalize( texture2D(texture4, texCoord0).xyz * 2.0 - 1.0);
		N = inv_mtangent*N;
		N = normalize(N);
	}
	
	float lambertTerm = dot(N,L);
	out_Color = vec4(out_Color.xyz*(lambertTerm),out_Color.w);
}

float getshadow(vec4 shadowCoord)
{
	shadowCoord = shadowCoord/shadowCoord.w;

	float bias = 0.005;
	shadowCoord.z += bias;

	float shadow = 1.0;
	float dist = texture( u_shadowMap,shadowCoord.xy).z;

	if (shadowCoord.w > 0.0)
		shadow = dist < v_shadowCoord.z  ? 0.5f : 1.0f;

	return shadow;
}

float getShadow()
{
	float shadow = 1.0f;
	for(int i = 0; i < 9; i++)
		shadow +=getshadow(v_shadowCoord+vec4(offsetTable[i]/700.0,0,0));

	shadow /= 9;
	return shadow;
}



void main()
{
	out_Color = vec4(1.0);
	if((u_textureFlags & 1 ) != 0)
		out_Color = texture2D(texture0, texCoord0);
		
	//if((RenderFlags & 32 ) != 0)
		//out_Color = texture2D(texture5, texCoord0);
	//directLight();
	return;
	float vis = 1.0f;
	/*for (int i=0;i<4;i++)
	{
		vis -= 0.2*(1.0-getshadow(i));
	}*/
	vis =getShadow();

	
	//out_Color = texture(u_shadowMap,texCoord0);
		
	out_Color *=vis;
	//out_Color = vec4(1.0f);
}



#endif