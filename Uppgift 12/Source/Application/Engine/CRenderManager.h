#pragma once
#include "CForwardRenderer.h"
#include "CFullscreenRenderer.h"
#include "CFullscreenTexture.h"
#include "CParticleRenderer.h"
#include "CRenderStateManager.h"
#include "CGBuffer.h"
#include "CDeferredRenderer.h"
class CScene;
class CDirectX11Framework;
class CWindowHandler;

class CRenderManager
{
public:
	CRenderManager(CScene& aScene);
	~CRenderManager();

	bool Init(CDirectX11Framework* aFramework, CWindowHandler* aWindowHandler);

	void Render();
private:
	CScene& myScene;
	CGBuffer myGBuffer;
	CDeferredRenderer myDeferredRenderer;
	CForwardRenderer myForwardRenderer;
	CFullscreenRenderer myFullscreenRenderer;
	CParticleRenderer myParticleRenderer;
	CRenderStateManager myRenderStateManager;

	CFullscreenTexture myLuminanceTexture;
	CFullscreenTexture myHalfsizeTexture;
	CFullscreenTexture myQuartersizeTexture;
	CFullscreenTexture myBlurTexture1;
	CFullscreenTexture myBlurTexture2;

	CFullscreenTexture myBackBuffer;
	CFullscreenTexture myIntermediateTexture;
	CFullscreenTexture myIntermediateDepth;
	CFullscreenTexture myFullscreenDeferredTexture;
};

