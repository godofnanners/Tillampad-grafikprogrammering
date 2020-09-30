#include "ShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
	PixelOutput returnValue;
    float3 textureColor = albedoTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    float3 textureNormal = normalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    textureNormal = (textureNormal * 2) - 1;
	
    float3x3 tangentspacematrix = float3x3(normalize(input.myTangent.xyz), normalize(input.myBinormal.xyz), normalize(input.myNormal.xyz));
    tangentspacematrix = transpose(tangentspacematrix);
    float3 pixelnormal = mul(tangentspacematrix, textureNormal.xyz);
    
    float3 environmentColor = EnvironmentCubemapTexture.SampleLevel(defaultSampler, pixelnormal, 8).rgb;
    float attenuation = saturate(dot(pixelnormal, toDirectionalLight.xyz));
    
    float3 ambient = textureColor * environmentColor;
    float3 diffuse = textureColor * attenuation * directionalLightColor.rgb;
    
    float3 returnColor = ambient + diffuse;
    returnValue.myColor = float4(returnColor.xyz, 1);
	return returnValue;
}