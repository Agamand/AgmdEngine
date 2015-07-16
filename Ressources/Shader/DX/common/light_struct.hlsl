
#ifndef _LIGHT_STRUCT_HLSL_
#define _LIGHT_STRUCT_HLSL_
#define MAX_LIGHT 10

struct lightInfoStruct
{
	float4 l_position;
	float4 l_dir;
	float4 l_ambient;
	float4 l_diffuse;
	float4 l_specular;
	float l_innerAngle;
	float l_outerAngle;
	float l_range;
	int l_type;
};

#endif /* _LIGHT_STRUCT_HLSL_ */