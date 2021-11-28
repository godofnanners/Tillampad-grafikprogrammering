struct VertexToPixel
{
    float4 myPosition : SV_POSITION;
    float2 myUV : UV;
};

struct PixelOutput
{
    float4 myColor : SV_TARGET;
};

cbuffer FrameBuffer : register(b0)
{
    float4x4 toCamera;
    float4x4 toProjection;
    float4 cameraPosition;
}

cbuffer EnvironmentLightBuffer : register(b1)
{
    float4 toDirectionalLight;
    float4 directionalLightColor;
}

cbuffer PointLightBuffer : register(b1)
{
    float3 myPosition;
    float myRange;
    float3 myColour;
    float myIntensity;
}

TextureCube environmentTexture : register(t0);
Texture2D positionTexture : register(t1);
Texture2D albedoTexture : register(t2);
Texture2D normalTexture : register(t3);
Texture2D vertexnormalTexture : register(t4);
Texture2D metalnessTexture : register(t5);
Texture2D roughnessTexture : register(t6);
Texture2D ambientocclusionTexture : register(t7);
Texture2D emissiveTexture : register(t8);
SamplerState defaultSampler : register(s0);


#include "CommonShaderFunctions.hlsli"


PixelOutput PixelShader_Exists(VertexToPixel input)
{
    PixelOutput output;
    float3 exists = albedoTexture.Sample(defaultSampler, input.myUV.xy).aaa;
    output.myColor.rgb = exists;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_WorldPosition(VertexToPixel input)
{
    PixelOutput output;
    float3 position = positionTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = position;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Albedo(VertexToPixel input)
{
    PixelOutput output;
    float3 albedo = albedoTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = albedo;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Normal(VertexToPixel input)
{
    PixelOutput output;
    float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = normal;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_VertexNormal(VertexToPixel input)
{
    PixelOutput output;
    float3 vnt = vertexnormalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = vnt;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_AmbientOcclusion(VertexToPixel input)
{
    PixelOutput output;
    float3 ao = ambientocclusionTexture.Sample(defaultSampler, input.myUV.xy).rrr;
    output.myColor.rgb = ao;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Metalness(VertexToPixel input)
{
    PixelOutput output;
    float3 metal = metalnessTexture.Sample(defaultSampler, input.myUV.xy).rrr;
    output.myColor.rgb = metal;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_PerceptualRoughness(VertexToPixel input)
{
    PixelOutput output;
    float3 rough = roughnessTexture.Sample(defaultSampler, input.myUV.xy).rrr;
    output.myColor.rgb = rough;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Emissive(VertexToPixel input)
{
    PixelOutput output;
    float3 em = emissiveTexture.Sample(defaultSampler, input.myUV.xy).rrr;
    output.myColor.rgb = em;
    output.myColor.a = 1.0f;
    return output;
}