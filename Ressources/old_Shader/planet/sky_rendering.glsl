#version 330

#include <common/global_uniform.glsl>

#ifdef _VERTEX_
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

const int nSamples = 4;
const float fSamples = 4.0;

in vec3 in_Vertex;

out vec3 v3Direction;
out vec4 color1;
out vec4 color2;

vec3 v3ELightPos = vec3(u_matModel * vec4(v3LightPos, 1.0));
vec3 v3ECameraPos= vec3(u_matModel * vec4(v3CameraPos, 1.0));


float scale(float fCos)
{
	float x = 1.0 - fCos;
	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

void main(void)
{

gl_Position = u_matViewProjection * u_matModel * vec4(in_Vertex,1.0f);
// Get the ray from the camera to the vertex and its length (which is the far    point of the ray passing through the atmosphere)
vec3 v3Pos = vec3(u_matModel * vec4(in_Vertex,1.0f));
vec3 v3Ray = v3Pos - v3ECameraPos;
float fFar = length(v3Ray);
v3Ray /= fFar;

// Calculate the closest intersection of the ray with the outer atmosphere (which is the near point of the ray passing through the atmosphere)
float B = 2.0 * dot(v3CameraPos, v3Ray);
float C = fCameraHeight2 - fOuterRadius2;
float fDet = max(0.0, B*B - 4.0 * C);
float fNear = 0.5 * (-B - sqrt(fDet));

// Calculate the ray's starting position, then calculate its scattering offset
vec3 v3Start = v3CameraPos + v3Ray * fNear;
fFar -= fNear;
float fDepth = exp((fInnerRadius - fOuterRadius) / fScaleDepth);
float fCameraAngle = dot(-v3Ray, v3Pos) / fFar;
float fLightAngle = dot(v3ELightPos, v3Pos) / fFar;
float fCameraScale = scale(fCameraAngle);
float fLightScale = scale(fLightAngle);
float fCameraOffset = fDepth*fCameraScale;
float fTemp = (fLightScale + fCameraScale);

// Initialize the scattering loop variables
float fSampleLength = fFar / fSamples;
float fScaledLength = fSampleLength * fScale;
vec3 v3SampleRay = v3Ray * fSampleLength;
vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

// Now loop through the sample rays
vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
vec3 v3Attenuate;
for(int i=0; i<nSamples; i++)
{
    float fHeight = length(v3SamplePoint);
    float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
    float fScatter = fDepth*fTemp - fCameraOffset;
    v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
    v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
    v3SamplePoint += v3SampleRay;
}
vec3 first = v3FrontColor * (v3InvWavelength * fKrESun + fKmESun);
vec3 secondary = v3Attenuate;
 color1 = vec4((first +  vec3(0.25,0.25,0.25) * secondary), 1.0);
 color2	= vec4(secondary,1);
}
#endif


#ifdef _FRAGMENT_



uniform vec3 v3LightPos;
uniform float g;
uniform float g2;

in vec3 v3Direction;
in vec4 color1;
in vec4 color2;

layout(location = 0) out vec4 out_Color;
void main()
{
	float fCos = dot(v3LightPos, v3Direction) / length(v3Direction);
	float fMiePhase = 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos*fCos) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
	out_Color = color2;// + fMiePhase * color2;
	out_Color.a = 1;//out_Color.b;
}



#endif