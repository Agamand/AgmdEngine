
#ifndef _LIGHT_UNIFORM_HLSL_
#define _LIGHT_UNIFORM_HLSL_

#include "light_struct.hlsl"

uniform lightInfoStruct u_light[MAX_LIGHT];
uniform int u_lightCount = 0;

#endif /* _LIGHT_UNIFORM_HLSL_ */
