#version 330

#include <common/global_uniform.glsl>
#include "tools.glsl"

#ifdef _VERTEX_




in vec3 in_Vertex;
out vec3 v3Pos;

void main(void)
{
	v3Pos = vec3(1.025f*in_Vertex);
    gl_Position = u_matViewProjection * u_matModel * vec4(1.025f*in_Vertex,1.0f);
}
#endif

#ifdef _FRAGMENT_
uniform vec3 v3CameraPos;
uniform vec3 v3LightPos;		
uniform vec3 v3InvWavelength;	
uniform float fCameraHeight;	
uniform float fCameraHeight2;	
	
uniform float fOuterRadius;		
uniform float fOuterRadius2;	
uniform float fInnerRadius;		
uniform float fInnerRadius2;

uniform float fKrESun;			
uniform float fKmESun;			
uniform float fKr4PI;			
uniform float fKm4PI;		
uniform float fScale;			
uniform float fScaleDepth;		
uniform float fScaleOverScaleDepth;
uniform float g;
uniform float g2;
const int nSamples = 5;
const float fSamples = 5.0;
in vec3 v3Pos;

layout(location = 0) out vec4 out_Color;
void main()
{
    vec3 v3Ray = v3Pos - v3CameraPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

    // Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
    float B = 2.0f * dot(v3CameraPos, v3Ray);
    float C = fCameraHeight2 - fOuterRadius2;
    float fDet = max(0.0f, B * B - 4.0f * C);
    float fNear = 0.5f * (-B - sqrt(fDet));

    // Calculate the ray's starting position, then calculate its scattering offset
    vec3 v3Start = v3CameraPos + v3Ray * fNear;
    fFar -= fNear;
    float fDepth = exp((fInnerRadius - fOuterRadius) / fScaleDepth);
    float fCameraAngle = dot(-v3Ray, v3Pos) / length(v3Pos);
    float fLightAngle = dot(v3LightPos, v3Pos) / length(v3Pos);

    float fStartDepth = exp(-1.0/fScaleDepth);
    float fStartAngle = dot(v3Ray, v3Start) / fOuterRadius;
    float fStartOffset = fStartDepth*scale(fStartAngle,0.25f);
    float fCameraScale = scale(fCameraAngle, fScaleDepth);
    float fLightScale = scale(fLightAngle, fScaleDepth);

    float fCameraOffset = fDepth * fCameraScale;
    float fTemp = (fLightScale + fCameraScale);

    // Initialize the scattering loop variables
    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * fScale;
    vec3 v3SampleRay = v3Ray * fSampleLength;
    vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5f;

    // Now loop through the sample rays
    vec3 v3FrontColor = vec3(0);
    //vec3 v3Attenuate = vec3(0);
    for (int i = 0; i < nSamples; i++)
    {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
        float fLightAngle = dot(v3LightPos, v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
        float fScatter = (fStartOffset + fDepth*(scale(fLightAngle,0.25f) - scale(fCameraAngle,0.25f)));
        vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + vec3(fKm4PI)));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }

    // scattering colors
    vec3 vRayleighColor = v3FrontColor * (v3InvWavelength * fKrESun);
    vec3 vMieColor = v3FrontColor * fKmESun;

    vec3 v3Dir = v3CameraPos - v3Pos;
 	float fCos = dot(v3LightPos, v3Dir ) / length(v3Dir);
    float fCos2 = fCos*fCos;
    out_Color = vec4(getRayleighPhase(fCos2) * vRayleighColor + getMiePhase(fCos, fCos2, g, g2)* vMieColor,1);
    //vec4(vRayleighColor + vec3(0.25f, 0.25f, 0.3f) * vMieColor,1);
    out_Color.a = out_Color.b;
    //out_Color = vec4(1,0,0,1);

}

#endif