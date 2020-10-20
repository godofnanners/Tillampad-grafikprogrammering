#include "FullscreenShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
    PixelOutput returnValue;
    float texelsize = 1.0f / Resolution.x;
    float3 blurcolor = float3(0.0f, 0.0f, 0.0f);

    unsigned int kernelsize = 5;
    float start = (((float) (kernelsize) - 1.0f) / 2.0f) * -1.0f;
    for (unsigned int index = 0; index < kernelsize;index++)
    {
        float2 uv = input.myUV.xy + float2(texelsize * (start + (float) index), 0.0f);
        float3 resource = FullscreenTexture1.Sample(defaultSampler, uv).rgb;
        blurcolor += resource * GaussianKernel5[index];
    }
    returnValue.myColor.rgb = blurcolor;
    returnValue.myColor.a = 1.0f;
    return returnValue;
}