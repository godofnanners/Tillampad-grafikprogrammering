#include "CDeferredRenderer.h"
#include "CDirectX11Framework.h"
#include <fstream>
#include "CModel.h"

bool CDeferredRenderer::Init(CDirectX11Framework& aFramework)
{
	myContext = aFramework.GetContext();
	myDevice = aFramework.GetDevice();
	
	if (!myDevice)
		return false;
	HRESULT result;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferDesc.ByteWidth = sizeof(FrameBufferData);
	result = myDevice->CreateBuffer(&bufferDesc, nullptr, &myFrameBuffer);
	if (FAILED(result))
		return false;

	bufferDesc.ByteWidth = sizeof(ObjectBufferData);
	result = myDevice->CreateBuffer(&bufferDesc, nullptr, &myObjectBuffer);
	if (FAILED(result))
		return false;

	bufferDesc.ByteWidth = sizeof(EnvironmentLightBufferData);
	result = myDevice->CreateBuffer(&bufferDesc, nullptr, &myEnvironmentLightBuffer);
	if (FAILED(result))
		return false;

	bufferDesc.ByteWidth = sizeof(PointLightBufferData);
	result = myDevice->CreateBuffer(&bufferDesc, nullptr, &myPointLightBuffer);
	if (FAILED(result))
		return false;

	std::ifstream psFile;
	psFile.open("DeferredEnvironementLightShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = myDevice->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		psFile.close();
		return false;
	}
	psFile.close();
	myEnvironmentLightShader = pixelShader;


	std::ifstream ps2File;
	ps2File.open("DeferreddPointLightShader.cso", std::ios::binary);
	std::string ps2Data = { std::istreambuf_iterator<char>(ps2File), std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pointLightPixelShader;
	result = myDevice->CreatePixelShader(ps2Data.data(), ps2Data.size(), nullptr, &pointLightPixelShader);
	if (FAILED(result))
	{
		ps2File.close();
		return false;
	}
	ps2File.close();
	myPointLightShader = pointLightPixelShader;


	std::ifstream vsFile;
	vsFile.open("FullscreenVertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = myDevice->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		vsFile.close();
		return false;
	}
	vsFile.close();
	myFullscreenShader = vertexShader;



	std::ifstream gpsFile;
	gpsFile.open("GBuffer.cso", std::ios::binary);
	std::string gpsData = { std::istreambuf_iterator<char>(gpsFile), std::istreambuf_iterator<char>() };
	result = myDevice->CreatePixelShader(gpsData.data(), gpsData.size(), nullptr, &myGBufferPixelShader);
	if (FAILED(result))
	{
		gpsFile.close();
		return false;
	}
	gpsFile.close();


	return true;
}

void CDeferredRenderer::Render(CCamera* aMainCamera, CEnvironmentLight* aEnvironmentLight)
{
	if (!aMainCamera)
	{
		return;
	}
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE bufferData;
	D3D11_MAPPED_SUBRESOURCE bufferData2;

	myFrameBufferData.myToCamera = CommonUtilities::Matrix4x4<float>::GetFastInverse(aMainCamera->GetTransform());
	myFrameBufferData.myToProjection = aMainCamera->GetProjection();

	CommonUtilities::Vector4<float> campos = aMainCamera->GetPosition();
	campos.z = 1.f;
	myFrameBufferData.myCameraPosition = campos;

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		return;
	}
	memcpy(bufferData.pData, &myFrameBufferData, sizeof(FrameBufferData));
	myContext->Unmap(myFrameBuffer, 0);
	myContext->PSSetConstantBuffers(0, 1, &myFrameBuffer);

	myEnviromentLightBufferData.myToDirectionalLight = { aEnvironmentLight->GetDirection(), 0.0f };
	myEnviromentLightBufferData.myDirectionalLightColor = { aEnvironmentLight->GetColor(), 1.0f};
	ZeroMemory(&bufferData2, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myEnvironmentLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData2);
	if (FAILED(result))
	{
		assert(false && "Error in deferredRenderer2");
	}
	memcpy(bufferData2.pData, &myEnvironmentLightBuffer, sizeof(EnvironmentLightBufferData));
	myContext->Unmap(myEnvironmentLightBuffer, 0);
	myContext->PSSetConstantBuffers(1, 1, &myEnvironmentLightBuffer);


	ID3D11ShaderResourceView* cubeMap = aEnvironmentLight->GetCubemap();
	myContext->PSSetShaderResources(0, 1, &cubeMap);
	myContext->GSSetShader(nullptr, nullptr, 0);


	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	myContext->IASetInputLayout(nullptr);
	myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

	myContext->GSSetShader(nullptr, nullptr, 0);

	myContext->VSSetShader(myFullscreenShader, nullptr, 0);
	myContext->PSSetShader(myEnvironmentLightShader, nullptr, 0);

	myContext->Draw(3, 0);
}

