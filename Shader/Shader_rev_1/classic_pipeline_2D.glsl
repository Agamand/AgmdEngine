-- Vertex
#version 330

in vec3 in_Vertex;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 color;
out vec2 texCoord0;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int RenderFlags;

void main()
{
	vec3 vertex = in_Vertex;
	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix* vec4(vertex,1.0f);
}

-- Fragment
#version 330

in vec4 color;
in vec2 texCoord0;

out vec4 out_Color;
uniform sampler2D texture0;
uniform int RenderFlags;

void main()
{
	out_Color = color;
	
	if((RenderFlags & 2 ) != 0)
		out_Color = texture2D(texture0, texCoord0);
}