
#ifndef _GLOBAL_2D_UNIFORM_GLSL_
#define _GLOBAL_2D_UNIFORM_GLSL_

layout(std140) uniform camera2DInfoBlock
{
    mat4 				u_matProjection;
    mat4 				u_matView;
};

uniform int  			u_textureFlags = 0;
uniform mat4 			u_matModel = mat4(1.0);
#endif /* _GLOBAL_2D_UNIFORM_GLSL_ */