void CDeferredRenderer::Render(CCamera* aMainCamera, std::vector<CPointLight*>& aPointLightList)
{
	if (!aMainCamera)
	{
		return;
	}

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE bufferData;
	D3D11_MAPPED_SUBRESOURCE bufferData2;

	myFrameBufferData.myToCamera = CommonUtilities::Matrix4x4<float>::GetFastInverse(aMainCamera->GetTransform());
	myFrameBufferData.myToProjection = aMainCamera->GetProjection();

	CommonUtilities::Vector4<float> campos = aMainCamera->GetPosition();
	campos.z = 1.f;
	myFrameBufferData.myCameraPosition = campos;

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		assert(false && "Error in forwardrenderer");
	}
	memcpy(bufferData.pData, &myFrameBufferData, sizeof(FrameBufferData));
	myContext->Unmap(myFrameBuffer, 0);
	myContext->VSSetConstantBuffers(0, 1, &myFrameBuffer);
	myContext->PSSetConstantBuffers(0, 1, &myFrameBuffer);

	for (CPointLight* currentInstance : aPointLightList)
	{

		myPointLightBufferData.myColor = currentInstance->GetColor();
		myPointLightBufferData.myIntensity = currentInstance->GetIntensity();
		myPointLightBufferData.myPosition = currentInstance->GetPosition();
		myPointLightBufferData.myRange = currentInstance->GetRange();

		ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
		result = myContext->Map(myPointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
		if (FAILED(result))
		{
			continue;
		}
		memcpy(bufferData.pData, &myPointLightBufferData, sizeof(PointLightBufferData));
		myContext->Unmap(myPointLightBuffer, 0);
		myContext->VSSetConstantBuffers(1, 1, &myPointLightBuffer);
		myContext->PSSetConstantBuffers(1, 1, &myPointLightBuffer);

		myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		myContext->IASetInputLayout(nullptr);
		myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
		myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

		myContext->GSSetShader(nullptr, nullptr, 0);

		myContext->VSSetShader(myFullscreenShader, nullptr, 0);
		myContext->PSSetShader(myPointLightShader, nullptr, 0);

		myContext->Draw(3, 0);
	}
}

void CDeferredRenderer::GenerateGBuffer(CCamera* aMainCamera, std::vector<CModelInstance*> aModelList)
{
	if (!aMainCamera || aModelList.empty())
	{
		return;
	}


	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE bufferdata;


	myFrameBufferData.myToCamera = CommonUtilities::Matrix4x4<float>::GetFastInverse(aMainCamera->GetTransform());
	myFrameBufferData.myToProjection = aMainCamera->GetProjection();
	CommonUtilities::Vector4<float>camPos = aMainCamera->GetPosition();
	camPos.z = 1.f;
	myFrameBufferData.myCameraPosition = camPos;

	ZeroMemory(&bufferdata, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferdata);
	if (FAILED(result))
	{
		assert(false && "Error in deferredRenderer");
	}
	memcpy(bufferdata.pData, &myFrameBufferData, sizeof(FrameBufferData));
	myContext->Unmap(myFrameBuffer, 0);
	myContext->VSSetConstantBuffers(0, 1, &myFrameBuffer);




	for (CModelInstance* instance : aModelList)
	{
		CModel* model = instance->GetModel();

		bool isLoaded = instance->GetModel() != nullptr;

		if (isLoaded)
		{
			CModel::SModelData data = model->GetModelData();

			myObjectBufferData.myToWorld = instance->GetTransform();



			ZeroMemory(&bufferdata, sizeof(D3D11_MAPPED_SUBRESOURCE));
			result = myContext->Map(myObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferdata);
			if (FAILED(result))
			{
				assert(false && "Error in deferredRenderer2");
			}
			memcpy(bufferdata.pData, &myObjectBufferData, sizeof(ObjectBufferData));
			myContext->Unmap(myObjectBuffer, 0);


			myContext->IASetPrimitiveTopology(data.myPrimitiveTopology);
			myContext->IASetInputLayout(data.myInputLayout);
			myContext->IASetVertexBuffers(0, 1, &data.myVertexBuffer, &data.myStride, &data.myOffset);
			myContext->IASetIndexBuffer(data.myIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

			myContext->VSSetConstantBuffers(1, 1, &myObjectBuffer);

			myContext->PSSetShaderResources(1, 3, &data.myTexture[0]);

			myContext->VSSetShader(data.myVertexShader, nullptr, 0);
			myContext->PSSetShader(myGBufferPixelShader, nullptr, 0);
			myContext->GSSetShader(nullptr, nullptr, 0);

			myContext->DrawIndexed(data.myNumberOfIndices, 0, 0);
		}

	}
}
