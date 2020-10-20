#pragma once
#include <array>
struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
class CWindowHandler;
class CFullscreenTexture;
class CDirectX11Framework
{
public:
	CDirectX11Framework();
	~CDirectX11Framework();
	bool Init(CWindowHandler* aWindowHandler);
	ID3D11DeviceContext* GetContext();
	ID3D11Device* GetDevice();
	ID3D11Texture2D* GetBackbufferTexture();
	void BeginFrame(std::array<float, 4>aClearColor);
	void EndFrame();
private:
	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myContext;
	ID3D11Texture2D* myBackBufferTexture;
	ID3D11RenderTargetView* myBackBuffer;
	ID3D11DepthStencilView* myDepthBuffer;
};

