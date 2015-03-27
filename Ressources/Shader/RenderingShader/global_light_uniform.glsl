
#ifndef _GLOBAL_LIGHT_UNIFORM_GLSL_
#define _GLOBAL_LIGHT_UNIFORM_GLSL_

layout(std140) uniform lightInfoBlock
{
    vec4 l_position;
    vec4 l_dir;
    vec4 l_ambient;
    vec4 l_diffuse;
    vec4 l_specular;
    float l_innerAngle;
    float l_outerAngle;
    float l_range;
    int l_type;
};


#endif /* _GLOBAL_LIGHT_UNIFORM_GLSL_ */
