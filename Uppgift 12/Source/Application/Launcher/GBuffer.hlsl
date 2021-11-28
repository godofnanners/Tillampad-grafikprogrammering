#include "ModelTextureFunctions.hlsli"
//struct GBufferOutput
//{
//    float4 myWorldPosition : SV_TARGET0;
//    float4 myAlbedo : SV_TARGET1;
//    float4 myNormal : SV_TARGET2;
//    float4 myVertexNormal : SV_TARGET3;
//    float myMetalness : SV_TARGET4;
//    float myRoughness : SV_TARGET5;
//    float myAmbientOcclusion : SV_TARGET6;
//    float myEmissive : SV_TARGET7;
//};

GBufferOutput main(VertexToPixel input)
{
    float3 albedo = PixelShader_Albedo(input).myColor.rgb;
    float3 normal = PixelShader_Normal(input).myColor.xyz;
    float ambientOcclusion = PixelShader_AmbientOcclusion(input).myColor.r;
    float metalness = PixelShader_Metalness(input).myColor.r;
    float perceptualRoughness = PixelShader_PerceptualRoughness(input).myColor.r;
    float emissive = PixelShader_Emissive(input).myColor.r;

    GBufferOutput output;
    output.myWorldPosition = input.myWorldPosition;
    output.myAlbedo = float4(albedo, 1.0f);
    output.myNormal = float4(normal, 1.0f);
    output.myVertexNormal = float4(input.myNormal.xyz, 1.0f);
    output.myMetalness = metalness;
    output.myRoughness = perceptualRoughness;
    output.myAmbientOcclusion = ambientOcclusion;
    output.myEmissive = emissive;
    return output;
}