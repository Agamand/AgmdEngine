#ifndef _DIFFUSE_GROUND_GLSL_
#define _DIFFUSE_GROUND_GLSL_

#version 330
#ifdef _VERTEX_

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec3 v_position;
out vec2 v_TexCoord;
void main()
{
	v_TexCoord = in_TexCoord0;
	v_position = in_Vertex;
	gl_Position = vec4(2*in_Vertex,1.0f);

}
#endif

#ifdef _FRAGMENT_

uniform mat4 u_position_matrix;
uniform sampler2D texture0;
uniform sampler2D texture1;
in vec2 v_TexCoord;
in vec3 v_position;

layout(location = 0) out vec4 out_Color0;

void main ()
{
	float offset = texture(texture0,v_TexCoord).r;
	vec3 color = texture(texture1,vec2(offset,0)).rgb;
	out_Color0 = vec4(color,1.0f);
}

#endif
#endif /* _DIFFUSE_GROUND_GLSL_ */