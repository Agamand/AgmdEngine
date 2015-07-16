#version 330

#include <common/global_uniform.glsl>
#include "tools.glsl"

#ifdef _VERTEX_




in vec3 in_Vertex;
out vec3 v3Pos;

void main(void)
{
	v3Pos = in_Vertex;
    gl_Position = u_matViewProjection * u_matModel * vec4(in_Vertex,1.0f);
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
const int nSamples = 5;
const float fSamples = 5.0;
in vec3 v3Pos;

layout(location = 0) out vec4 out_Color;
void main()
{
	vec3 _v3Pos = v3Pos;
	vec3 v3Ray = v3Pos - v3CameraPos;
	float fCameraHeight = length(v3CameraPos);					// The camera's current height
	_v3Pos = normalize(_v3Pos);
	float fFar = length(v3Ray);
	v3Ray /= fFar;
	
	// Calculate the ray's starting position, then calculate its scattering offset
	vec3 v3Start = v3CameraPos;
	float fDepth = exp((fInnerRadius - fCameraHeight) * (1.0/fScaleDepth));
	float fCameraAngle = dot(-v3Ray, _v3Pos);
	float fLightAngle = dot(v3LightPos, _v3Pos);
	float fCameraScale = scale(fCameraAngle,0.25f);
	float fLightScale = scale(fLightAngle,0.25f);
	float fCameraOffset = fDepth*fCameraScale;
	float fTemp = (fLightScale + fCameraScale);
	
	const float fSamples = 2.0;

	// Initialize the scattering loop variables
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
	
	// Now loop through the sample rays
	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	vec3 v3Attenuate;
	for(int i=0; i<int(fSamples); i++)
	{
		float fHeight = length(v3SamplePoint);
		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
		float fScatter = fDepth*fTemp - fCameraOffset;
		v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
		v3SamplePoint += v3SampleRay;
	}

    // scattering colors
    vec3 vRayleighColor = v3FrontColor * (v3InvWavelength * fKrESun + fKmESun);
    vec3 vMieColor = v3Attenuate;
    out_Color = vec4(vRayleighColor + vMieColor,1);

}

#endif