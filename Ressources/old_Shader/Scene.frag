#version 130
#define MAX_LIGHT 8

uniform int enableLight[MAX_LIGHT];
uniform sampler2D texture;
in vec3 normal, vVertex;
in int _uselight, _usetexture;






vec4 pointLighting(int index)
{
	
	vec3 lightDir = vec3(gl_LightSource[index].position.xyz - vVertex);
	float dist = length(lightDir);
	vec3 halfVector = normalize(gl_LightSource[index].halfVector.xyz);
	vec3 eyeVec = -vVertex;
	vec3 n,halfV,viewV,ldir;
	float NdotL,NdotHV;
	vec4 diffuse,ambientGlobal, ambient;
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[index].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[index].ambient;
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	vec4 color = ambientGlobal;
	float att;
	
	/* a fragment shader can't write a verying variable, hence we need
	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
	
	/* compute the dot product between normal and ldir */
	NdotL = max(dot(n,normalize(lightDir)),0.0);

	if (NdotL > 0.0) {
	
		att = 1.0 / (gl_LightSource[index].constantAttenuation +
				gl_LightSource[index].linearAttenuation * dist +
				gl_LightSource[index].quadraticAttenuation * dist * dist);
		color += att * (diffuse * NdotL + ambient);
	
		
		halfV = normalize(halfVector);
		NdotHV = max(dot(n,halfV),0.0);
		color += att * gl_FrontMaterial.specular * gl_LightSource[index].specular * pow(NdotHV,gl_FrontMaterial.shininess);
		//color += basecolor;
	}
	return color;
	//gl_FragColor += color;
}

void dirLighting(int index)
{
	vec3 lightDir = vec3(gl_LightSource[index].position.xyz - vVertex);
	float dist = length(lightDir);
	vec3 halfVector = normalize(gl_LightSource[index].halfVector.xyz);
	vec3 eyeVec = -vVertex;
}

vec4 spotLighting(int index)
{
	vec3 lightDir = vec3(gl_LightSource[index].position.xyz - vVertex);
	float dist = length(lightDir);
	vec3 halfVector = normalize(gl_LightSource[index].halfVector.xyz);
	vec3 eyeVec = -vVertex;
	vec3 n,halfV;
	float NdotL,NdotHV;
	vec4 diffuse,ambientGlobal, ambient;
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[index].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[index].ambient;
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	vec4 color = ambientGlobal;
	float att = 1.0,spotEffect;

	
	/* a fragment shader can't write a verying variable, hence we need
	a new variable to store the normalized interpolated normal */
	n = normalize(normal);
	
	/* compute the dot product between normal and ldir */
	NdotL = max(dot(n,normalize(lightDir)),0.0);
	float cos_inner_cone_angle = gl_LightSource[0].spotCosCutoff;
	const float cos_outer_cone_angle = 0.8;	
	float cos_inner_minus_outer_angle =	cos_inner_cone_angle - cos_outer_cone_angle;
	if (NdotL > 0.0) {
	
		
		spotEffect = dot(normalize(gl_LightSource[index].spotDirection), normalize(-lightDir));
		float spotAtt = 0.0;
		if (spotEffect > cos_inner_cone_angle) {
			spotAtt = 1.0;
		}else if(spotEffect > cos_outer_cone_angle)
		{
			spotAtt = clamp((spotEffect - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);
		}
			spotEffect = pow(spotEffect, gl_LightSource[index].spotExponent);
			att = spotEffect / (gl_LightSource[index].constantAttenuation +
					gl_LightSource[index].linearAttenuation * dist +
					gl_LightSource[index].quadraticAttenuation * dist * dist);
				
			color += att* spotAtt * (diffuse * NdotL + ambient);
		
			
			halfV = normalize(halfVector);
			NdotHV = max(dot(n,halfV),0.0);
			color += att * gl_FrontMaterial.specular * gl_LightSource[index].specular * pow(NdotHV,gl_FrontMaterial.shininess);
			//color += basecolor;
	}
	return color;
	//gl_FragColor += color;
}

vec4 applyLighting(int index )
{
	if(enableLight[index] == 0)
		return vec4(0,0,0,0);

	if(gl_LightSource[index].spotCosCutoff != 180.0)
		return spotLighting(index);
	else
		return pointLighting(index);
}
vec4 applyAllLighting()
{
	vec4 totLighting = vec4(0,0,0,0); 
	for(int i = 0; i < MAX_LIGHT; i++)
		totLighting += applyLighting(i);
	
	return totLighting;
	//gl_FragColor = basecolor*totLighting;//( + totLighting)*0.5;
}

vec4 applyTexture()
{
	return texture2D(texture,gl_TexCoord[0].st);
}

void main (void)
{
	vec4 basecolor = vec4(1,1,1,1);
	if(_usetexture !=0)
	{
		basecolor *= applyTexture();
	}
	
	
	if(_uselight !=0)
	{
		basecolor *= applyAllLighting();
	}
	
	gl_FragColor = vec4(basecolor);
	
}