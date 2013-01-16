#version 330

#include "global_2D_uniform.glsl"
#ifdef _VERTEX_

uniform int u_size;
uniform float u_offset;
uniform int u_char;


in vec4 in_Vertex;
out vec4 color;
out vec2 texCoord0;
const float tex_unit = 1.0f / 16.0f;

void main()
{
	vec3 vertex = in_Vertex.xyz;
	int id = 0;
	id += int(vertex.x)*1 + int(vertex.y)*2;
	color = vec4(1.0);
	vertex.x *= float(u_size);
	vertex.y *= float(u_size);
	
	
	
		
	switch(id)
	{
		case 0:
			texCoord0 = vec2(tex_unit * ((u_char % 16) + 0) + u_offset, 1.0f - tex_unit * ((u_char / 16) + 1) - u_offset);
			break;
		case 1:
			texCoord0 = vec2(tex_unit * ((u_char % 16) + 1) - u_offset, 1.0f - tex_unit * ((u_char / 16) + 1) - u_offset);
			break;
		case 2:
			texCoord0 = vec2(tex_unit * ((u_char % 16) + 0) + u_offset, 1.0f - tex_unit * ((u_char / 16) + 0) + u_offset);
			break;
		case 3:
			texCoord0 = vec2(tex_unit * ((u_char % 16) + 1) - u_offset, 1.0f - tex_unit * ((u_char / 16) + 0) + u_offset);
			break;
	}
	gl_Position = u_matProjection * u_matModel * vec4(vertex,1.0f);
}
#endif


#ifdef _FRAGMENT_

in vec4 color;
in vec2 texCoord0;


layout(location = 0) out vec4 out_Color;
uniform sampler2D texture0;

void main()
{
	out_Color = texture2D(texture0, texCoord0)*color;
	if(out_Color.a < 0.5f)
		discard;
}



#endif