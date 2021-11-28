#include "ParticleShaderStructs.hlsli"

VertexToGeometry main(VertexInput input)
{
    VertexToGeometry returnValue;
    float4 vertexObjectPos = input.myPosition.xyzw;
    float4 vertexWorldPos = mul(ToWorld, vertexObjectPos);
    float4 vertexViewPos = mul(ToCamera, vertexWorldPos);
    returnValue.myPosition = vertexViewPos;
    returnValue.myColor = input.myColor;
    returnValue.mySize = input.mySize;
    return returnValue;
}