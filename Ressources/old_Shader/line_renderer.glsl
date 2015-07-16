#version 330
#ifdef _VERTEX_

uniform mat4 u_projection;
in vec2 in_Vertex;

void main()
{
	gl_Position = u_projection*vec4(in_Vertex,0,1);
}
#endif

#ifdef _FRAGMENT_
out vec4 out_Color;
void main()
{
	out_Color = vec4(1,0,0,0);
}



#endif