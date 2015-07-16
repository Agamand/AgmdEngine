#ifndef _COLOR_HLSL_
#define _COLOR_HLSL_

#include "math.hlsl"

float rgb2grayscale(float3 color)
{
	return 0.299f*color.r + 0.58f*color.g + 0.114f*color.b;
}

float3 normal2rgb(float3 normal)
{
	return float3(0.5f,0.5f,0.5f)+normal/2;
}

float3 rgb2normal(float3 rgb)
{
	return (rgb-float3(0.5f,0.5f,0.5f))*2;
}

float3 getColor1f(float a)
{
	return float3(clamp(cos(4*M_PI/3*a-4/3*M_PI),0,1),clamp(cos(4*M_PI/3*a-2*M_PI/3),0,1),clamp(cos(4*M_PI/3*a),0,1));
}

float3 getColor2f(float a)
{
	return float3(clamp(cos(4*M_PI/3*a-4/3*M_PI),0,1),clamp(cos(4*M_PI/3*a-2*M_PI/3),0,1),clamp(cos(4*M_PI/3*a),0,1));
}

#endif /* _COLOR_HLSL_ */