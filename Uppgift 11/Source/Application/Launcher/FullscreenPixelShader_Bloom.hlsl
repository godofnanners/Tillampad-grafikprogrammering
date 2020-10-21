#include "FullscreenShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
    PixelOutput returnValue;
    float3 resource = FullscreenTexture1.Sample(defaultSampler, input.myUV.xy).rgb;
    float3 resource2 = FullscreenTexture2.Sample(defaultSampler, input.myUV.xy).rgb;
    {
        float luminance = dot(resource, float3(0.2126f, 0.7152f, 0.0722f));
        resource2 *= (1.0f - luminance);
        returnValue.myColor.rgb = resource + resource2;
    }
    returnValue.myColor.a = 1.0f;
    return returnValue;
}