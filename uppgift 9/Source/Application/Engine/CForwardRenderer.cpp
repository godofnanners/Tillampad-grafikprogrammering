#include "CForwardRenderer.h"
#include "CDirectX11Framework.h"
#include <d3d11.h>
#include "CModel.h"
#include "CModelInstance.h"
#include "CCamera.h"
#include "CEnvironmentLight.h"
#include "CPointLight.h"
CForwardRenderer::CForwardRenderer()
{
	myContext = nullptr;
	myFrameBuffer = nullptr;
	myObjectBuffer = nullptr;
}

CForwardRenderer::~CForwardRenderer()
{
	myContext = nullptr;
	myFrameBuffer = nullptr;
	myObjectBuffer = nullptr;
}

bool CForwardRenderer::Init(CDirectX11Framework* aFramework)
{
	if (!aFramework)
	{
		return false;
	}

	myContext = aFramework->GetContext();

	if (!myContext)
	{
		return false;
	}

	ID3D11Device* device = aFramework->GetDevice();
	if (!device)
	{
		return false;
	}
	HRESULT result;

	D3D11_BUFFER_DESC bufferDescription = { 0 };
	bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferDescription.ByteWidth = sizeof(FrameBufferData);
	result = device->CreateBuffer(&bufferDescription, nullptr, &myFrameBuffer);
	if (FAILED(result))
	{
		return false;
	}
	bufferDescription.ByteWidth = sizeof(ObjectBufferData);
	result = device->CreateBuffer(&bufferDescription, nullptr, &myObjectBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void CForwardRenderer::Render(std::vector<CModelInstance*>& aModelList, CCamera* aCamera, const CommonUtilities::GrowingArray<CommonUtilities::VectorOnStack<CPointLight*, 8>>& aPointLightList, CEnvironmentLight* anEnvironmentLight)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE bufferdata;

	myFrameBufferData.myToCamera = CommonUtilities::Matrix4x4<float>::GetFastInverse(aCamera->GetTransform());
	myFrameBufferData.myToProjection = aCamera->GetProjection();
	myFrameBufferData.myCameraPosition = { aCamera->GetTransform().GetPosition(),1.0f };
	myFrameBufferData.myDirectionalLightDirection = { anEnvironmentLight->GetDirection() ,1.f };
	myFrameBufferData.myDirectionalLightColor = { anEnvironmentLight->GetColor() ,1.f };

	ZeroMemory(&bufferdata, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferdata);
	if (FAILED(result))
	{
		assert(L"Mapping of FrameBuffer failed");
	}
	ID3D11ShaderResourceView* shaderResourceviews = { anEnvironmentLight->GetCubemap() };


	memcpy(bufferdata.pData, &myFrameBufferData, sizeof(FrameBufferData));
	myContext->Unmap(myFrameBuffer, 0);
	myContext->VSSetConstantBuffers(0, 1, &myFrameBuffer);
	myContext->PSSetConstantBuffers(0, 1, &myFrameBuffer);
	myContext->PSSetShaderResources(0, 1, &shaderResourceviews);
	//TODO inmplement the mainCamera
	unsigned short modelLightIndex = 0;
	for (CModelInstance* instance : aModelList)
	{
		CModel* model = instance->GetModel();
		CModel::SModelData modelData = model->GetModelData();

		myObjectBufferData.myToWorld = instance->GetTransform();
		myObjectBufferData.myNumberOfUsedPointLights = aPointLightList[modelLightIndex].Size();
		for (unsigned short lightIndex = 0; lightIndex < myObjectBufferData.myNumberOfUsedPointLights; lightIndex++)
		{
			myObjectBufferData.myPointLights[lightIndex].myPosition = { aPointLightList[modelLightIndex][lightIndex]->GetPosition(), 1};
			myObjectBufferData.myPointLights[lightIndex].myColor = aPointLightList[modelLightIndex][lightIndex]->GetColor();
			myObjectBufferData.myPointLights[lightIndex].myRange = aPointLightList[modelLightIndex][lightIndex]->GetRange();
			myObjectBufferData.myPointLights[lightIndex].myIntensity = aPointLightList[modelLightIndex][lightIndex]->GetIntensity();
		}
		modelLightIndex++;
		ZeroMemory(&bufferdata, sizeof(D3D11_MAPPED_SUBRESOURCE));
		result = myContext->Map(myObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferdata);
		if (FAILED(result))
		{
			assert(L"Mapping of ObjectBuffer failed");
		}
		memcpy(bufferdata.pData, &myObjectBufferData, sizeof(ObjectBufferData));
		myContext->Unmap(myObjectBuffer, 0);

		myContext->IASetPrimitiveTopology(modelData.myPrimitiveTopology);
		myContext->IASetInputLayout(modelData.myInputLayout);
		myContext->IASetVertexBuffers(0, 1, &modelData.myVertexBuffer, &modelData.myStride, &modelData.myOffset);
		myContext->IASetIndexBuffer(modelData.myIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		myContext->VSSetConstantBuffers(1, 1, &myObjectBuffer);
		myContext->PSSetConstantBuffers(1, 1, &myObjectBuffer);
		myContext->VSSetShader(modelData.myVertexShader, nullptr, 0);

		myContext->PSSetShaderResources(1, 3, &modelData.myTexture[0]);
		myContext->PSSetShader(modelData.myPixelShader, nullptr, 0);

		//myContext->Draw(modelData.myNumberOfVerticies, 0);
		myContext->DrawIndexed(modelData.myNumberOfIndices, 0, 0);
	}
}
