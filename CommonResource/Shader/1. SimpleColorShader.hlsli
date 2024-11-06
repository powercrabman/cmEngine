cbuffer CBTransform : register(b0)
{
    row_major float4x4 gWorld;
};

struct VSInput
{
    float3 PositionL : POSITION;
    float4 Color : COLOR;
};

struct VSOutput
{
    float4 PositionH : SV_POSITION;
    float4 Color : COLOR;
};

VSOutput VS(VSInput input)
{
    VSOutput ret;
    ret.PositionH = mul(float4(input.PositionL, 1.f), gWorld);
    ret.Color = input.Color;

    return ret;
}

float4 PS(VSOutput input) : SV_Target
{
    return input.Color;
}