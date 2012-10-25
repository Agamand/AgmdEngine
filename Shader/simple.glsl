-- Vertex
#version 400
in vec3 in_Vertex;
in vec2 in_TexCoord0;
out vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main()
{
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(in_Vertex,1.0);
	texCoord0 = in_TexCoord0;
}

-- Fragment
#version 400

uniform int RenderFlags;
uniform sampler2D texture0;

in vec2 texCoord0;

out vec4 out_Color;

void main()
{
	out_Color = vec4(1.0);
	if((RenderFlags & 2 ) != 0)
		out_Color = vec4(texture(texture0, texCoord0).rgb,1.0f);
}