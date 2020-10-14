#include "CRenderManager.h"
#include "CScene.h"
#include <d3d11.h>
#include "CDirectX11Framework.h"
#include "CWindowHandler.h"
CRenderManager::CRenderManager(CScene& aScene):myScene(aScene)
{
}

CRenderManager::~CRenderManager()
{
}

bool CRenderManager::Init(CDirectX11Framework* aFramework, CWindowHandler* aWindowHandler)
{
    myForwardRenderer.Init(aFramework);
    myFullscreenRenderer.Init(aFramework);
    myFullscreenRenderer.Init(aFramework);

    ID3D11Texture2D*backbufferTexture=aFramework->get

    return false;
}

void CRenderManager::Render()
{
}
