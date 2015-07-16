#version 330

#include <common/global_uniform.glsl>

#ifdef _VERTEX_

in vec3 in_Vertex;

void main()
{
	gl_Position = u_matViewProjection*u_matModel*vec4(in_Vertex,1);
}
#endif


#ifdef _FRAGMENT_
layout(location = 0) out vec4 out_Color;
void main()
{
	out_Color = vec4(1,0,0,1);//vec4(,1.0f);
}
#endif