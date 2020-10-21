#include "CDirectX11Framework.h"
#include "CWindowHandler.h"
#include <iostream>
#include<d3d11.h>
#include "CFullscreenTexture.h"
#include "CFullscreenTextureFactory.h"
#pragma comment (lib,"d3d11.lib")
CDirectX11Framework::CDirectX11Framework() :myBackBufferTexture(nullptr), myContext(nullptr), myDevice(nullptr), mySwapChain(nullptr)
{
    myDepthBuffer = nullptr;
    myContext = nullptr;
    myBackBuffer = nullptr;

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

	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&myBackBufferTexture);
	if (FAILED(result))
	{
        assert(!"Swapchain failed in framework failed");
    }
	
    result = myDevice->CreateRenderTargetView(myBackBufferTexture, nullptr, &myBackBuffer);
    if (FAILED(result))
    {
        assert(!"Creaing Texture2D in framework failed");
        return false;
    }

	result = myBackBufferTexture->Release();
	if (FAILED(result))
	{
        assert(!"Releasing BackbufferTexture in framework failed");
	}

    //Temporary
    ID3D11Texture2D* depthbufferTexture;
    D3D11_TEXTURE2D_DESC depthbufferDescription = { 0 };
    depthbufferDescription.Width = static_cast<unsigned int>(aWindowHandler->GetWidth());
    depthbufferDescription.Height = static_cast<unsigned int>(aWindowHandler->GetHeight());
    depthbufferDescription.ArraySize = 1;
    depthbufferDescription.Format = DXGI_FORMAT_D32_FLOAT;
    depthbufferDescription.SampleDesc.Count = 1;
    depthbufferDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    result = myDevice->CreateTexture2D(&depthbufferDescription, nullptr, &depthbufferTexture);
    if (FAILED(result))
    {
        assert(!"Creaing Texture2D in framework failed");
        return false;
    }

    result = myDevice->CreateDepthStencilView(depthbufferTexture, nullptr, &myDepthBuffer);
    if (FAILED(result))
    {
        assert(!"Creaing DepthStencilView in framework failed");
        return false;
    }

    myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

    D3D11_VIEWPORT viewport = { 0 };
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.f;
    viewport.Width = static_cast<float>(aWindowHandler->GetWidth());
    viewport.Height = static_cast<float>(aWindowHandler->GetHeight());
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.0f;
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
	myContext->ClearRenderTargetView(myBackBuffer, &aClearColor[0]);
	myContext->ClearDepthStencilView(myDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void CDirectX11Framework::EndFrame()
{
	mySwapChain->Present(1, 0);
}
