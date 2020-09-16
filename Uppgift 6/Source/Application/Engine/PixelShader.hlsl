#include "ShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
	PixelOutput returnValue;
    float3 normal = normalTexture.Sample(defaultSampler, input.myUV.xy).rgb;
    normal = (normal * 2) - 1;
	
    float3x3 tangentspacematrix = float3x3(normalize(input.myTangent.xyz), normalize(input.myBinormal.xyz), normalize(input.myNormal.xyz));
    tangentspacematrix = transpose(tangentspacematrix);
    float3 pixelnormal = mul(tangentspacematrix, normal.xyz);
    returnValue.myColor = float4(pixelnormal, 1);
	//float4 textureColor = instanceTexture.Sample(defaultSampler, input.myUV.xy).rgba;
	//returnValue.myColor = textureColor;
	//returnValue.myColor = input.myColor;
	return returnValue;
}