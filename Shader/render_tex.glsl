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

void main (void)
{
    vec4 input1 = texture(texture0, v_TexCoord);
    out_Color = input1;
}

#endif