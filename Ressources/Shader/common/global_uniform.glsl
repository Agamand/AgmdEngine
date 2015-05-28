
#ifndef _GLOBAL_UNIFORM_GLSL_
#define _GLOBAL_UNIFORM_GLSL_

layout(std140) uniform cameraInfoBlock
{
	vec4				u_viewPosition;
	mat4 				u_matView;
    mat4 				u_matProjectionView;
    mat4 				u_matProjection;
};
uniform mat4 			u_matModel = mat4(1.0);
#endif /* _GLOBAL_UNIFORM_GLSL_ */
