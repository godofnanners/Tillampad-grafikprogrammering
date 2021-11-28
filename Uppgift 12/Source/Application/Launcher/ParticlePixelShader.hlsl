#include "ParticleShaderStructs.hlsli"

PixelOutput main(GeometryToPixel input)
{
    PixelOutput output;
    float4 texturecolor = ParticleTexture.Sample(DefaultSampler, input.myUV.xy).rgba;
    output.myColor.rgba = texturecolor.rgba * input.myColor.rgba;
    return output;
}