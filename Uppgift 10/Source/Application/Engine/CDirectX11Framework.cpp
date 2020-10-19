#include "CDirectX11Framework.h"
#include "CWindowHandler.h"
#include <iostream>
#include<d3d11.h>
#include "CFullscreenTexture.h"
#include "CFullscreenTextureFactory.h"
#pragma comment (lib,"d3d11.lib")
CDirectX11Framework::CDirectX11Framework() :myBackBufferTexture(nullptr), myContext(nullptr), myDevice(nullptr), mySwapChain(nullptr)
{
}
CDirectX11Framework::~CDirectX11Framework()
{

}
bool CDirectX11Framework::Init(CWindowHandler* aWindowHandler)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapchainDescription = {};
	swapchainDescription.BufferCount = 1;
	swapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDescription.OutputWindow = aWindowHandler->GetWindowHandle();
	swapchainDescription.SampleDesc.Count = 1;
	swapchainDescription.Windowed = true;

	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapchainDescription, &mySwapChain, &myDevice, nullptr, &myContext);

	ID3D11Texture2D* backbufferTexture;

	CFullscreenTextureFactory::GetInstance().CreateTexture(backbufferTexture);

	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferTexture);
	if (FAILED(result))
	{
		std::cout << "DirectX SwapChain Failed/n";
	}
	
	result = backbufferTexture->Release();
	if (FAILED(result))
	{
		std::cout << "DirectX backbufferTexture Failed/n";
	}

	//Temporary
	CFullscreenTexture depthbufferTexture;
	depthbufferTexture = CFullscreenTextureFactory::GetInstance().CreateDepth({ aWindowHandler->GetWidth(), aWindowHandler->GetHeight() }, DXGI_FORMAT_D32_FLOAT);

	
	myBackBuffer->SetAsActiveTarget(&depthbufferTexture);

	myContext->RSSetViewports(1, &viewport);
	//Temporary

	return true;
}

ID3D11DeviceContext* CDirectX11Framework::GetContext()
{
	return myContext;
}

ID3D11Device* CDirectX11Framework::GetDevice()
{
	return myDevice;
}

ID3D11Texture2D* CDirectX11Framework::GetBackbufferTexture()
{
	return myBackBufferTexture;
}

void CDirectX11Framework::BeginFrame(std::array<float, 4> aClearColor)
{
	myBackBuffer->ClearTexture();
	myBackBuffer->ClearDepth();
}

void CDirectX11Framework::EndFrame()
{
	mySwapChain->Present(1, 0);
}
