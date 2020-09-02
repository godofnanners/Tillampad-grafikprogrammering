#pragma once

class ID3D11Buffer;
class ID3D11VertexShader;
class ID3D11PixelShader;
class ID3D11InputLayout;
class CModel
{
public:
	struct SModelData
	{
		int myNumberOfVerticies;
		int myStride;
		int myOffset;
		ID3D11Buffer* myVertexBuffer;
		ID3D11VertexShader* myVertexShader;
		ID3D11PixelShader* myPixelShader;
		int myPrimitiveTopology;
		ID3D11InputLayout* myInputLayout;
	};
	void Init(SModelData aModelData);
private:
};

