#pragma once
#include<d3d11.h>
#include "StaticArray.h"
class CModel
{
public:
	struct SModelData
	{
		UINT myNumberOfVerticies = 0;
		UINT myNumberOfIndices = 0;
		UINT myStride = 0;
		UINT myOffset = 0;
		ID3D11Buffer* myVertexBuffer = nullptr;
		ID3D11Buffer* myIndexBuffer = nullptr;
		ID3D11VertexShader* myVertexShader = nullptr;
		ID3D11PixelShader* myPixelShader = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY myPrimitiveTopology;
		ID3D11InputLayout* myInputLayout = nullptr;
		CommonUtilities::StaticArray<ID3D11ShaderResourceView*, 6> myTexture = { nullptr };
	};
	void Init(SModelData aModelData);
	const SModelData& GetModelData();
private:
	SModelData myModelData;
};

