#ifndef _GROUND_GLSL_
#define _GROUND_GLSL_

#version 330
#ifdef _VERTEX_

uniform mat4 u_matProjection = mat4(1);

in vec3 in_Vertex;
in vec2 in_TexCoord0;

out vec3 v_position;
out vec2 v_TexCoord;

void main()
{
	v_TexCoord = in_TexCoord0;
	v_position = in_Vertex;
	gl_Position = vec4(2*in_Vertex,1.0f);

}

#endif

#ifdef _FRAGMENT_
//#include <Core/noise/perlin.glsl>
#include <Core/noise/perlin3.glsl>

#include <common/math.glsl>

uniform mat4 u_position_matrix;
uniform int u_octave = 1;
uniform float u_frequency = 1.0f;
uniform float u_persistance = 1.0f;
in vec2 v_TexCoord;
in vec3 v_position;

layout(location = 0) out vec4 out_Color0;
layout(location = 1) out vec4 out_Color1;

const float const_scalling = 1.0f;
uniform float u_offset = 0.05f;
float getDisplacement(vec3 normal)
{

	float noise = 0*10.0f *  -.10 * turbulence( .5 * normal );
    float b = 10*5.0 * pnoise(0.05*normal,vec3(10));//pnoise( 0.05 * normal, vec3( 100.0 ) );

    return 0.1*(10. * noise + b);
    //return GetValue(normal.x,normal.y,normal.z);
	//return  (1.0f *  -.1 * turbulence( .5 * normal )+pnoise(vec3(normal.x,normal.y,normal.z),vec3(1.f))+pnoise(vec3(normal.x,normal.y,normal.z),vec3(10.f))+pnoise(vec3(normal.x,normal.y,normal.z),vec3(100.f)))/4*0.1;//10. * noise + b;
}

float _getDisplacement(vec3 position)
{
    float value = 0;
    int octave_count = max(u_octave,1);
    float curP = u_persistance;
    vec3 noise = position*u_frequency;
    float w = 1;
    int seed = -5656;

    for (int curOctave = 0; curOctave < octave_count; curOctave++) {
        value += (pnoise(noise+vec3(seed),vec3(100*curP))+(turbulence( .5 * noise)))*w;
        value *=2.0f;
        curP *= u_persistance;
        w *= 0.5f;
    }
    value += 2;
    return max(0,value)/2.0f;
    //float b = 0.5f-1 * pnoise(position,vec3(10));
    //float _noise = 10.0f *  -.1f * turbulence( .5 * position );
    //return (b+_noise);
}
const vec3 off = vec3(-1,0,1)*0.001f;
const float mult = 1;
vec4 getNormal(vec2 angles,float displacement)
{
	

    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);
    

    //return 0.1*vec4(getDisplacement(vx1),getDisplacement(vx2),getDisplacement(vy1),getDisplacement(vy2));
    return vec4(0.5f - (displacement*mult-getDisplacement(vx1)*mult),
    	0.5f + (displacement-getDisplacement(vx2))*mult,
    	0.5f + (displacement-getDisplacement(vy1))*mult,
    	0.5f + (displacement-getDisplacement(vy2)))*mult;
}
vec3 _getNormal(vec2 angles)
{


    vec3 vx1 = sphere2Cart(angles+off.xy);
    vec3 vx2 = sphere2Cart(angles+off.zy);

    vec3 vy1 = sphere2Cart(angles+off.yx);
    vec3 vy2 = sphere2Cart(angles+off.yz);

    vx1 *=1+_getDisplacement(vx1)*u_offset*const_scalling;
    vx2 *=1+_getDisplacement(vx2)*u_offset*const_scalling;
 
    vy1 *=1+_getDisplacement(vy1)*u_offset*const_scalling;
    vy2 *=1+_getDisplacement(vy2)*u_offset*const_scalling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return -cross(va,vb);
}
vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}


void main ()
{
	vec3 position = normalize(vec3(u_position_matrix*vec4(v_position,1.f)));
	float displacement = _getDisplacement(position);//(1+Perlin3D(position))/2;
    if(displacement > 1)
        out_Color0 = vec4(1.0f,0,0,1.f);
    else if(displacement < 0)
         out_Color0 = vec4(0,1.0f,0,1.f);
    else
        out_Color0 = vec4(vec3(0,0,1),1.f);

	out_Color0 = vec4(displacement);	
    out_Color1 = vec4(normal2color(_getNormal(cart2sphere(position))),1.0f);
	//out_Color1 = getNormal(cart2sphere(position),displacement);
}

#endif


#endif /* _GROUND_GLSL_ */