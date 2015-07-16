#include <common/global_uniform.hlsl>
struct VIn
{
    float4 position : POSITION;
    float4 color : COLOR;
};


struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};




VOut VShader(VIn input)
{
    VOut output;
    float4x4 m = {  
    {1,0,0,0},  
    {0,1,0,0},  
    {0,0,1,0},  
    {0,0,0,1}  
}; 
    input.position.w = 1.0f;
    output.position = input.position;
    //output.position = mul(input.position, u_matModel);
    //output.position = mul(output.position, u_matViewProjection);
    output.color = float4(1,1,1,1);

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}