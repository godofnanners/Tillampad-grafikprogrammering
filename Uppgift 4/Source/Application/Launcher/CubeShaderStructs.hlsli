

texture2D instanceTexture : register(t0);
SamplerState defaultSampler : register(s0);
//Filter D3D11_FFILTER_MIN_MAG_MIP_LINEAR
//AdressU D3D11_TEXTURE_ADRESS_CLAMP
//AdressV D3D11_TEXTURE_ADRESS_CLAMP
//AdressW D3D11_TEXTURE_ADRESS_CLAMP
//MinLOD - 3.402823466e+38F (-FLT_MAX)
//MaxLOD 3.402823466e+38F (FLT_MAX)
//MipMapLODBias 0.0f
//MaxAnisotropy 1
//CompariosnFunc D3D11_COMPARISON_NEVER
//BorderColor float4(1.0f, 1.0f, 1.0f, 1.0f)
//Texture N/A


struct VertexInput
{
	float4 myPosition : POSITION;
	float4 myColor : COLOR;
	float2 myUV : UV;
};

struct VertexToPixel
{
	float4 myPosition:SV_POSITION;
	float4 myColor : COLOR;
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

