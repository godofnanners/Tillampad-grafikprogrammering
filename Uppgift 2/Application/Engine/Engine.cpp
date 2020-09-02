#include "Engine.h"
#include <array>
#include "CDirectX11Framework.h"
#include <vector>
#include "CModelInstance.h"
Engine::Engine()
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
	return true;
}

void Engine::BeginFrame()
{
	const std::array<float, 4>clearcolor = { .25f,.5f,1,1 };
	myFramework->BeginFrame(clearcolor);
}

void Engine::RenderFrame()
{
	std::vector<CModelInstance*>modelsToRender = myScene.CullModels();
	myForwardrenderer.Render(modelsToRender);
}

void Engine::EndFrame()
{
	myFramework->EndFrame();
}
