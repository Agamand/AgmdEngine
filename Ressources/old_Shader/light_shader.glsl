#version 330
#include <common/global_uniform.glsl>
#include <common/color.glsl>
#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
out vec3 v_position;
out vec3 v_normal;
void main(){
	v_normal = mat3(u_matModel)*in_Normal;
	vec4 worldPosition = u_matModel * vec4(in_Vertex,1);
	v_position = worldPosition.xyz;
	gl_Position = u_matProjectionView * worldPosition;
}
#endif

#ifdef _FRAGMENT_

in vec3 v_position;
in vec3 v_normal;

out vec4 out_color;

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 eye = normalize(u_viewPosition.xyz-v_position);
	if(dot(eye,normal) < 0.5)
	 	out_color = vec4(1,1,1,1);
	else out_color = vec4(1,1,0,1);
	//out_color = vec4(vec3(normal2rgb(normal)),1);
}
#endif