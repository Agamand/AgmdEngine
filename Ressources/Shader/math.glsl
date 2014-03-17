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

#endif