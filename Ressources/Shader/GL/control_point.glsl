#version 330
#ifdef _VERTEX_

uniform mat4 u_projection;
in vec2 in_Vertex;


const float size = 5.0f;
void main()
{
	gl_PointSize = size;
	gl_Position = u_projection*vec4(in_Vertex,0,1);
}
#endif

#ifdef _FRAGMENT_

uniform sampler2D texture2;
out vec4 out_Color;

void main()
{
	out_Color = vec4(0,1,0,0);
}



#endif