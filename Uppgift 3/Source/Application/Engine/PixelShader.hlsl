#include "ShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
	PixelOutput returnValue;
	returnValue.myColor = input.myColor;
	return returnValue;
}