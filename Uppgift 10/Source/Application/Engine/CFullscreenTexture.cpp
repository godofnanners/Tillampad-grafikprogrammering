#include "CFullscreenTexture.h"

CFullscreenTexture::CFullscreenTexture()
{
	myViewport = nullptr;
	myShaderResource = nullptr;
	myContext = nullptr;
	myDepth = nullptr;
	myTexture = nullptr;
	myRenderTarget = nullptr;
}

CFullscreenTexture::~CFullscreenTexture()
{
}

void CFullscreenTexture::ClearTexture(CommonUtilities::Vector4<float> aClearColor)
{
	myContext->ClearRenderTargetView(myRenderTarget, &aClearColor.x);
}

void CFullscreenTexture::ClearDepth(float aClearDepth, unsigned int aClearStencil)
{
	myContext->ClearDepthStencilView(myDepth, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, aClearDepth, (UINT8)aClearStencil);
}

void CFullscreenTexture::SetAsActiveTarget(CFullscreenTexture* aDepth)
{
	if (aDepth)
	{
		myContext->OMSetRenderTargets(1, &myRenderTarget, aDepth->myDepth);
	}
	else
	{
		myContext->OMSetRenderTargets(1, &myRenderTarget, nullptr);
	}
	myContext->RSSetViewports(1, myViewport);
}

void CFullscreenTexture::SetAsResourceOnSlot(unsigned int aSlot)
{
	myContext->PSSetShaderResources(aSlot, 1, &myShaderResource);
}
