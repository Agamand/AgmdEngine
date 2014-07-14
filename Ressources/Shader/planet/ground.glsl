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
#include <Core/noise/perlin.glsl>

#include <common/math.glsl>

uniform mat4 u_position_matrix;

in vec2 v_TexCoord;
in vec3 v_position;

layout(location = 0) out vec4 out_Color0;
layout(location = 1) out vec4 out_Color1;

const float const_scalling = 2.0f;
uniform float u_offset = 0.1f;
float getDisplacement(vec3 normal)
{
	float noise = 10.0f *  -.10 * turbulence( .5 * normal );
    float b = 5.0 * pnoise( 0.05 * normal, vec3( 100.0 ) );

	return 10. * noise + b;
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

    vx1 *=1+getDisplacement(vx1)*u_offset*const_scalling;
    vx2 *=1+getDisplacement(vx2)*u_offset*const_scalling;
 
    vy1 *=1+getDisplacement(vy1)*u_offset*const_scalling;
    vy2 *=1+getDisplacement(vy2)*u_offset*const_scalling;

    vec3 va = normalize(vx2-vx1);
    vec3 vb = normalize(vy1-vy2);
    return cross(va,vb);
}
vec3 normal2color(vec3 normal)
{
	return normal/2+vec3(0.5);
}


void main ()
{
	vec3 position = normalize(vec3(u_position_matrix*vec4(v_position,1.f)));
	float displacement = getDisplacement(position);
	out_Color0 = 0.1*vec4(displacement);
	out_Color1 = vec4(normal2color(_getNormal(cart2sphere(position))),1.0f);
	//out_Color1 = getNormal(cart2sphere(position),displacement);
}

#endif


#endif /* _GROUND_GLSL_ */