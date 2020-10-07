TextureCube EnvironmentCubemapTexture : register(t0);
texture2D albedoTexture : register(t1);
texture2D normalTexture : register(t2);
texture2D materialTexture : register(t3);

SamplerState defaultSampler : register(s0);

struct VertexInput
{
	float4 myPosition : POSITION;
	float4 myNormal : NORMAL;
	float4 myTangent : TANGENT;
	float4 myBinormal : BINORMAL;
	float2 myUV : UV;
};

struct VertexToPixel
{
	float4 myPosition:SV_POSITION;
    float4 myWorldPosition : POSITION;
	float4 myNormal : NORMAL;
	float4 myTangent : TANGENT;
	float4 myBinormal : BINORMAL;
	float2 myUV : UV;
};

struct PixelOutput
{
	float4 myColor:SV_TARGET;
};

cbuffer FrameBuffer : register(b0)
{
	float4x4 toCamera;
	float4x4 toProjection;
    float4 cameraPosition;
    float4 toDirectionalLight;
    float4 directionalLightColor;
    unsigned int environmentalLightMipCount;
    unsigned int trash[3];
}

cbuffer ObjectBuffer : register(b1)
{
	float4x4 toWorld;
}
