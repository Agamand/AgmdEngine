#ifndef _LIGHT_HLSL_
#define _LIGHT_HLSL_

#include "math.hlsl"
#include "light_struct.hlsl"
float4 lightPoint(float3 normal, float4 position, float3 lightPos, float3 lightDir, float4 diffuse = float4(1))
{

	return diffuse;
}

float4 lightDirection(float3 normal, float3 lightDir, float4 diffuse = float4(1))
{
	float3 N = normal;
	float3 L = -normalize(lightDir);
	float lambertTerm = clamp(max(dot(N,L),0.0),0,1);
	float3 _color = diffuse.rgb*0.1f; //ambient
	if(lambertTerm > 0)
	{
		_color +=diffuse.rgb*lambertTerm;

		//no specular;
	}
	return float4(_color,diffuse.a);
}

float4 lightSpot(float3 normal, float4 position, float3 lightPos, float3 lightDir, float4 diffuse = float4(1), float spotAngles = 30.0)
{

	return diffuse;
}

const float fSpecularPower = 5;
const float fSpecularIntensity = 0.41; 
void light_direction(inout float4 diffuse, inout float4 _specular, float3 pos, float3 normal,float3 eye, float specular, lightInfoStruct light)
{
	float3 direction = light.l_dir.xyz;
	float3 reflectedVector = normalize(reflect(direction, normal));
	diffuse += float4(float3(1)*max(0.0, pow(dot(normal, -direction)*0.5+0.5,2)),0);
 	float fSpecularFactor = dot(eye, reflectedVector); 
	if (fSpecularFactor > 0) 
   	{ 
       fSpecularFactor = pow(fSpecularFactor, fSpecularPower); 
       _specular += float4(float3(fSpecularIntensity * fSpecularFactor), 0.0f);
   	}
}



void light_point(inout float4 diffuse, inout float4 _specular, float3 pos, float3 normal,float3 eye, float specular, lightInfoStruct light)
{
	float dist = length(pos-light.l_position.xyz);
	float3 direction = normalize(pos-light.l_position.xyz);
	float Att = dist > light.l_range ? 0.0f : 1.0f - dist/(light.l_range);
	float3 reflectedVector = normalize(reflect(direction, normal)); 
	diffuse += float4(float3(1)*max(0.0, pow(dot(normal, -direction)*0.5+0.5,2)),0)*Att;
 	float fSpecularFactor = dot(eye, reflectedVector);
	//_specular += float4(float3(fSpecularFactor),0);
	if (fSpecularFactor > 0) 
   	{ 
       fSpecularFactor = pow(fSpecularFactor, fSpecularPower); 
       _specular += float4(float3(fSpecularIntensity * fSpecularFactor), 0.0)*Att;
   	}
}

void light_spot(inout float4 diffuse, inout float4 _specular, float3 pos, float3 normal,float3 eye, float specular, lightInfoStruct light)
{
	float dist = length(pos-light.l_position.xyz);
	float3 direction = normalize(pos-light.l_position.xyz);
	float spotEffect = max(dot(direction,light.l_dir.xyz),0.0f); 
	float lambertTerm = dot(normal, -direction);
	float3 reflectedVector = normalize(reflect(direction, normal)); 	
 	float fSpecularFactor = dot(eye, reflectedVector); 
	float spotAtt = 0.0f;
	float Att = dist > light.l_range ? 0.0f : 1.0f - dist/(light.l_range);
	if (spotEffect > light.l_innerAngle) {
		spotAtt = 1.0f;
	}else if(spotEffect > light.l_outerAngle)
		spotAtt = clamp((spotEffect - light.l_outerAngle) / (light.l_innerAngle - light.l_outerAngle), 0.0f, 1.0f);
	
	if (fSpecularFactor > 0) 
   	{
       fSpecularFactor = pow(fSpecularFactor, fSpecularPower); 
       _specular += float4(float3(fSpecularIntensity * fSpecularFactor), 0.0f)*spotAtt*Att;
   	}

   	diffuse += float4(float3(1)*max(0.0f, pow(lambertTerm*0.5f+0.5f,2)),0)*spotAtt*Att;
}


void applyLighting(inout float4 diffuse, inout float4 _specular, float3 pos,float3 normal, float3 eye,float specular, lightInfoStruct light)
{
	switch(light.l_type)
	{
		case 0:
			light_direction(diffuse,_specular,pos,normal,eye,specular,light);
			break;
		case 1:
			light_point(diffuse,_specular,pos,normal,eye,specular,light);
			break;
		case 2:
			light_spot(diffuse,_specular,pos,normal,eye,specular,light);
			break;
	}
}

float4 applyAllLight(float4 diffuse, float3 pos, float3 normal, float3 cameraPos, float specular, lightInfoStruct lights[MAX_LIGHT], int count)
{

	float3 eye  = normalize(cameraPos-pos);
	float4 lighting = float4(0,0,0,1),
		 _specular = float4(0);

	for(int i = 0; i < count && i < MAX_LIGHT; ++i)
	{
		applyLighting(lighting,_specular,pos,normal,eye,specular,lights[i]);
	}
	return diffuse*0.1f + diffuse*lighting + _specular;
}


#endif /* _LIGHT_HLSL_ */