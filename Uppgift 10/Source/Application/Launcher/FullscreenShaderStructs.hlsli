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