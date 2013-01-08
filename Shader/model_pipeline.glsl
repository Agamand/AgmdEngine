#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_

#ifndef MAX_BONES
#define MAX_BONES 58
#endif 

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec4 in_Tangent;
in vec4 in_BoneWeight;
in vec4 in_BoneIndex;
in float in_BoneCount;

out vec3 tangent;
out vec3 binormal;

out vec4 color;
out vec2 texCoord0;
out vec3 normal;
out vec3 lightDir;
out vec3 eye;

uniform sampler2D texture5;

uniform mat4 boneMatrix[MAX_BONES];



vec3 _lightDir = vec3(1.0,1.0,1.0);

mat4 getSkinning()
{
    if(in_BoneCount > 1.0)
        return  mat4(1.0);
    
    mat4 transform = mat4(0.0);
    float weightsum = 0.0;
    
    int max = int(in_BoneCount);
    
    for(int i = 0; i < max; i++)
    {
        transform += boneMatrix[int(in_BoneIndex[i])]*in_BoneWeight[i];
        weightsum += in_BoneWeight[i];
    }
    
    transform /= weightsum;
    return transform;    
}

void main()
{
    vec3 vertex = in_Vertex;
    
    mat4 skinningMatrix = getSkinning();
    
    color = in_Color;
    texCoord0 = in_TexCoord0;
    normal = mat3(u_matModel) */*normalMatrix */ mat3(skinningMatrix) * in_Normal;
    lightDir = _lightDir;
    tangent = mat3(u_matModel) */*normalMatrix */ mat3(skinningMatrix) * in_Tangent.xyz;
    binormal = cross(normal, tangent) * in_Tangent.w;

    if((u_textureFlags & 32) != 0)
    {
        vec4 dv = texture2D( texture5, texCoord0);
        float df = 0.30*dv.x + 0.59*dv.y + 0.11*dv.z;
        float du = 2.0f;
        vertex = vertex + in_Normal * df * du; 
    }
    vec4 pos = u_matView * u_matModel * skinningMatrix * vec4(vertex, 1.0f);
    eye = -(pos.xyz / pos.w);
    gl_Position = u_matProjection* pos;
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

out vec4 out_Color;
uniform sampler2D texture0;
uniform sampler2D texture4;
uniform sampler2D texture5;

void directLight()
{
    mat3 mtangent = mat3(tangent.x , binormal.x , normal.x,
                         tangent.y, binormal.y, normal.y,
                         tangent.z  , binormal.z  , normal.z);
                         
    vec3 _eye = mtangent * eye;
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);
    if((u_textureFlags & 16 ) != 0)
    {
        L = mtangent*L;
        normalize(L);
        N = normalize( texture2D(texture4, texCoord0).xyz * 2.0 - 1.0);
        normalize(N);
    }
    
    float lambertTerm = dot(N,L);
    
    out_Color = vec4(out_Color.xyz*(lambertTerm),out_Color.w);

}

void main()
{
    out_Color = vec4(1.0);
    if((u_textureFlags & 1 ) != 0)
        out_Color = texture2D(texture0, texCoord0);
        
    //if((u_textureFlags & 32 ) != 0)
        //out_Color = texture2D(texture5, texCoord0);
    directLight();
}
#endif