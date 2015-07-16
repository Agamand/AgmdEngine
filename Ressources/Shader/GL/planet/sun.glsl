#ifndef _DIFFUSE_GROUND_GLSL_
#define _DIFFUSE_GROUND_GLSL_

#version 330

#include <common/global_uniform.glsl>
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec3 v_position;
out vec2 v_TexCoord;
void main()
{
	v_TexCoord = in_TexCoord0;
	v_position = in_Vertex;
	vec4 viewPos = u_matView*u_matModel*vec4(in_Vertex,1.0f);
	float dist = length(viewPos.xyz);
	gl_PointSize = 2.0f/dist;
	gl_Position = u_matProjection * viewPos;

}
#endif

#ifdef _FRAGMENT_

uniform sampler2D texture0;

out vec4 out_Color0;

void main ()
{
	vec4 color = texture(texture0,gl_PointCoord).rgba;
	color.a = color.g;
	out_Color0 = vec4(color);
}

#endif
#endif /* _DIFFUSE_GROUND_GLSL_ */