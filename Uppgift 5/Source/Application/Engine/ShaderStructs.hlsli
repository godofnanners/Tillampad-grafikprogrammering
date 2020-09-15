texture2D instanceTexture : register(t0);
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
}

cbuffer ObjectBuffer : register(b1)
{
	float4x4 toWorld;
}
