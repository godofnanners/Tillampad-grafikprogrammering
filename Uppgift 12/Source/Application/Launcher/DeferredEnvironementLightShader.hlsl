#include "LightIncludes.hlsli"
#include "PBRFunctions.hlsli"

PixelOutput main(VertexToPixel input)
{
    float exists = PixelShader_Exists(input).myColor.r;
    if (exists == 0)
        discard;

    PixelOutput output;

    float3 worldPosition = PixelShader_WorldPosition(input).myColor.rgb;
    float3 toEye = normalize(cameraPosition.xyz - worldPosition.xyz);
    float3 albedo = PixelShader_Albedo(input).myColor.rgb;
    albedo = GammaToLinear(albedo);
    float3 normal = PixelShader_Normal(input).myColor.xyz;
    float3 vertexNormal = PixelShader_VertexNormal(input).myColor.xyz;
    float ambientOcclusion = PixelShader_AmbientOcclusion(input).myColor.r;
    float metalness = PixelShader_Metalness(input).myColor.r;
    float perceptualRoughness = PixelShader_PerceptualRoughness(input).myColor.r;
    float emissiveData = PixelShader_Emissive(input).myColor.r;

    float3 specularColor = lerp((float3) 0.04, albedo, metalness);
    float3 diffuseColor = lerp((float3) 0.00, albedo, 1 - metalness);

    float3 ambience = EvaluateAmbience(environmentTexture, normal, vertexNormal, toEye, perceptualRoughness, metalness, albedo, ambientOcclusion, diffuseColor, specularColor);
    float3 directionalLight = EvaluateDirectionalLight(diffuseColor, specularColor, normal, perceptualRoughness, directionalLightColor.xyz, toDirectionalLight.xyz, toEye.xyz);
    if (emissiveData < 0.2f)
    {
        emissiveData = 0.f;
    }
    float3 emissive = albedo * emissiveData;
    float3 radiance = ambience + directionalLight + emissive;

    output.myColor.rgb = radiance;
    output.myColor.a = 1.0f;
    return output;
}