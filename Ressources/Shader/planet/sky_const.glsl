#ifndef _SKY_CONST_GLSL_
#define _SKY_CONST_GLSL_
const float fKrESun = 0.0025f * 20.0f;
const float fKmESun = 0.0015f * 20.0f;
const float fKr4PI = 0.0025f * 4.0f * 3.141592653f;
const float fKm4PI = 0.0015f * 4.0f * 3.141592653f;

const float fInnerRadius = 1.0f;
const float fInnerRadius2 = 1.0f;
const float fOuterRadius = 1.025f;
const float fOuterRadius2 = 1.025f*1.025f;
/*
const float fScale = 1.0f / 0.25f;
const float fScaleDepth = 0.25f;
const float fScaleOverScaleDepth = 4.0f / 0.25f;*/
const float g = -0.990f;
const float g2 =  -0.990f * -0.990f;
#endif _SKY_CONST_GLSL_