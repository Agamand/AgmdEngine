#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_texCoord;

void main(void)
{
    v_texCoord = in_TexCoord0;

    gl_Position = u_matProjection*u_matModel*vec4(in_Vertex,1.0f);
}
#endif

#ifdef _FRAGMENT_

#define NUMBERWAVES 4

const float Eta = 0.15; // Water
const float PI = 3.141592654;
const float G = 9.81;

uniform float u_waterPlaneLength = 200.0;

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
    vec3 vertex = vec3(v_texCoord.x*u_waterPlaneLength-u_waterPlaneLength/2.0 + 0.5, -v_texCoord.y*u_waterPlaneLength+u_waterPlaneLength/2.0 + 0.5, 0.0);

    vec4 finalVertex;

    finalVertex.x = vertex.x;
    finalVertex.y = vertex.y;
    finalVertex.z = vertex.z;
    finalVertex.w = 1.0;

    vec3 finalNormal;
    
    finalNormal.x = 0;
    finalNormal.y = 0;
    finalNormal.z = 0;

    for (int i = 0; i < NUMBERWAVES; i++)
    {
        vec2 direction = normalize(u_waveDirections[i]);
        float speed = u_waveParameters[i].x;
        float amplitude = u_waveParameters[i].y;
        float wavelength = u_waveParameters[i].z;
        float steepness = u_waveParameters[i].w;

        float frequency = sqrt(G*2.0*PI/wavelength);
        float phase = speed*frequency;
        float alpha = frequency*dot(direction, vertex.xy)+phase*u_passedTime;
        
        finalVertex.x += steepness*amplitude*direction.x*cos(alpha);
        finalVertex.y += steepness*amplitude*direction.y*cos(alpha);
        finalVertex.z += amplitude*sin(alpha);
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
        float alpha = frequency * dot(direction, finalVertex.xy) + phase*u_passedTime;
                
        finalNormal.x += direction.x * wavelength * amplitude * cos(alpha);
        finalNormal.y += direction.y * wavelength * amplitude * cos(alpha);
        finalNormal.z += steepness * wavelength * amplitude * sin(alpha);
    }

    finalNormal.x = -finalNormal.x;
    finalNormal.y = -finalNormal.y;
    finalNormal.z = 1.0-finalNormal.z;
    
    out_Color = vec4(normalToTexture(finalNormal), 1.0);
    
}

#endif