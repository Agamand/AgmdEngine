#version 330

#include "global_uniform.glsl"


#ifdef _VERTEX_

#define NUMBERWAVES 4
const float PI = 3.141592654;
const float G = 9.81;
uniform float u_passedTime;

uniform float u_waterPlaneLength = 200.0;

uniform vec4 u_waveParameters[NUMBERWAVES];
uniform vec2 u_waveDirections[NUMBERWAVES];

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec3 v_incident;

out vec3 v_bitangent;
out vec3 v_normal;
out vec3 v_tangent;

out vec2 v_texCoord;
out vec2 v_texCoord2;
out vec2 v_texCoord3;

#define M_PI = 3.141592654;

void main()
{
/*
    vec4 finalVertex;

    finalVertex.x = in_Vertex.x;
    finalVertex.y = in_Vertex.y;
    finalVertex.z = in_Vertex.z;
    finalVertex.w = 1.0;

    vec3 finalBitangent;
    vec3 finalNormal;
    vec3 finalTangent;

    finalBitangent.x = 0.0;
    finalBitangent.y = 0.0;
    finalBitangent.z = 0.0;
    
    finalNormal.x = 0.0;
    finalNormal.y = 0.0;
    finalNormal.z = 0.0;

    finalTangent.x = 0.0;
    finalTangent.y = 0.0;
    finalTangent.z = 0.0;

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
        float alpha = frequency*dot(direction, in_Vertex.xy)+phase*u_passedTime;
        
        finalVertex.x += steepness*amplitude*direction.x*cos(alpha);
        finalVertex.z += amplitude*sin(alpha);
        finalVertex.y += steepness*amplitude*direction.y*cos(alpha);
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
                
        // x direction
        finalBitangent.x += steepness * direction.x*direction.x * wavelength * amplitude * sin(alpha);
        finalBitangent.z += direction.x * wavelength * amplitude * cos(alpha);    
        finalBitangent.y += steepness * direction.x*direction.y * wavelength * amplitude * sin(alpha);    
    
        // y direction
        finalNormal.x += direction.x * wavelength * amplitude * cos(alpha);
        finalNormal.z += steepness * wavelength * amplitude * sin(alpha);
        finalNormal.y += direction.y * wavelength * amplitude * cos(alpha);

        // z direction
        finalTangent.x += steepness * direction.x*direction.y * wavelength * amplitude * sin(alpha);
        finalTangent.z += direction.y * wavelength * amplitude * cos(alpha);    
        finalTangent.y += steepness * direction.y*direction.y * wavelength * amplitude * sin(alpha);    
    }

    finalTangent.x = -finalTangent.x;
    finalTangent.y = 1.0 - finalTangent.y;
    finalTangent = normalize(finalTangent);

    finalBitangent.x = 1.0 - finalBitangent.x;
    finalBitangent.y = -finalBitangent.y;
    finalBitangent = normalize(finalBitangent);

    finalNormal.x = -finalNormal.x;
    finalNormal.z = 1.0 - finalNormal.z;
    finalNormal.y = -finalNormal.y;
    finalNormal = normalize(finalNormal);
    
    v_bitangent = finalBitangent;
    v_normal = finalNormal;
    v_tangent = finalTangent;
    
    v_texCoord = vec2(clamp((finalVertex.x+u_waterPlaneLength*0.5-0.5)/u_waterPlaneLength, 0.0, 1.0), clamp((-finalVertex.y+u_waterPlaneLength*0.5+0.5)/u_waterPlaneLength, 0.0, 1.0));

    vec4 vertex = u_matView*finalVertex;
    
    // We caculate in world space.
    v_incident = inverse(mat3(u_matView)) * vec3(vertex);    
                
    gl_Position = u_matProjection*vertex;
*/
    v_bitangent = vec3(0.0,1.0,0.0);
    v_normal = vec3(0.0,0.0,1.0);
    v_tangent = vec3(1.0,0.0,0.0);
    vec4 vertex  =  u_matView*u_matModel*vec4(in_Vertex,1.0);
    gl_Position = u_matProjection*vertex;
    v_texCoord = in_TexCoord0;//+vec2(u_passedTime,u_passedTime*0.5);
    v_texCoord2 = in_TexCoord0;//+vec2(u_passedTime*0.5,0);
    v_texCoord3 = in_TexCoord0;//+vec2(-0.5*u_passedTime,-0.5*u_passedTime);
    v_incident = inverse(mat3(u_matView))*vec3(vertex);//inverse(mat3(u_matView))*vec3(vertex.x*cos(M_PI*2*u_passedTime),vertex.y*sin(M_PI*2*u_passedTime),vertex.z);

}
#endif

#ifdef _FRAGMENT_

uniform sampler2D texture5, texture1;
uniform samplerCube texture0;
uniform vec3 u_dir;

in vec3 v_incident;

in vec3 v_bitangent;
in vec3 v_normal;
in vec3 v_tangent;

in vec2 v_texCoord;
in vec2 v_texCoord2;
in vec2 v_texCoord3;

out vec4 out_Color;

const float Eta = 0.15; // Water

const vec3 lightDir = vec3(1.0f,1.0f,-1.0f);

vec3 textureToNormal(vec4 orgNormalColor)
{
    return normalize(vec3(clamp(orgNormalColor.r*2.0 - 1.0, -1.0, 1.0), clamp(orgNormalColor.g*2.0 - 1.0, -1.0, 1.0), clamp(orgNormalColor.b*2.0 - 1.0, -1.0, 1.0)));
}

void directLight()
{            
    vec3 N = vec3(0.0f,0.0f,1.0f);
    if((u_textureFlags & 2 ) != 0)
         N = textureToNormal(texture(texture1, v_texCoord)); 
    vec3 L = normalize(lightDir);
N = vec3(0.0f,0.0f,1.0f);
    
    float lambertTerm = dot(N,L);

    if(lambertTerm > 0 && lambertTerm <= 1)
        out_Color = vec4(out_Color.xyz*(lambertTerm+0.5),out_Color.w);
    else out_Color = vec4(out_Color.xyz*0.5,out_Color.w);
}



void main()
{
    mat3 objectToWorldMatrix = mat3(1.0f);
    out_Color = vec4(1.0);
        
    vec3 worldIncident = normalize(v_incident);
    vec3 n1 = textureToNormal(texture(texture1, v_texCoord));
    vec3 n2 = textureToNormal(texture(texture1, v_texCoord2));
    vec3 n3 = textureToNormal(texture(texture1, v_texCoord3));
    vec3 objectNormal = normalize(n1+n2+n3);
    vec3 worldNormal = objectToWorldMatrix*objectNormal;
    vec3 refraction = refract(worldIncident, worldNormal, 1.0/*Eta*/);
    vec3 reflection = reflect(worldIncident, worldNormal);
    
    vec4 refractionColor = texture(texture0, refraction);
    vec4 reflectionColor = texture(texture0, reflection);
    
    float fresnel = Eta + (1.0 - Eta) * pow(max(0.0, 1.0 - dot(-worldIncident, worldNormal)), 5.0);
    
    out_Color = reflectionColor;//mix(refractionColor, reflectionColor, fresnel);
    
    //out_Color = texture(texture1, v_texCoord);
    //directLight();

    

}

#endif