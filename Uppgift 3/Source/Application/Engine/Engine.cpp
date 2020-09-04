#include "Engine.h"
#include <array>
#include "CDirectX11Framework.h"
#include <vector>
#include "CModelInstance.h"
#include "CScene.h"
#include "CModelFactory.h"
Engine::Engine()/*:myScene(CScene::GetInstance())*/
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
	
	CModelFactory::GetInstance().Init(myFramework->GetDevice());
	
	return true;
}

void Engine::BeginFrame()
{
	const std::array<float, 4>clearcolor = { .25f,.5f,1,1 };
	myFramework->BeginFrame(clearcolor);
}

void Engine::RenderFrame()
{
	std::vector<CModelInstance*>modelsToRender = CScene::GetInstance().CullModels();
	myForwardrenderer.Render(modelsToRender);
}

void Engine::EndFrame()
{
	myFramework->EndFrame();
}
