#version 330

#include <common/global_uniform.glsl>
#include "tools.glsl"

#ifdef _VERTEX_




in vec3 in_Vertex;
out vec3 v3Pos;

void main(void)
{
	v3Pos = vec3(u_matModel * vec4(in_Vertex,1.0f));
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
uniform float g;
uniform float g2;
const int nSamples = 5;
const float fSamples = 5.0;
in vec3 v3Pos;

layout(location = 0) out vec4 out_Color;
void main()
{
    

  	float fCameraHeight = length(v3CameraPos);					// The camera's current height
	vec3 v3Ray = v3Pos - v3CameraPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;
	
	// Calculate the ray's starting position, then calculate its scattering offset
	vec3 v3Start = v3CameraPos;
	float fHeight = length(v3Start);
	float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
	float fStartAngle = dot(v3Ray, v3Start) / fHeight;
	float fStartOffset = fDepth*scale(fStartAngle,0.25f);
	
	const float fSamples = 2.0;

	// Initialize the scattering loop variables
	float fSampleLength = fFar / fSamples;
	float fScaledLength = fSampleLength * fScale;
	vec3 v3SampleRay = v3Ray * fSampleLength;
	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
	
	// Now loop through the sample rays
	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
	for(int i=0; i<int(fSamples); i++)
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

}

#endif