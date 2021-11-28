#include "LightIncludes.hlsli"
#include "PBRFunctions.hlsli"

PixelOutput main(VertexToPixel input)
{
    PixelOutput output;

    float3 worldPosition = PixelShader_WorldPosition(input).myColor.rgb;
    float3 toEye = normalize(cameraPosition.xyz - worldPosition.xyz);
    float3 albedo = PixelShader_Albedo(input).myColor.rgb;
    albedo = GammaToLinear(albedo);
    float3 normal = PixelShader_Normal(input).myColor.xyz;
    float metalness = PixelShader_Metalness(input).myColor.r;
    float perceptualRoughness = PixelShader_PerceptualRoughness(input).myColor.r;

    float3 specularColor = lerp((float3) 0.04, albedo, metalness);
    float3 diffuseColor = lerp((float3) 0.00, albedo, 1 - metalness);

    float3 toLight = myPosition.xyz - worldPosition.xyz;
    float lightDistance = length(toLight);
    toLight = normalize(toLight);
    float3 radiance = EvaluatePointLight(diffuseColor, specularColor, normal, perceptualRoughness, myColour, myIntensity, myRange, toLight.xyz, lightDistance, toEye.xyz);

    output.myColor.rgb = radiance;
    output.myColor.a = 1.0f;
    return output;
}