#include "CRenderManager.h"
#include "CScene.h"
#include <d3d11.h>
#include "CDirectX11Framework.h"
#include "CWindowHandler.h"
#include "CFullscreenTextureFactory.h"
CRenderManager::CRenderManager(CScene& aScene) :myScene(aScene)
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

	ID3D11Texture2D* backbufferTexture = aFramework->GetBackbufferTexture();
	if (!backbufferTexture)
	{
		assert("Backbuffer was nullptr, location RenderManager");
	}

	myBackBuffer = CFullscreenTextureFactory::GetInstance().CreateTexture(backbufferTexture);
	myIntermediateDepth = CFullscreenTextureFactory::GetInstance().CreateDepth({ aWindowHandler->GetWidth(),aWindowHandler->GetWidth() }, DXGI_FORMAT_D32_FLOAT);

	return false;
}

void CRenderManager::Render()
{
	myBackBuffer.ClearTexture();
	myIntermediateTexture.ClearTexture();
	myIntermediateDepth.ClearDepth();

	myBackBuffer.SetAsActiveTarget(&myIntermediateDepth);

	CEnvironmentLight* environmentlight = myScene.GetEnvironmentLight();
	CCamera* mainCamera = myScene.GetMainCamera();
	std::vector<CModelInstance*>modelsToRender = myScene.CullModels(mainCamera);
	CommonUtilities::GrowingArray<CommonUtilities::VectorOnStack<CPointLight*, 8>> pointlights;
	for (CModelInstance* instance : modelsToRender)
	{
		pointlights.Add(myScene.CullLights(instance));
	}
	myForwardRenderer.Render(modelsToRender, mainCamera, pointlights, environmentlight);

	myBackBuffer.SetAsActiveTarget();
	myIntermediateTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);
}
