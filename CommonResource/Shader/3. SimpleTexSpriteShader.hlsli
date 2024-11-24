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
    float OffsetX;
    float OffsetY;
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

    output.UV.x = input.UV.x + OffsetX;
    output.UV.y = input.UV.y + OffsetY;
    
    return output;
}

float4 PS(VSOutput input) : SV_Target
{
    float4 finalColor = texDiffuse.Sample(samLinear, input.UV);

    if (finalColor.w < 0.01f)
    {
        discard;
    }

    return finalColor;
}
