#version 330
#include <common/global_uniform.glsl>

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

out vec4 color;
out vec2 texCoord0;
out vec3 texCoord1;
out vec3 normal;
out vec4 pos;
out vec4 comp_pos;
uniform samplerCube texture0;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main()
{
	vec3 vertex = in_Vertex;

	
	float scale = 1.f;
	color = in_Color;
	texCoord0 = in_TexCoord0;
	normal = normalize(texCoord1 = (u_matModel * vec4(in_Vertex,1)).xyz);
	pos = vec4(normal*scale,1.0f);
	float displacement = rgb2grayscale(texture(texture0,pos.xyz).rgb);
	displacement = clamp(displacement,0.0f,1.f);
	pos += vec4(normal*scale*-0.02+scale*normal*displacement*0.02,0);
	comp_pos = u_matViewProjection *  pos;
	gl_Position = comp_pos;
}
#endif


#ifdef _FRAGMENT_

in vec4 color;
in vec2 texCoord0;
in vec3 normal;
in vec4 pos;
in vec4 comp_pos;

layout(location = 0) out vec4 out_Color;
uniform samplerCube texture0;
uniform sampler2D texture1;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main()
{
	float offset = rgb2grayscale(texture(texture0,pos.xyz).rgb);
	out_Color = vec4(texture(texture1,vec2(offset,0)).rgb,1.0f);
}
#endif