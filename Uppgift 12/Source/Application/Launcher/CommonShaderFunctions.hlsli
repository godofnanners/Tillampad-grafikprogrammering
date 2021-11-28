float3 LinearToGamma(float3 aColor)
{
    return pow(abs(aColor), 1.0 / 2.2);
}

float3 GammaToLinear(float3 aColor)
{
    return pow(abs(aColor), 2.2);
}

int GetNumMips(TextureCube cubeTex)
{
    int iWidth = 0, iHeight = 0, numMips = 0;
    cubeTex.GetDimensions(0, iWidth, iHeight, numMips);
    return numMips;
}