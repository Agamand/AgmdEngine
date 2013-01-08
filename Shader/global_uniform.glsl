
#ifndef _GLOBAL_UNIFORM_GLSL_
#define _GLOBAL_UNIFORM_GLSL_

layout(std140) uniform globalValue
{
    mat4 				u_matProjection;
    mat4 				u_matView;
	int 				u_nlights;
};

uniform int  			u_textureFlags = 0;
uniform mat4 			u_matModel = mat4(1.0);
//uniform sampler2DShadow	u_shadowMap;
//uniform samplerBuffer   u_light;
uniform sampler2D u_shadowMap;
#endif /* _GLOBAL_UNIFORM_GLSL_ */
