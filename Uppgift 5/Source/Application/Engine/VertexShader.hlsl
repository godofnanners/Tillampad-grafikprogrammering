#include "ShaderStructs.hlsli"

VertexToPixel main(VertexInput input)
{
	VertexToPixel returnValue;

	float4 vertexObjectPos = input.myPosition.xyzw;
	float4 vertexWorldPos = mul(toWorld, vertexObjectPos);
	float4 vertexViewPos = mul(toCamera, vertexWorldPos);
	float4 vertexProjectionPos = mul(toProjection, vertexViewPos);

	returnValue.myPosition = vertexProjectionPos;
	returnValue.myNormal = input.myNormal;
	returnValue.myTangent = input.myTangent;
	returnValue.myBinormal = input.myBinormal;
	returnValue.myUV = input.myUV;
	return returnValue;
}