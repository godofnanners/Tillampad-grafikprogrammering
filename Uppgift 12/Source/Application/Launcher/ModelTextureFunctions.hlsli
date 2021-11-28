#include "CommonShaderFunctions.hlsli"
#include "..\Engine\ShaderStructs.hlsli"

PixelOutput PixelShader_Albedo(VertexToPixel input)
{
    PixelOutput output;
    float3 albedo = albedoTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    //albedo = GammaToLinear(albedo);
    output.myColor.rgb = albedo;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Normal(VertexToPixel input)
{
    float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    normal = (normal * 2) - 1;
    normal = normalize(normal);

    float3x3 tangentspacematrix = float3x3(normalize(input.myTangent.xyz), normalize(input.myBinormal.xyz), normalize(input.myNormal.xyz));
    normal = mul(normal.xyz, tangentspacematrix);
    normal = normalize(normal);

    PixelOutput output;
    output.myColor.xyz = normal.xyz;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_AmbientOcclusion(VertexToPixel input)
{
    PixelOutput output;
    float ao = normalTexture.Sample(defaultSampler, input.myUV.xy).a;
    output.myColor.rgb = ao.xxx;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Material(VertexToPixel input)
{
    PixelOutput output;
    float3 material = materialTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    output.myColor.rgb = material.rgb;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Metalness(VertexToPixel input)
{
    PixelOutput output;
    PixelOutput material = PixelShader_Material(input);
    output.myColor.rgb = material.myColor.rrr;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_PerceptualRoughness(VertexToPixel input)
{
    PixelOutput output;
    PixelOutput material = PixelShader_Material(input);
    output.myColor.rgb = material.myColor.ggg;
    output.myColor.a = 1.0f;
    return output;
}

PixelOutput PixelShader_Emissive(VertexToPixel input)
{
    PixelOutput output;
    PixelOutput material = PixelShader_Material(input);
    float emissive = material.myColor.b;
    emissive = 1.0f - emissive;
    emissive = pow(emissive, 10);
    emissive = 1.0f - emissive;
    output.myColor.rgb = emissive;
    output.myColor.a = 1.0f;
    return output;
}