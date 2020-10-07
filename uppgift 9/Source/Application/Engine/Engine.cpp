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
	CommonUtilities::GrowingArray<std::pair<unsigned int, std::array<CPointLight*, 8>>>pointlights;
	for (CModelInstance*instance:modelsToRender)
	{
		pointlights.Add(myScene.CullLights(instance))
	}
	myForwardrenderer.Render(modelsToRender,mainCamera,pointlights,environmentlight);
}

void Engine::EndFrame()
{
	myFramework->EndFrame();
}
