#version 330
#include "global_uniform.glsl"
#include "global_light_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
out vec4 v_Color;
out vec3 v_pos;

void main(){
	
	v_Color = in_Color;
	v_pos = in_Vertex;
	gl_Position = u_matViewProjection * u_matModel * vec4(in_Vertex+vec3(4,0,0),1);
}
#endif

#ifdef _FRAGMENT_

//uniform sampler2D texture0;
in vec4 v_Color;
in vec3 v_pos;
out vec4 out_color;

void main()
{
	out_color = v_Color;
	//float offset = (length(v_pos)-1)/0.05f;

	//out_color = vec4(texture(texture0,vec2(offset,0)).rgb,1);	
}
#endif