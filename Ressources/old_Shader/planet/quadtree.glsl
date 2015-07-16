#version 420
#ifdef _VERTEX_
#include <common/global_uniform.glsl>
#include <Core/noise/perlin.glsl>
uniform mat4 u_position_matrix;
uniform float u_offset;
in vec3 in_Vertex;
in vec2 in_TexCoord0;
out vec2 v_texCoord0;

float getDisplacement(vec3 normal)
{
	float noise = 10.0f *  -.10 * turbulence( 100 * normal );
    float b = 5.0 * pnoise( 100 * normal, vec3( 1000.0 ) );

	return 10. * noise + b;
}

void main()
{
	vec4 position = vec4(0,0,0,1);
	position.xyz = normalize(( u_position_matrix * vec4(in_Vertex,1)).xyz);
	float dis = getDisplacement(position.xyz);
	v_texCoord0 = clamp(in_TexCoord0,0,1);
	gl_Position = u_matViewProjection *u_matModel* vec4(position.xyz*(1+(dis-1)*u_offset*0.1f),1.0f);
}

#endif

#ifdef _FRAGMENT_
in vec2 v_texCoord0;
layout(location = 0) out vec4 out_Color;
void main()
{
	vec3 color = vec3(1,0,0);
	if(v_texCoord0.x > 0.5f)
		color += vec3(0,1,0);
	if(v_texCoord0.y > 0.5f)
		color += vec3(-1,0,1);
	out_Color = vec4(color,1);
}
#endif