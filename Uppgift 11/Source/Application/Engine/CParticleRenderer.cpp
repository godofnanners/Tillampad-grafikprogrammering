#include "CParticleRenderer.h"
#include <d3d11.h>
#include "CCamera.h"
#include "CDirectX11Framework.h"
#include "CParticle.h"
#include "CParticleInstance.h"

bool CParticleRenderer::Init(CDirectX11Framework* aFramework)
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
	return false;
}

void CParticleRenderer::Render(CCamera* aCamera, std::vector<CParticleInstance*>& aParticleList)
{
	HRESULT	 result;
	D3D11_MAPPED_SUBRESOURCE bufferData;

	myFrameBufferData.myToCamera = aCamera->GetTransform();
	myFrameBufferData.myToCamera = CommonUtilities::Matrix4x4<float>::GetFastInverse(myFrameBufferData.myToCamera);
	myFrameBufferData.myToProjection = aCamera->GetProjection();
	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
	{
		assert(!"Couldnt map frambuffer in CParticleRenderer");
	}
	memcpy(bufferData.pData, &myFrameBufferData, sizeof(FrameBufferData));
	myContext->Unmap(myFrameBuffer, 0);
	myContext->VSSetConstantBuffers(0, 1, &myFrameBuffer);
	myContext->GSSetConstantBuffers(0, 1, &myFrameBuffer);

	for (unsigned int instanceIndex = 0; instanceIndex < aParticleList.size(); instanceIndex++)
	{
		if (aParticleList[instanceIndex]->GetParticleVerteces().size() <= 0)
		{
			continue;
		}
		else
		{
			CParticleInstance* instance = aParticleList[instanceIndex];
			CParticle* particle = instance->GetParticle();
			myObjectBufferData.myToWorld = instance->GetTransform();
			ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
			result = myContext->Map(myObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
			if (FAILED(result))
			{
				assert(!"Couldnt map objectbuffer in CParticleRender");
			}
			memcpy(bufferData.pData, &myObjectBuffer, sizeof(ObjectBufferData));
			myContext->Unmap(myObjectBuffer, 0);

			CParticle::SParticleData particleData = particle->GetParticleData();

			ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
			result = myContext->Map(particleData.myPartcleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
			if (FAILED(result))
			{
				assert(!"Couldnt map VertexBuffer in CParticleRenderer");
			}
			memcpy(bufferData.pData, &(instance->GetParticleVerteces()[0]), sizeof(CParticle::SParticleVertex) * instance->GetParticleVerteces().size());
			myContext->Unmap(particleData.myPartcleVertexBuffer, 0);

			myContext->IASetPrimitiveTopology(particleData.myPrimitiveTopology);
			myContext->IASetInputLayout(particleData.myInputLayout);
			myContext->IASetVertexBuffers(0, 1, &particleData.myPartcleVertexBuffer, &particleData.myStride, &particleData.myOffset);

			myContext->VSSetConstantBuffers(1, 1, &myObjectBuffer);
			myContext->VSSetShader(particleData.myVertexShader, nullptr, 0);

			myContext->GSSetShader(particleData.myGeometryShader, nullptr, 0);

			myContext->PSSetConstantBuffers(1, 1, &myObjectBuffer);
			myContext->PSSetShaderResources(0, 1, &particleData.myTexture);
			myContext->PSSetShader(particleData.myPixelShader, nullptr, 0);

			myContext->Draw(particleData.myNumberOfParticles, 0);
		}
	}
}
