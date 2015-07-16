#version 330

#include "global_2D_uniform.glsl"
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec2 in_TexCoord0;
out vec2 texCoord0;

void main()
{
	texCoord0 = in_TexCoord0;
	gl_Position = u_matProjection * u_matModel * vec4(in_Vertex,1.0f);
}
#endif


#ifdef _FRAGMENT_

uniform vec4 color = vec4(1.0);
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