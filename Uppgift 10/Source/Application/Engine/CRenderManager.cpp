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
	CFullscreenTextureFactory::GetInstance().Init(aFramework);

	ID3D11Texture2D* backbufferTexture = aFramework->GetBackbufferTexture();
	if (!backbufferTexture)
	{
		assert("Backbuffer was nullptr, location RenderManager");
	}

	myBackBuffer = CFullscreenTextureFactory::GetInstance().CreateTexture(backbufferTexture);
	myIntermediateDepth = CFullscreenTextureFactory::GetInstance().CreateDepth({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT_D32_FLOAT);
	myIntermediateTexture = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT_R8G8B8A8_UNORM);
	myLuminanceTexture = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT_R32G32B32A32_FLOAT);
	myHalfsizeTexture = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth() * 0.5f,(float)aWindowHandler->GetWidth() * 0.5f }, DXGI_FORMAT_R32G32B32A32_FLOAT);
	myQuartersizeTexture = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth() * 0.25f,(float)aWindowHandler->GetWidth() * 0.25f }, DXGI_FORMAT_R32G32B32A32_FLOAT);
	myBlurTexture1 = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT_R32G32B32A32_FLOAT);
	myBlurTexture2 = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT_R32G32B32A32_FLOAT);
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

	myLuminanceTexture.SetAsActiveTarget();
	myIntermediateTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_LUMINANCE);

	myHalfsizeTexture.SetAsActiveTarget();
	myLuminanceTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);

	myQuartersizeTexture.SetAsActiveTarget();
	myHalfsizeTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);

	myBlurTexture1.SetAsActiveTarget();
	myQuartersizeTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);

	myBlurTexture2.SetAsActiveTarget();
	myBlurTexture1.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_GAUSSIANHORIZONTAL);

	myBlurTexture1.SetAsActiveTarget();
	myBlurTexture2.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_GAUSSIANVERTICAL);

	myBlurTexture2.SetAsActiveTarget();
	myBlurTexture1.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_GAUSSIANHORIZONTAL);

	myBlurTexture1.SetAsActiveTarget();
	myBlurTexture2.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_GAUSSIANVERTICAL);

	myQuartersizeTexture.SetAsActiveTarget();
	myBlurTexture1.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);

	myHalfsizeTexture.SetAsActiveTarget();
	myQuartersizeTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_COPY);

	myBackBuffer.SetAsActiveTarget();
	myIntermediateTexture.SetAsResourceOnSlot(0);
	myHalfsizeTexture.SetAsResourceOnSlot(1);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_BLOOM);

}
