#include "CRenderManager.h"
#include "CScene.h"
#include <d3d11.h>
#include "CDirectX11Framework.h"
#include "CWindowHandler.h"
#include "CFullscreenTextureFactory.h"
#include "CParticleInstance.h"

CRenderManager::CRenderManager(CScene& aScene) :myScene(aScene)
{
}

CRenderManager::~CRenderManager()
{
}

bool CRenderManager::Init(CDirectX11Framework* aFramework, CWindowHandler* aWindowHandler)
{
	if (!myForwardRenderer.Init(aFramework))
		return false;
	if (!myFullscreenRenderer.Init(aFramework))
		return false;
	if (!myParticleRenderer.Init(aFramework))
		return false;
	if (!myRenderStateManager.Init(aFramework))
		return false;
	if (!myGBuffer.Init(*aFramework, { static_cast<float>(aWindowHandler->GetWidth()),static_cast<float>(aWindowHandler->GetHeight()) }))
		return false;
	if (!myDeferredRenderer.Init(*aFramework))
		return false;


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
	myFullscreenDeferredTexture = CFullscreenTextureFactory::GetInstance().CreateTexture({ (float)aWindowHandler->GetWidth(),(float)aWindowHandler->GetWidth() }, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);

	return false;
}

void CRenderManager::Render()
{
	myRenderStateManager.SetAllDefault();
	myBackBuffer.ClearTexture();
	myIntermediateTexture.ClearTexture();
	myIntermediateDepth.ClearDepth();
	myFullscreenDeferredTexture.ClearTexture();
	myGBuffer.ClearTextures();

	myIntermediateTexture.SetAsActiveTarget(&myIntermediateDepth);
	
	CEnvironmentLight* environmentlight = myScene.GetEnvironmentLight();
	std::vector<CPointLight*>pointlights = myScene.GetPointLights();
	CCamera* mainCamera = myScene.GetMainCamera();
	std::vector<CModelInstance*>modelsToRender = myScene.CullModels(mainCamera);
	myGBuffer.SetViewport(myIntermediateTexture.GetViewPort());
	myGBuffer.SetAsActiveTarget(&myIntermediateDepth);
	myDeferredRenderer.GenerateGBuffer(mainCamera, modelsToRender);
	myFullscreenDeferredTexture.SetAsActiveTarget();
	myGBuffer.SetAllAsResources();
	myRenderStateManager.SetBlendStates(CRenderStateManager::BlendStates::BLENDSTATE_ADDITATIVEBLEND);
	myDeferredRenderer.Render(mainCamera, environmentlight);
	myDeferredRenderer.Render(mainCamera, pointlights);
	//ForwardRendering
	//CommonUtilities::GrowingArray<CommonUtilities::VectorOnStack<CPointLight*, 8>> pointlights;
	//for (CModelInstance* instance : modelsToRender)
	//{
	//	pointlights.Add(myScene.CullLights(instance));
	//}
	//myForwardRenderer.Render(modelsToRender, mainCamera, pointlights, environmentlight);

	/*myRenderStateManager.SetBlendStates(CRenderStateManager::BlendStates::BLENDSTATE_ALPHABLEND);
	myRenderStateManager.SetDepthStencilState(CRenderStateManager::DepthStencilStates::DEPTHSTENCILSTATE_ONLYREAD);
	std::vector<CParticleInstance*>particlesToRender = myScene.CullParticles(mainCamera);
	myParticleRenderer.Render(mainCamera, particlesToRender);
	myRenderStateManager.SetBlendStates(CRenderStateManager::BlendStates::BLENDSTATE_DISABLE);
	myRenderStateManager.SetDepthStencilState(CRenderStateManager::DepthStencilStates::DEPTHSTENCILSTATE_DEFAULT);

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
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_BLOOM);*/

	myRenderStateManager.SetBlendStates(CRenderStateManager::BlendStates::BLENDSTATE_DISABLE);
	myIntermediateTexture.SetAsActiveTarget();
	myFullscreenDeferredTexture.SetAsResourceOnSlot(0);
	myFullscreenRenderer.Render(CFullscreenRenderer::FullscreenShader::FULLSCREENSHADER_GAMMACORRECTION);

	myRenderStateManager.SetBlendStates(CRenderStateManager::BlendStates::BLENDSTATE_ALPHABLEND);
	myIntermediateTexture.SetAsActiveTarget(&myIntermediateDepth);

	myLuminanceTexture.SetAsActiveTarget();
	myIntermediateTexture.SetAsResourceOnSlot(0);
	/*std::vector<std::pair<unsigned int, std::array<PointLight*, 8>>> pointLights;
	for (ModelInstance* instance : modelsToRender)
	{
		pointLights.push_back(myScene->CullLights(instance));
	}*/
	//myForwardRenderer.Render(environmentLight, pointLights, mainCamera, modelsToRender);

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
