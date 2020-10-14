#pragma once
#include "CForwardRenderer.h"
#include "CFullscreenRenderer.h"
#include "CFullscreenTexture.h"
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
	CForwardRenderer myForwardRenderer;
	CFullscreenRenderer myFullscreenRenderer;

	CFullscreenTexture myBackBuffer;
	CFullscreenTexture myIntermediateDepth;
};

