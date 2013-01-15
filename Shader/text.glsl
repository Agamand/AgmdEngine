#version 330

#include "global_uniform.glsl"
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 color;
out vec2 texCoord0;

void main()
{
	vec3 vertex = in_Vertex;

	
	color = in_Color;
	texCoord0 = in_TexCoord0;

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
	out_Color = texture2D(texture0, texCoord0);
}



#endif