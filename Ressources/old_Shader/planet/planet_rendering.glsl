#version 420

#include <common/global_uniform.glsl>

#include <Core/noise/perlin.glsl>
float getDisplacement(vec3 normal)
{
	//float noise = 10.0f *  -.10 * turbulence( .5 * normal );
    float b = 5.0 * pnoise( 0.05 * normal, vec3( 100.0 ) );

	//return 10. * noise + b;
	return b/5.0f;
}
const float const_scalling = 1.0f;
#ifdef _VERTEX_
in vec3 in_Vertex;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoord0;

#include <common/math.glsl>

out vec3 v_normal;
out vec3 v_position;
out vec2 v_texCoord0;
out float v_displacement;


uniform sampler2D texture0;
uniform float u_offset = 0.05f;
uniform mat4 u_position_matrix;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}


void main()
{
	vec3 vertex = in_Vertex;
	vec4 position;
	vec3 normal;
	position.w = 1.0f;
	float scale = 1f;
	
	position.xyz = normal = normalize(( u_position_matrix * vec4(in_Vertex,1)).xyz);
	position.xyz *= scale;

	float displacement = v_displacement =  texture(texture0,clamp(in_TexCoord0,0,1)).x;
	//position = vec4(normal*scale,1);
	if(in_TexCoord0.x < 0.0f || in_TexCoord0.y < 0.0f || in_TexCoord0.x > 1.0f || in_TexCoord0.y > 1.0f)
	{
		displacement =displacement*u_offset*const_scalling-0.1f;
		position += vec4(scale*normal*displacement,0);
	}
	else{
		displacement = clamp(displacement,0.0f,1.f)*u_offset*const_scalling;
		position += vec4(scale*normal*displacement,0);
	}


	
	vec4 comp_position = u_matViewProjection *u_matModel* position;

	v_position = position.xyz;
	v_normal = normal;
	v_texCoord0 = clamp(in_TexCoord0,0,1);

	gl_Position = comp_position;
}

#endif

#ifdef _FRAGMENT_

#include <common/math.glsl>

in vec3 v_normal;
in vec3 v_position;
in vec2 v_texCoord0;
in float v_displacement;

layout(location = 0) out vec4 out_Color;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float u_divisor = 1;
uniform float u_offset = 0.05f;
uniform int u_normal_mapping = 1;
uniform vec3 v3LightPos = vec3(1,0,0);
uniform int u_use_atmosphere = 0;

#include "ground_function.glsl"

float texMult = 30f;

float rgb2grayscale(vec3 color)
{
	return 0.299*color.r + 0.58*color.g + 0.114*color.b;
}

vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}

vec3 color2normal(vec3 color)
{
	return (color-vec3(0.5))*2;
}

void main()
{
	vec4 screen_pos = gl_FragCoord;
	vec3 color;
	float offset = texture(texture0,v_texCoord0).x;
	vec2 angles = cart2sphere(v_normal);
	vec3 normal = normalize(mat3(u_matModel)*color2normal(texture(texture2,v_texCoord0).rgb));

	color = texture(texture1,vec2(clamp(offset,0,1),0)).rgb;
	
	float lambert =clamp(dot(v3LightPos,normal),0,1),
	lambert2 = clamp(dot(v3LightPos,v_normal),0,1);
	//show color with normal mapping
	if(u_normal_mapping > 0)
		color *=lambert;
	//show color without normal mapping
	else
		color *=lambert2;

	if(u_use_atmosphere > 0)
		color = select_ground(v_position,color);
	out_Color = vec4(color,1.0f);
	//show heigth map
	out_Color = vec4(vec3(offset),1);
}
#endif