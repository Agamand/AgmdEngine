#version 330

#ifdef _VERTEX_

uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 v_Color;
out vec2 v_tex;


void main(){
	
	v_Color = in_Color;
	v_tex = in_TexCoord0;
	gl_Position =  u_matProjection * vec4(in_Vertex,1);
}

#endif

#ifdef _FRAGMENT_
#define PI 3.1415926
uniform float u_time;

in vec2 v_tex;
in vec4 v_Color;
out vec4 out_color;

void main()
{
	out_color = vec4(abs(cos(2*PI*(v_tex.x+u_time*100))),abs(cos(2*PI*(v_tex.y+u_time*100))),1,1);
}
#endif