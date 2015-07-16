#ifndef _MATH_HLSL_
#define _MATH_HLSL_

static const float M_PI = 3.14159265359f;
static const float M_PI_2 = M_PI/2.f;
static const float M_2PI = M_PI*2.f;

bool near3f(float3 a ,float3 b)
{
	return length(a-b) < 0.001f;
}


float _atan2(float y, float x)
{
	if(x == 0.f)
		return 0; //in reality, if y == 0 this is undefined but HLSL is not reality :D
	else if(x > 0)
		return atan(y/x);
	else if(x < 0)
	{
		if(y >= 0)
			return atan(y/x)+M_PI;
		else
			return atan(y/x)-M_PI;
	}
}

float2 cart2sphere(float3 pos)
{
	return float2(_atan2(pos.y,pos.x),_atan2(pos.z,sqrt(pos.x*pos.x+pos.y*pos.y)));
}
float3 sphere2Cart(float2 angles)
{
	return float3(cos(angles.x)*cos(angles.y),sin(angles.x)*cos(angles.y),sin(angles.y));
}

#endif