#include "CGBuffer.h"
#include <d3d11.h>
#include "CFullscreenTexture.h"
#include "CDirectX11Framework.h"

CGBuffer::CGBuffer()
{
}

CGBuffer::~CGBuffer()
{
}

bool CGBuffer::Init(CDirectX11Framework& aFramework, CommonUtilities::Vector2<float> aScreensize)
{
	myViewport = new D3D11_VIEWPORT({ 0.0f,0.0f,aScreensize.x,aScreensize.y,0.0f,1.0f });
	myContext = aFramework.GetContext();

	std::array<DXGI_FORMAT, GBUFFERTEXTURE_COUNT> textureFormats =
	{
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R16G16B16A16_SNORM,
		DXGI_FORMAT_R16G16B16A16_SNORM,
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R8_UNORM,
		DXGI_FORMAT_R8_UNORM
	};


	for (int i = 0; i < GBUFFERTEXTURE_COUNT; i++)
	{

		D3D11_TEXTURE2D_DESC textureDesc = { 0 };
		textureDesc.Width = static_cast<unsigned int>(aScreensize.x);
		textureDesc.Height = static_cast<unsigned int>(aScreensize.y);
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = textureFormats[i];
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		HRESULT result;
		result = aFramework.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &myTextures[i]);
		if (FAILED(result))
		{
			return false;
		}


		result = aFramework.GetDevice()->CreateRenderTargetView(myTextures[i], nullptr, &myRenderTargets[i]);
		if (FAILED(result))
		{
			return false;
		}

		result = aFramework.GetDevice()->CreateShaderResourceView(myTextures[i], nullptr, &myShaderResources[i]);
		if (FAILED(result))
		{
			return false;
		}
	}

	return true;
}

void CGBuffer::SetViewport(D3D11_VIEWPORT* aViewport)
{
	myViewport = aViewport;
}

void CGBuffer::ClearTextures(CommonUtilities::Vector4<float> aClearColor)
{
	for (ID3D11RenderTargetView* renderTarget : myRenderTargets)
	{
		myContext->ClearRenderTargetView(renderTarget, &aClearColor.x);
	}
}

void CGBuffer::SetAsActiveTarget(CFullscreenTexture* aDepth)
{
	if (aDepth)
	{
		myContext->OMSetRenderTargets(GBufferTextures::GBUFFERTEXTURE_COUNT, &myRenderTargets[0], aDepth->myDepth);
	}
	else
	{
		myContext->OMSetRenderTargets(GBufferTextures::GBUFFERTEXTURE_COUNT,&myRenderTargets[0],nullptr);
	}
	myContext->RSSetViewports(1, myViewport);
}

void CGBuffer::SetAsResourceOnSlot(GBufferTextures aResource, unsigned int aSlot)
{
}

void CGBuffer::SetAllAsResources()
{
	myContext->PSSetShaderResources(1, GBufferTextures::GBUFFERTEXTURE_COUNT, &myShaderResources[0]);
}
