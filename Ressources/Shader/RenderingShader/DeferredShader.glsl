#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 v_color;
out vec2 v_texCoord0;
out vec3 v_normal;
out vec4 v_pos;
uniform samplerCube texture0;



void main()
{

	v_color = in_Color;
	v_texCoord0 = in_TexCoord0;
	v_normal = normalize(mat3(u_matModel)*in_Normal);
	v_pos = u_matModel * vec4(in_Vertex,1);
	gl_Position = u_matViewProjection * vec4(v_pos.xyz,1);
}
#endif


#ifdef _FRAGMENT_

#include <common/color.glsl>

in vec4 v_color;
in vec2 v_texCoord0;
in vec3 v_normal;
in vec4 v_pos;

layout(location = 0) out vec4 out_Color;
layout(location = 1) out vec3 out_Normal;
layout(location = 2) out vec3 out_Position;
uniform sampler2D texture0;
void main()
{
	out_Color = vec4(normal2rgb(v_normal),1);//vec4(texture(texture0,v_texCoord0).rgb,1);
	out_Normal = normal2rgb(v_normal);
	out_Position = v_pos.xyz;
}



#endif