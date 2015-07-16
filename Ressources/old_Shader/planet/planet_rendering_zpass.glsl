#version 420


#ifdef _VERTEX_

#include <common/global_uniform.glsl>
#include <Core/noise/perlin.glsl>
uniform float u_offset;
const float scaling = 0.1f;
uniform mat4 u_position_matrix;

in vec3 in_Vertex;
in vec2 in_TexCoord0;
float getDisplacement(vec3 normal)
{
	float noise = 10.0f *  -.10 * turbulence( 100 * normal );
	float noise2 = 10.0f *  -.10 * turbulence( 100 * normal );
    float b = 5.0 * pnoise( 10 * normal, vec3( 1000.0 ) );

	return 10. * (noise+noise2)/2 + b;
}

void main()
{
	vec4 position = vec4(0,0,0,1);
	position.xyz = normalize(( u_position_matrix * vec4(in_Vertex,1)).xyz);
	float dis = getDisplacement(position.xyz);
	dis = 0;//(dis-1)*u_offset*scaling;
	
	gl_Position = u_matViewProjection *u_matModel* vec4(position.xyz*(1+dis),1.0f);
}

#endif

#ifdef _FRAGMENT_

out float out_depth;

void main(){
	out_depth = gl_FragCoord.z;
}
#endif