
struct VertexInput
{
    unsigned int myIndex : SV_VertexID;
};

struct VertexToPixel
{
    float4 myPosition : SV_POSITION;
    float2 myUV : UV;
};

struct PixelOutput
{
    float4 myColor : SV_TARGET;
};

texture2D FullscreenTexture1 : register(t0);
texture2D FullscreenTexture2 : register(t1);
SamplerState defaultSampler : register(s0);

static const float2 Resolution = float2(1600.0f, 900.0f) / 8.0f;
static const float GaussianKernel5[5] = { 0.06136f, 0.24477f, 0.38774f, 0.24477f, 0.06136 };