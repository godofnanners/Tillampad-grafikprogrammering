#include "Engine.h"
#include <array>
#include "CDirectX11Framework.h"
#include <vector>
#include "CModelInstance.h"
#include "CScene.h"
#include "CModelFactory.h"
#include "CCameraFactory.h"
#include "CCamera.h"
#include "CLightFactory.h"
#include "VectorOnStack.h"
#include "CFullscreenTextureFactory.h"
Engine::Engine():myScene(CScene::GetInstance())
{
	myFramework = nullptr;
	myWindowHandler = CWindowHandler();
}
Engine::~Engine()
{
	delete myFramework;
	myFramework = nullptr;
}
bool Engine::Init(CWindowHandler::SWindowData aWindowData)
{
	if (!myWindowHandler.Init(aWindowData))
	{
		return false;
	}

	myFramework = new CDirectX11Framework();
	CFullscreenTextureFactory::GetInstance().Init(myFramework);//very important that this gets initiated before framework
	if (!myFramework->Init(&myWindowHandler))
	{
		return false;
	}

	myForwardrenderer.Init(myFramework);
	CCameraFactory::GetInstance().Init(&myWindowHandler);
	CModelFactory::GetInstance().Init(myFramework->GetDevice());
	CLightFactory::GetInstance().Init(myFramework->GetDevice());
	return true;
}

void Engine::BeginFrame()
{
	const std::array<float, 4>clearcolor = { .25f,.5f,1,1 };
	myFramework->BeginFrame(clearcolor);
}

void Engine::RenderFrame()
{
	CEnvironmentLight* environmentlight = myScene.GetEnvironmentLight();
	CCamera* mainCamera = myScene.GetMainCamera();
	std::vector<CModelInstance*>modelsToRender = myScene.CullModels(mainCamera);
	CommonUtilities::GrowingArray<CommonUtilities::VectorOnStack<CPointLight*, 8>>pointlights;
	for (CModelInstance*instance:modelsToRender)
	{
		CommonUtilities::VectorOnStack<CPointLight*, 8> lightsOninstance=myScene.CullLights(instance);
		if (lightsOninstance.Size()>0)
		{
			pointlights.Add(lightsOninstance);
		}
	}
	myForwardrenderer.Render(modelsToRender,mainCamera,pointlights,environmentlight);
}

void Engine::EndFrame()
{
	myFramework->EndFrame();
}
