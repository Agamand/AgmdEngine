-- Vertex
#version 330

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

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform int RenderFlags;

void main()
{
	vec3 vertex = in_Vertex;
	
	color = in_Color;
	texCoord0 = in_TexCoord0;
	texCoord1 = in_TexCoord1;
	texCoord2 = in_TexCoord2;
	texCoord3 = in_TexCoord3;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix* vec4(vertex,1.0f);
}

-- Fragment
#version 330

in vec4 color;
in vec2 texCoord0;
in vec2 texCoord1;
in vec2 texCoord2;
in vec2 texCoord3;

out vec4 out_Color;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform int RenderFlags;

void main()
{
	out_Color = color;
	
	if((RenderFlags & 2 ) != 0)
	{
		out_Color = texture2D(texture0, texCoord0);
		//out_Color = vec4(texCoord0,0.0,1.0);
	}
	if((RenderFlags & 4 ) != 0)
	{
		out_Color = texture2D(texture1, texCoord1);
		//out_Color = vec4(texCoord1,0.0,1.0);
	}
	if((RenderFlags & 8 ) != 0)
	{
		out_Color = texture2D(texture2, texCoord2);
		out_Color = vec4(texCoord3,0.0,1.0);
	}
	if((RenderFlags & 16 ) != 0)
	{
		out_Color = texture2D(texture3, texCoord3);
		out_Color = vec4(texCoord2.x,texCoord2.y,0.0,1.0);
	}
}