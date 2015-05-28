#ifndef _LIGHT_GLSL_
#define _LIGHT_GLSL_

#include "math.glsl"
#include "light_struct.glsl"
vec4 lightPoint(vec3 normal, vec4 position, vec3 lightPos, vec3 lightDir, vec4 diffuse = vec4(1))
{

	return diffuse;
}

vec4 lightDirection(vec3 normal, vec3 lightDir, vec4 diffuse = vec4(1))
{
	vec3 N = normal;
	vec3 L = -normalize(lightDir);
	float lambertTerm = clamp(max(dot(N,L),0.0),0,1);
	vec3 _color = diffuse.rgb*0.1f; //ambient
	if(lambertTerm > 0)
	{
		_color +=diffuse.rgb*lambertTerm;

		//no specular;
	}
	return vec4(_color,diffuse.a);
}

vec4 lightSpot(vec3 normal, vec4 position, vec3 lightPos, vec3 lightDir, vec4 diffuse = vec4(1), float spotAngles = 30.0)
{

	return diffuse;
}

const float fSpecularPower = 5;
const float fSpecularIntensity = 0.41; 
void light_direction(inout vec4 diffuse, inout vec4 _specular, vec3 pos, vec3 normal,vec3 eye, float specular, lightInfoStruct light)
{
	vec3 direction = light.l_dir.xyz;
	vec3 reflectedVector = normalize(reflect(direction, normal));
	diffuse += vec4(vec3(1)*max(0.0, pow(dot(normal, -direction)*0.5+0.5,2)),0);
 	float fSpecularFactor = dot(eye, reflectedVector); 
	if (fSpecularFactor > 0) 
   	{ 
       fSpecularFactor = pow(fSpecularFactor, fSpecularPower); 
       _specular += vec4(vec3(fSpecularIntensity * fSpecularFactor), 0.0f);
   	}
}



void light_point(inout vec4 diffuse, inout vec4 _specular, vec3 pos, vec3 normal,vec3 eye, float specular, lightInfoStruct light)
{
	float dist = length(pos-light.l_position.xyz);
	vec3 direction = normalize(pos-light.l_position.xyz);
	float Att = dist > light.l_range ? 0.0f : 1.0f - dist/(light.l_range);
	vec3 reflectedVector = normalize(reflect(direction, normal)); 
	diffuse += vec4(vec3(1)*max(0.0, pow(dot(normal, -direction)*0.5+0.5,2)),0)*Att;
 	float fSpecularFactor = dot(eye, reflectedVector);
	//_specular += vec4(vec3(fSpecularFactor),0);
	if (fSpecularFactor > 0) 
   	{ 
       fSpecularFactor = pow(fSpecularFactor, fSpecularPower); 
       _specular += vec4(vec3(fSpecularIntensity * fSpecularFactor), 0.0)*Att;
   	}
}

void light_spot(inout vec4 diffuse, inout vec4 _specular, vec3 pos, vec3 normal,vec3 eye, float specular, lightInfoStruct light)
{
	float dist = length(pos-light.l_position.xyz);
	vec3 direction = normalize(pos-light.l_position.xyz);
	float spotEffect = max(dot(direction,light.l_dir.xyz),0.0f); 
	float lambertTerm = dot(normal, -direction);
	vec3 reflectedVector = normalize(reflect(direction, normal)); 	
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
       _specular += vec4(vec3(fSpecularIntensity * fSpecularFactor), 0.0f)*spotAtt*Att;
   	}

   	diffuse += vec4(vec3(1)*max(0.0f, pow(lambertTerm*0.5f+0.5f,2)),0)*spotAtt*Att;
}


void applyLighting(inout vec4 diffuse, inout vec4 _specular, vec3 pos,vec3 normal, vec3 eye,float specular, lightInfoStruct light)
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

vec4 applyAllLight(vec4 diffuse, vec3 pos, vec3 normal, vec3 cameraPos, float specular, lightInfoStruct lights[MAX_LIGHT], int count)
{

	vec3 eye  = normalize(cameraPos-pos);
	vec4 lighting = vec4(0,0,0,1),
		 _specular = vec4(0);

	for(int i = 0; i < count && i < MAX_LIGHT; ++i)
	{
		applyLighting(lighting,_specular,pos,normal,eye,specular,lights[i]);
	}
	return diffuse*0.1f + diffuse*lighting + _specular;
}


#endif /* _LIGHT_GLSL_ */