#ifndef _MATH_GLSL_
#define _MATH_GLSL_

const float M_PI = 3.14159265359f;
const float M_PI_2 = M_PI/2.f;
const float M_2PI = M_PI*2.f;

const int rand_max = 0x7fff;

float rand1f(vec2 x, int _seed)
{
	float seed = float(_seed);
	uint n = floatBitsToUint(x.y * seed + x.x * seed);
	n = n * (n * n * 15731u + 789221u);
	n = (n >> 9u) | 0x3F800000u;

	return 2.0 - uintBitsToFloat(n);
}


bool near3f(vec3 a ,vec3 b)
{
	return length(a-b) < 0.001f;
}

int vec2ToInt(vec2 value)
{
	ivec2 _int = floatBitsToInt(value);
	return _int.x + _int.y<<8;
}

vec2 intToVec2(int value)
{
	ivec2 _int = ivec2((value & 0xFF),(value>>8) & 0xFF);
	return intBitsToFloat(_int);
}


float _atan2(float y, float x)
{
	if(x == 0.f)
		return 0; //in reality, if y == 0 this is undefined but glsl is not reality :D
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

vec2 cart2sphere(vec3 pos)
{
	return vec2(_atan2(pos.y,pos.x),_atan2(pos.z,sqrt(pos.x*pos.x+pos.y*pos.y)));
}
vec3 sphere2Cart(vec2 angles)
{
	return vec3(cos(angles.x)*cos(angles.y),sin(angles.x)*cos(angles.y),sin(angles.y));
}

#endif