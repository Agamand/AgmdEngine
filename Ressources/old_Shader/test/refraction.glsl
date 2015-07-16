#version 330
#include <common/global_uniform.glsl>
#include <common/global_light_uniform.glsl>
#include <common/color.glsl>


#ifdef _VERTEX_

uniform sampler2D texture1;
in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normal;
out vec2 v_texCoord0;
out vec3 v_position;
out vec3 v_normal;
void main(){
	
	vec3 ref = vec3(1,0,0);

	v_texCoord0 = in_TexCoord0;
	vec3 normal = v_normal = in_Normal;
	float h =1;
	v_position = (u_matModel * (vec4(in_Vertex,1)+vec4(0,0,h*10,0))).xyz;
	gl_Position = u_matViewProjection * u_matModel * (vec4(in_Vertex,1)+vec4(0,0,h*0,0));
}
#endif

#ifdef _FRAGMENT_
#include <common/global_uniform.glsl>
const float Eta = 0.15;
uniform samplerCube texture0;
uniform sampler2D texture1;
uniform vec3 u_camPosition;
in vec3 v_position;
in vec2 v_texCoord0;
in vec3 v_normal;
out vec4 out_color;

void main()
{
	vec3 normal =v_normal;// rgb2normal(texture(texture1,v_texCoord0*1).rgb);
	vec3 viewDirection = normalize(v_position - u_camPosition); 
	vec3 refraction = refract(viewDirection,normal,Eta);
	vec3 reflection = reflect(viewDirection, normal);	
	vec4 refractionColor = texture(texture0, refraction);
	vec4 reflectionColor = texture(texture0, reflection);
	float fresnel = Eta + (1.0 - Eta) * pow(max(0.0, 1.0 - dot(-viewDirection, normal)), 5.0);
	out_color = vec4(refractionColor);//mix(refractionColor, reflectionColor, fresnel);
}
#endif