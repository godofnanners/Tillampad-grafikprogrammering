#include "ParticleShaderStructs.hlsli"

[maxvertexcount(4)]
void main(
	point VertexToGeometry input[1],
	inout TriangleStream<GeometryToPixel> output
)
{
    const float2 offset[4] =
    {
        { -1.0f, -1.0f },
        { 1.0f, 1.0f },
        { -1.0f, -1.0f },
        { 1.0f, -1.0f }
    };

    const float2 uv[4] =
    {
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 0.0f, 1.0f },
        { 1.0f, 1.0f }
    };
    
    VertexToGeometry inputvertex = input[0];
    for (unsigned int index = 0; index < 4; index++)
    {
        GeometryToPixel vertex;
        vertex.myPosiiton = inputvertex.myPosition;
        vertex.myPosiiton.xy += offset[index] * inputvertex.mySize;
        vertex.myPosiiton = mul(ToProjection, vertex.myPosiiton);
        vertex.myColor = inputvertex.myColor;
        vertex.myUV = uv[index];
        output.Append(vertex);
    }

}