#pragma once
#include <array>
#include <d3d11.h>
class CWindowHandler;
class CDirectX11Framework
{
public:
	CDirectX11Framework();
	~CDirectX11Framework();
	bool Init(CWindowHandler* aWindowHandler);
	void BeginFrame(std::array<float, 4>aClearColor);
	void EndFrame();
private:
	IDXGISwapChain *mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myContext;
	ID3D11RenderTargetView* myBackBuffer;
};

