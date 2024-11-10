cbuffer cbTransform : register(b0)
{
    row_major float4x4 World;
};

cbuffer cbCamera : register(b1)
{
    row_major float4x4 ViewProj;
};

cbuffer cmCBSprite : register(b2)
{
    float PivotCol;
    float PivotRow;
}

Texture2D texDiffuse : register(t0);
SamplerState samLinear : register(s0);

///////////////////////////////////////

struct VSInput
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VSOutput
{
    float4 PositionH : SV_Position;
    float2 UV : TEXCOORD0;
};

////////////////////////////////////////

VSOutput VS(VSInput input)
{
    VSOutput output;
    float4x4 finalMatrix = mul(World, ViewProj);
    output.PositionH = mul(float4(input.Position, 1.f), finalMatrix);

    output.UV.x = input.UV.x + PivotCol;
    output.UV.y = input.UV.y + PivotRow;
    
    return output;
}

float4 PS(VSOutput input) : SV_Target
{
    float4 finalColor = texDiffuse.Sample(samLinear, input.UV);

    float4 ignoreColor = float4(1.f, 0.f, 1.f, 1.f);
    float tolerance = 0.01f;
    
    if (abs(finalColor.r - ignoreColor.r) < tolerance &&
        abs(finalColor.g - ignoreColor.g) < tolerance &&
        abs(finalColor.b - ignoreColor.b) < tolerance &&
        abs(finalColor.a - ignoreColor.a) < tolerance)
    {
        return float4(0.f, 0.f, 0.f, 0.f);
    }
    
    return finalColor;
}
