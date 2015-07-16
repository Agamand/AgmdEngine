#include <common/global_uniform.hlsl>
#include <common/color.hlsl>

struct VertexInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};


PixelInput VShader(VertexInput input)
{
    PixelInput output;
    input.position.w = 1.0f;
        float4x4 m = {  
    {1,0,0,0},  
    {0,1,0,0},  
    {0,0,1,0},  
    {0,0,0,1}  
}; 
    output.position = input.position;
    output.position = mul(input.position, u_matModel);
    output.position = mul(output.position, u_matViewProjection);
    output.normal = normalize(input.position.xyz);
    output.color = float4(1,1,1,1);//input.color;

    return output;
}


float4 PShader(PixelInput input) : SV_TARGET
{
    float4 outColor = float4(0,0,0,1);

    float3 ncolor  = normal2rgb(input.normal);
    outColor.rgb = ncolor.rgb;
    return outColor;
 //   return input.color;
}