
#ifndef _LIGHT_STRUCT_GLSL_
#define _LIGHT_STRUCT_GLSL_
#define MAX_LIGHT 10

struct lightInfoStruct
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

#endif /* _LIGHT_STRUCT_GLSL_ */