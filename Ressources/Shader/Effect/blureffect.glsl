#version 330
#ifdef _VERTEX_

uniform mat4 u_matProjection;

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = in_TexCoord0;
	gl_Position = u_matProjection*vec4(in_Vertex,1.0f);
}

#endif

#ifdef _FRAGMENT_
uniform sampler2D texture0;

in vec2 v_TexCoord;
out vec4 out_Color;

uniform float offset = 0.005;
vec2 offsetTable[9] = 
{
	vec2(0,0),
	vec2(0,1),
	vec2(-1,0),
	vec2(1,0),
	vec2(0,-1),
	vec2(-1,-1),
	vec2(1,1),
	vec2(-1,1),
	vec2(1,-1)
};

vec4 blur()
{
	vec4 color = texture(texture0, v_TexCoord)*.25;
	for(int i = 1; i < 5; i++)
		color += texture(texture0, v_TexCoord + offsetTable[i]*offset)*.125;
	for(int i = 5; i < 9; i++)
		color += texture(texture0, v_TexCoord + offsetTable[i]*offset)*0.0625;
	return color;
}

void main (void)
{
	vec4 input1 = blur();
	out_Color = input1;
}

#endif
