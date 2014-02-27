#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 color;
out vec2 texCoord0;
out vec3 normal;
out vec4 pos;
out vec4 comp_pos;
uniform samplerCube texture0;

void main()
{
	vec3 vertex = in_Vertex;

	
	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	normal = ((u_matModel * vec4(in_Vertex,1)).xyz);//normalize(mat3(u_matModel) * in_Normal);
	pos = vec4(normal,1.0f);
	float displacement = texture(texture0,pos.xyz).r;
	pos += vec4(normal*displacement*0.005,0);
	comp_pos = u_matViewProjection *  pos;
	gl_Position = comp_pos;
}
#endif


#ifdef _FRAGMENT_

in vec4 color;
in vec2 texCoord0;
in vec3 normal;
in vec4 pos;
in vec4 comp_pos;

layout(location = 0) out vec4 out_Color;
layout(location = 1) out vec3 out_Normal;
layout(location = 2) out vec3 out_Position;
uniform samplerCube texture0;

void main()
{

	out_Color = vec4(texture(texture0,vec3(texCoord0,1.0f)).rgb,1.0f);
	out_Normal = normal;
	out_Position = pos.xyz;
}



#endif