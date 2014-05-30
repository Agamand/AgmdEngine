#ifndef _COLOR_GLSL_
#define _COLOR_GLSL_

#include "math.glsl"

float rgb2grayscale(vec3 color)
{
	return 0.299f*color.r + 0.58f*color.g + 0.114f*color.b;
}

vec3 normal2rgb(vec3 normal)
{
	return vec3(0.5f)+normal/2;
}

vec3 rgb2normal(vec3 rgb)
{
	return (rgb-vec3(0.5f))*2;
}

vec3 getColor1f(float a)
{
	return vec3(clamp(cos(4*M_PI/3*a-4/3*M_PI),0,1),clamp(cos(4*M_PI/3*a-2*M_PI/3),0,1),clamp(cos(4*M_PI/3*a),0,1));
}

vec3 getColor2f(float a)
{
	return vec3(clamp(cos(4*M_PI/3*a-4/3*M_PI),0,1),clamp(cos(4*M_PI/3*a-2*M_PI/3),0,1),clamp(cos(4*M_PI/3*a),0,1));
}

#endif /* _COLOR_GLSL_ */