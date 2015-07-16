
#ifndef _GLOBAL_UNIFORM_HLSL_
#define _GLOBAL_UNIFORM_HLSL_

cbuffer cameraInfoBlock : register(b0)
{   
	float4x4 u_matView;
    float4x4 u_matViewProjection;
    float4x4 u_matProjection;
    float4 	 u_viewPosition;
}
cbuffer modelInfoBlock: register(b1)
{
	float4x4  u_matModel;
}


#endif /* _GLOBAL_UNIFORM_HLSL_ */
