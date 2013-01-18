-- Vertex
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform int RenderFlags;
uniform vec2 uvrep;
#define NUMBERWAVES 4

const float Eta = 0.15; // Water
const float PI = 3.141592654;
const float G = 9.81;

uniform float u_waterPlaneLength;

uniform float u_passedTime;

uniform vec4 u_waveParameters[NUMBERWAVES];
uniform vec2 u_waveDirections[NUMBERWAVES];

in vec3 in_Vertex;
in vec4 in_Color;

out vec4 _color;
out vec4 EyePos; 
out vec4 ShadowVertex;
out vec2 texcoord0;
out vec3 normal;
 
void main() 
{     
    texcoord0 = gl_Vertex.xz*uvrep; 
    EyePos = projectionMatrix*viewMatrix*modelMatrix*in_Vertex; 
    gl_Position = EyePos; 
    ShadowVertex = texture0Matrix*in_Vertex;
	_color = in_color;

	vec4 finalVertex;

	finalVertex.x = vertex.x;
	finalVertex.y = vertex.y;
	finalVertex.z = vertex.z;
	finalVertex.w = 1.0;

	vec3 finalNormal;
	
	finalNormal.x = 0.0;
	finalNormal.y = 0.0;
	finalNormal.z = 0.0;

	// see GPU Gems: Chapter 1. Effective Water Simulation from Physical Models 
	for (int i = 0; i < NUMBERWAVES; i++)
	{
		vec2 direction = normalize(u_waveDirections[i]);
		float speed = u_waveParameters[i].x;
		float amplitude = u_waveParameters[i].y;
		float wavelength = u_waveParameters[i].z;
		float steepness = u_waveParameters[i].w;

		float frequency = sqrt(G*2.0*PI/wavelength);
		float phase = speed*frequency;
		float alpha = frequency*dot(direction, vertex.xz)+phase*u_passedTime;
		
		finalVertex.x += steepness*amplitude*direction.x*cos(alpha);
		finalVertex.y += amplitude*sin(alpha);
		finalVertex.z += steepness*amplitude*direction.y*cos(alpha);
	}

	for (int i = 0; i < NUMBERWAVES; i++)
	{
		vec2 direction = normalize(u_waveDirections[i]);
		float speed = u_waveParameters[i].x;
		float amplitude = u_waveParameters[i].y;
		float wavelength = u_waveParameters[i].z;
		float steepness = u_waveParameters[i].w;

		float frequency = sqrt(G*2.0*PI/wavelength);
		float phase = speed*frequency;
		float alpha = frequency * dot(direction, finalVertex.xz) + phase*u_passedTime;
				
		finalNormal.x += direction.x * wavelength * amplitude * cos(alpha);
		finalNormal.y += steepness * wavelength * amplitude * sin(alpha);
		finalNormal.z += direction.y * wavelength * amplitude * cos(alpha);
	}

	finalNormal.x = -finalNormal.x;
	finalNormal.y = 1.0 - finalNormal.y;
	finalNormal.z = -finalNormal.z;
	finalNormal = normalize(finalNormal);
}

-- Fragment

uniform float time,blend; 
uniform float deform; 
uniform float taille; 
uniform vec2 speed;

in vec4 ShadowVertex; 
in vec4 EyePos;
in vec2 texcoord0;
in vec4 _color;
in vec3 normal;

vec3 lightDir = vec3(1.0,1.0,1.0);
 
void main (void) 
{ 
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
 
    out_color = mix(gl_Fog.color, color, fogFactor ); 
}