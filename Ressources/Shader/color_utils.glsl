
#ifndef _COLOR_UTILS_GLSL_
#define _COLOR_UTILS_GLSL_

#include "math.glsl"

vec3 getColor(float a)
{
	return vec3(clamp(cos(4*M_PI/3*a-4/3*M_PI),0,1),clamp(cos(4*M_PI/3*a-2*M_PI/3),0,1),clamp(cos(4*M_PI/3*a),0,1));
}

#endif