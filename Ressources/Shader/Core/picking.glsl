#version 330
#ifdef _VERTEX_

uniform mat4 u_matProjection;
uniform mat4 u_matModel = mat4(1.0);

in vec3 in_Vertex;

void main()
{
	gl_Position = u_matProjection*u_matModel*vec4(in_Vertex,1.0f);
}

#endif

#ifdef _FRAGMENT_
uniform vec4 u_color;
out vec4 out_Color;

void main (void)
{
	out_Color = u_color;
}

#endif