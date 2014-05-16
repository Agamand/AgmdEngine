#version 330

#include <common/global_uniform.glsl>

#ifdef _VERTEX_

in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;


out vec3 texCoord0;

void main()
{
	vec3 vertex = in_Vertex;

	
	float scale = 1.f;
	vec4 pos = u_matModel * vec4(in_Vertex,1);//vec4(normal*scale,1.0f);
	vec3 normal = normalize(pos.xyz);
	texCoord0 = normal;
	vec4 comp_pos = u_matViewProjection *  pos;
	gl_Position = u_matViewProjection*vec4(in_Vertex,1);
}
#endif


#ifdef _FRAGMENT_


in vec3 texCoord0;

layout(location = 0) out vec4 out_Color;

uniform samplerCube texture0;
uniform sampler2D texture1;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main()
{
	float offset = rgb2grayscale(texture(texture0,texCoord0).rgb);
	vec4 color = texture(texture1,vec2(offset,0));
	out_Color = vec4(color.rgb,1);//vec4(,1.0f);
}



#endif