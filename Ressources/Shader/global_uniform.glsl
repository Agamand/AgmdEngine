
#ifndef _GLOBAL_UNIFORM_GLSL_
#define _GLOBAL_UNIFORM_GLSL_

layout(std140) uniform cameraInfoBlock
{
    mat4                 u_matProjectionView;
    mat4                 u_matView;
    mat4                 u_matProjection;
};

uniform int              u_textureFlags = 0; //unused
uniform mat4             u_matModel = mat4(1.0);
//uniform sampler2DShadow    u_shadowMap;
//uniform samplerBuffer   u_light;
uniform sampler2D u_shadowMap;
#endif /* _GLOBAL_UNIFORM_GLSL_ */
