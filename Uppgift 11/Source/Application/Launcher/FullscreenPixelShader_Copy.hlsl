#include "FullscreenShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
    PixelOutput returnValue;
    float3 resource = FullscreenTexture1.Sample(defaultSampler, input.myUV.xy).rgb;
    returnValue.myColor.rgb = resource;
    returnValue.myColor.a = 1.0f;
    return returnValue;
}