#version 330

#include "global_uniform.glsl"

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec2 in_TexCoord0;
out vec2 texCoord0;



void main()
{
    gl_Position = u_matProjection*u_matView*u_matModel*vec4(in_Vertex,1.0);
    texCoord0 = in_TexCoord0;
}
#endif

#ifdef _FRAGMENT_

uniform sampler2D texture0;

in vec2 texCoord0;

out vec4 out_Color;

void main()
{
    out_Color = vec4(1.0);
    if((u_textureFlags & 1 ) != 0)
        out_Color = vec4(texture(texture0, texCoord0).rgb,1.0f);
}
#endif