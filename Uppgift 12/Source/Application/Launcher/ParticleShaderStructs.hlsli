struct VertexInput
{
    float myLifetime : LIFETIME;
    float4 myPosition : POSITION;
    float4 myMovement : MOVEMENT;
    float4 myColor : COLOR;
    float2 mySize : SIZE;
    float myDistanceToCamera : DISTANCE;
};

struct VertexToGeometry
{
    float4 myPosition : SV_POSITION;
    float4 myColor : COLOR;
    float2 mySize : SIZE;
};

struct GeometryToPixel
{
    float4 myPosiiton : SV_POSITION;
    float4 myColor : COLOR;
    float2 myUV : UV;
};
struct PixelOutput
{
    float4 myColor : SV_TARGET;
};
cbuffer FrameBuffer : register(b0)
{
    float4x4 ToCamera;
    float4x4 ToProjection;
}
cbuffer ObjectBuffer : register(b1)
{
    float4x4 ToWorld;
}

Texture2D ParticleTexture : register(t0);
SamplerState DefaultSampler : register(s0);