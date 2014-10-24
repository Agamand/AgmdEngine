#version 420


//include <Core/noise/perlin.glsl>

uniform int u_octave = 1;
uniform float u_frequency = 1.0f;
uniform float u_persistance = 1.0f;
uniform float u_amplitude = 0.4f;
uniform float u_lacunarity = 2.510f;
#include <Core/noise/simplexNoise3.glsl>
float getDisplacement(vec3 normal)
{
	/*float noise = 10.0f *  -.10 * turbulence( 1 * normal );
	float noise2 = 10.0f *  -.10 * turbulence( 1 * normal );
    float b =  pnoise( 10 * normal, vec3( 1000.0 ) );

    float value=0;
    float w = 1;
    float p = u_frequency*1.0f;
    for(int i  = 0; i < u_octave; i++)
    {
    	value += pnoise( p*(i+1) * normal, vec3( 1000.0 ) )*w+turbulence( p*(i+1) * normal )*w;
    	w*=0.5f;
    }*/


   	float t =SimplexBillowed(normal, u_octave, vec3(0,0,0), u_frequency, u_amplitude,u_lacunarity, u_persistance);
	return t;//SimplexBillowed(normal,u_octave,vec3(),u_frequency,0.4f,2.51f,u_persistance);//0.5+(value)/2;
}
uniform float u_offset;
const float scaling = 1f;
#ifdef _VERTEX_

#include <common/global_uniform.glsl>
uniform mat4 u_position_matrix;

in vec3 in_Vertex;
in vec2 in_TexCoord0;
out vec3 v_position;
out vec2 v_texCoord0;

void main()
{
	vec4 position = vec4(0,0,0,1);
	position.xyz = normalize(( u_position_matrix * vec4(in_Vertex,1)).xyz);
	float dis = getDisplacement(position.xyz);
	//if(in_TexCoord0.x < 0.0f || in_TexCoord0.y < 0.0f || in_TexCoord0.x > 1.0f || in_TexCoord0.y > 1.0f)
		//dis = (dis-1)*u_offset*scaling-0.1f;
	//else 
	dis = (1-dis)*u_offset*scaling;
	

	v_position = position.xyz;
	v_texCoord0 = clamp(in_TexCoord0,0,1);
	gl_Position = u_matViewProjection *u_matModel* vec4(position.xyz*(1+dis),1.0f);
}

#endif

#ifdef _FRAGMENT_

in vec2 v_texCoord0;
in vec3 v_position;
uniform sampler2D texture1;
uniform vec3 v3LightPos = vec3(1,0,0);
uniform int u_use_atmosphere = 0;

layout(location = 0) out vec4 out_Color;
#include <common/math.glsl>

const vec3 off = vec3(-1,0,1)*0.0005f;
vec3 _getNormal(vec2 angles)
{


    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);

    vx1 *=1+(1-getDisplacement(vx1))*u_offset*scaling;
    vx2 *=1+(1-getDisplacement(vx2))*u_offset*scaling;
 
    vy1 *=1+(1-getDisplacement(vy1))*u_offset*scaling;
    vy2 *=1+(1-getDisplacement(vy2))*u_offset*scaling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return -cross(va,vb);
}

vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}

vec3 color2normal(vec3 color)
{
	return (color-vec3(0.5))*2;
}
#include "ground_function.glsl"

void main()
{


	float dis = getDisplacement(v_position.xyz)*0.1f;
	vec3 normal = _getNormal(cart2sphere(v_position.xyz));
	float lambert = clamp(dot(v3LightPos,normal),0,1);

	vec3 color = texture(texture1,vec2(clamp(1-dis*2,0,1),0)).rgb*lambert;
	if(u_use_atmosphere > 0)
		color = select_ground(v_position,color);
	out_Color = vec4(color,1.0f);

	out_Color = vec4(normal2color(normal),1);
}
#endif