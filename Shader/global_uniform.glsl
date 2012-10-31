
#ifndef _GLOBAL_UNIFORM_GLSL_
#define _GLOBAL_UNIFORM_GLSL_

layout(std140) uniform globalValue
{
    mat4 				u_matProjection;
    mat4 				u_matView;
	int 				u_nlights;
};

uniform int  			u_textureFlags;
uniform mat4 			u_matModel;
uniform gsamplerBuffer  u_light

#endif /* _GLOBAL_UNIFORM_GLSL_ */
