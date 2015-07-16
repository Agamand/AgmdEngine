#version 330
#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;
out vec4 v_Color;
out vec2 v_tex;


void main(){
	
	v_Color = in_Color;
	v_tex = in_TexCoord;
	gl_Position = u_matViewProjection *  u_matModel * vec4(vertex,1.0f);
}

#endif

#ifdef _FRAGMENT_
//#define PI 3.1415926
uniform float time;

in vec2 v_tex;
in vec4 v_Color;
out vec4 out_color;

void main()
{
	out_color = vec4(time,1,1,1);
}
#endif