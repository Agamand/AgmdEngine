
#ifndef _GLOBAL_UNIFORM_GLSL_
#define _GLOBAL_UNIFORM_GLSL_

layout(std140) uniform cameraInfoBlock
{
    mat4 				u_matViewProjection;
    mat4 				u_matView;
    mat4				u_matProjection;
};
uniform mat4 			u_matModel = mat4(1.0);
#endif /* _GLOBAL_UNIFORM_GLSL_ */
