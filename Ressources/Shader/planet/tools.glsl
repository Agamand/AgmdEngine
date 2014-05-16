#ifndef _TOOLS_GLSL_
#define _TOOLS_GLSL_
float getNearIntersection(vec3 position, vec3 ray, float distanceSquared, float radiusSquared)
{
    float B = dot(position, ray) * 2;

    float C = distanceSquared - radiusSquared;
    float fDet = max(0.0, B * B - 4.0 * C);
    return 0.5f * (-B - sqrt(fDet));
}


float scale(float fCos, float fScaleDepth)
{
    float x = 1.0f - fCos;
    return fScaleDepth * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}
#endif _TOOLS_GLSL_