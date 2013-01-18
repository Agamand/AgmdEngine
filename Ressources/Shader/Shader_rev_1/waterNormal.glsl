-- Vertex
#version 330

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_texCoord;

void main(void)
{
	v_texCoord = in_TexCoord0;

	gl_Position = projectionMatrix*modelMatrix*vec4(in_Vertex,1.0f);
}

-- Fragment
#version 330

#define NUMBERWAVES 4

const float Eta = 0.15; // Water
const float PI = 3.141592654;
const float G = 9.81;

uniform float u_waterPlaneLength = 10.0;

uniform float u_passedTime;

uniform vec4 u_waveParameters[NUMBERWAVES];
uniform vec2 u_waveDirections[NUMBERWAVES];

in vec2 v_texCoord;

out vec4 out_Color;

vec3 normalToTexture(vec3 orgNormal)
{
	return vec3(orgNormal.xyz*0.5+vec3(0.5));
}

void main(void)
{
	vec3 vertex = vec3(v_texCoord.x*u_waterPlaneLength-u_waterPlaneLength/2.0 + 0.5, 0.0, -v_texCoord.y*u_waterPlaneLength+u_waterPlaneLength/2.0 + 0.5);

	vec4 finalVertex;

	finalVertex.x = vertex.x;
	finalVertex.z = vertex.y;
	finalVertex.y = vertex.z;
	finalVertex.w = 1.0;

	vec3 finalNormal;
	
	finalNormal.x = 0;
	finalNormal.y = 0;
	finalNormal.z = 0;

/*	for (int i = 0; i < 4; i++)
	{
		vec2 direction = normalize(u_waveDirections[i]);
		float speed = u_waveParameters[i].x;
		float amplitude = u_waveParameters[i].y*4;
		float wavelength = u_waveParameters[i].z;
		float steepness = u_waveParameters[i].w;

		float frequency = sqrt(G*2.0*PI/wavelength);
		float phase = speed*frequency;
		float alpha = frequency*dot(direction, vertex.xy)+phase*u_passedTime;
		
		finalVertex.x += steepness*amplitude*direction.x*cos(alpha);
		finalVertex.y += steepness*amplitude*direction.y*cos(alpha);
		finalVertex.z += amplitude*sin(alpha);
	}

	for (int i = 0; i < 4; i++)
	{
		vec2 direction = normalize(u_waveDirections[i]);
		float speed = u_waveParameters[i].x;
		float amplitude = u_waveParameters[i].y*4;
		float wavelength = u_waveParameters[i].z;
		float steepness = u_waveParameters[i].w;

		float frequency = sqrt(G*2.0*PI/wavelength);
		float phase = speed*frequency;
		float alpha = frequency * dot(direction, finalVertex.xy) + phase*u_passedTime;
				
		finalNormal.x += direction.x * wavelength * amplitude * cos(alpha);
		finalNormal.y += direction.y * wavelength * amplitude * cos(alpha);
		finalNormal.z += steepness * wavelength * amplitude * sin(alpha);
	}

	finalNormal.x = -finalNormal.x;
	finalNormal.y = -finalNormal.y;
	finalNormal.z = 1.0-finalNormal.z;
	*/
	
	//V2
	
	/*for (int i = 0; i < 1; i++)
	{
		vec2 direction = normalize(u_waveDirections[i]);
		float speed = u_waveParameters[i].x;
		float amplitude = u_waveParameters[i].y*4;
		float wavelength = u_waveParameters[i].z;
		float steepness = u_waveParameters[i].w;

		float frequency = sqrt(G*2.0*PI/wavelength);
		float phase = speed*frequency*10.0f;
		float alpha = frequency + phase*u_passedTime;
		
		+v_texCoord.x*phase
				
		finalNormal.x += direction.x * wavelength * amplitude * cos(alpha+v_texCoord.x*phase);
		finalNormal.y += direction.y * wavelength * amplitude * cos(alpha+v_texCoord.y*phase);
		finalNormal.z += steepness * wavelength * amplitude * sin(alpha);
	}*/
	
	
	//V3
	
	vec2 dir =  vec2(1.0,3.0);
	dir = normalize(dir);
	
	finalNormal.x = sin(2*PI*u_passedTime/2.0f+PI*2*v_texCoord.x*dir.x+PI*2*v_texCoord.y*dir.y);
	//finalNormal.y = sin(PI*u_passedTime+v_texCoord.x*direction.x);
	
	//finalNormal = normalize(finalNormal);
	
	out_Color = vec4(normalToTexture(finalNormal), 1.0);
	
}
