#version 330
#include <common/global_uniform.glsl>

#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;


out vec2 texCoord0;
out vec3 normal;
out vec4 pos;


uniform samplerCube texture0;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

void main()
{
	vec3 vertex = in_Vertex;
	vec3 position;
	
	float scale = 1.f;
	texCoord0 = in_TexCoord0;
	normal = normalize( ( u_matModel * vec4(in_Vertex,1)).xyz);
	pos = vec4(scale*normal,1.0f);
	float displacement = rgb2grayscale(texture(texture0,pos.xyz).rgb);
	//pos = vec4(normal*scale,1);
	if(texCoord0.x < 0.0f || texCoord0.y < 0.0f || texCoord0.x > 1.0f || texCoord0.y > 1.0f)
		displacement = 0.0f;
	else	
		displacement = 1;//clamp(displacement,0.0f,1.f);

	pos += vec4(scale*normal*displacement*0.05,0);
	vec4 comp_pos = u_matViewProjection * pos;
	gl_Position = comp_pos;
}

#endif
/*
#ifdef _GEOMETRY	

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;


in vec2 texCoord0[];
in vec3 normal[];
in vec4 pos[];


out vec4 v_pos;
out vec2 v_texCoord0;
out vec3 v_normal;

void main()
{

    vec3 n = cross(normalize(pos[1].xyz-pos[0].xyz), normalize(pos[2].xyz-pos[0].xyz));
    for(int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        v_pos = pos[i];
		v_texCoord0 = texCoord0[i];
		v_normal = n;
        EmitVertex();
    }
}
#endif
*/
#ifdef _FRAGMENT_

in vec2 texCoord0;
in vec3 normal;
in vec4 pos;

layout(location = 0) out vec4 out_Color;
uniform samplerCube texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform float u_divisor = 1;
float texMult = 1;
float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}

void main()
{
	vec3 color;
	float offset = rgb2grayscale(color = texture(texture0,pos.xyz).rgb);
	if(offset < 0.3)
		color = texture(texture2,texCoord0*texMult/u_divisor).rgb;
	else if(offset > 0.8f)
		color = texture(texture3,texCoord0*texMult/u_divisor).rgb;
	else color = texture(texture2,texCoord0*texMult/u_divisor).rgb*(0.6-offset+0.3)/0.6+texture(texture3,texCoord0*texMult/u_divisor).rgb*(offset-0.3)/0.6;
	out_Color = vec4(color,1.0f);
}
#endif