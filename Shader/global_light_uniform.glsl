
#ifndef _GLOBAL_LIGHT_UNIFORM_GLSL_
#define _GLOBAL_LIGHT_UNIFORM_GLSL_

uniform layout(std140) lightInfo
{
	vec3 u_position;
	vec3 u_dir;
	vec4 color;
}


#endif /* _GLOBAL_LIGHT_UNIFORM_GLSL_ */
