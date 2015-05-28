#version 330

#include "global_2d_uniform.glsl"

#ifdef _VERTEX_

in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;
in vec2 in_TexCoord1;
in vec2 in_TexCoord2;
in vec2 in_TexCoord3;

out vec4 color;
out vec2 texCoord0;
out vec2 texCoord1;
out vec2 texCoord2;
out vec2 texCoord3;

void main()
{
    vec3 vertex = in_Vertex;
    
    color = in_Color;
    texCoord0 = in_TexCoord0;
    texCoord1 = in_TexCoord1;
    texCoord2 = in_TexCoord2;
    texCoord3 = in_TexCoord3;
    
    gl_Position = u_matProjection * u_matModel * vec4(vertex,1.0f);
}
#endif

#ifdef _FRAGMENT_

in vec4 color;
in vec2 texCoord0;
in vec2 texCoord1;
in vec2 texCoord2;
in vec2 texCoord3;

out vec4 out_Color;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    out_Color = vec4(1.0);
     if((u_textureFlags & 1 ) != 0)
    {
        out_Color = texture(texture0, texCoord0);
    }
    if((u_textureFlags & 2 ) != 0)
    {
        out_Color = texture(texture0, texCoord1);
    }
    if((u_textureFlags & 4 ) != 0)
    {
        out_Color = texture(texture0, texCoord2);
    }
    if((u_textureFlags & 8 ) != 0)
    {
        out_Color = texture(texture1, texCoord3);
    }
	//if(out_Color.a < 1.0f)
		//discard; //avoid transparent or semi-transparent pixel
}
#endif