#pragma once
#include<d3d11.h>

class CModel
{
public:
	struct SModelData
	{
		UINT myNumberOfVerticies;
		UINT myNumberOfIndices;
		UINT myStride;
		UINT myOffset;
		ID3D11Buffer* myVertexBuffer;
		ID3D11Buffer* myIndexBuffer;
		ID3D11VertexShader* myVertexShader;
		ID3D11PixelShader* myPixelShader;
		D3D11_PRIMITIVE_TOPOLOGY myPrimitiveTopology;
		ID3D11InputLayout* myInputLayout;
	};
	void Init(SModelData aModelData);
	const SModelData& GetModelData();
private:
	SModelData myModelData;
};

