#version 330
#include <common/global_uniform.glsl>
#include <common/light_uniform.glsl>
#include <common/color.glsl>
#include <common/light.glsl>
#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Binormal;
out vec2 v_texCoord0;
out vec3 v_normal;
out vec3 v_binormal;
out vec3 v_tangent;
out vec4 v_Color;
out vec3 v_pos;

void main(){
	
    v_Color = in_Color;
    v_pos = in_Vertex;
    v_texCoord0 = in_TexCoord0;
    v_normal = mat3(u_matModel)*in_Normal;
    if(length(in_Binormal) < 0.1)
    {
      v_binormal = mat3(u_matModel)*vec3(0,1,0);
    }else v_binormal = mat3(u_matModel)*in_Binormal;
    if(length(in_Tangent) < 0.1)
    {
      v_tangent = mat3(u_matModel)*vec3(1,0,0);
    }else v_tangent = mat3(u_matModel)*in_Tangent;



    vec4 worldPosition = u_matModel * vec4(in_Vertex,1);
    v_pos = worldPosition.xyz;
    gl_Position = u_matProjectionView * worldPosition;
}
#endif

#ifdef _FRAGMENT_

uniform sampler2D texture0; // diffuse
uniform sampler2D texture1; // bump/normal map
uniform sampler2D texture2; // specular map

in vec4 v_Color;
in vec3 v_pos;
in vec3 v_normal;
in vec3 v_binormal;
in vec3 v_tangent;
in vec2 v_texCoord0;
out vec4 out_color;


void main()
{
    out_color = v_Color;
   
    vec3 normal = normalize(v_normal);
    vec4 diffuse = texture(texture0,v_texCoord0);
    vec4 nMap = texture(texture1,v_texCoord0);
    vec3 n = rgb2normal(nMap.rgb);

    vec4 sMap = texture(texture2,v_texCoord0);

    vec3 vTangent = v_tangent;

    vec3 vBitangent = v_binormal; 
    mat3 tbn = mat3(vTangent, vBitangent, normal);
    n = normalize(tbn*n);
    //n = normal;
    //mat3 mTBN = transpose(tbn); 
    //out_color.rgb  = vec3(rgb2grayscale(out_color.rgb));
    //out_color.rgb = diffuse.rgb;

    float specular = rgb2grayscale(sMap.rgb);
    vec4 color = vec4(0);
    //for(int i = 0; i < u_lightCount; ++i)
    color = applyAllLight(diffuse,v_pos,n,u_viewPosition.xyz,1.0f,u_light,u_lightCount);
    out_color.rgb = color.rgb;
    //out_color.rgb = normal2rgb(n);
    out_color.a =diffuse.a;


}
#endif