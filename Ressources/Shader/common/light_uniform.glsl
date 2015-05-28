
#ifndef _LIGHT_UNIFORM_GLSL_
#define _LIGHT_UNIFORM_GLSL_

#include "light_struct.glsl"

uniform lightInfoStruct u_light[MAX_LIGHT];
uniform int u_lightCount = 0;

#endif /* _LIGHT_UNIFORM_GLSL_ */
