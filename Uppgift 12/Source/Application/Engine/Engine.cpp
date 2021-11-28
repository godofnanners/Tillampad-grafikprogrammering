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
#include "CParticleFactory.h"
Engine::Engine():myScene(CScene::GetInstance())
{
	myFramework = nullptr;
	myRenderManager = nullptr;
	myWindowHandler = CWindowHandler();
}
Engine::~Engine()
{
	delete myFramework;
	myFramework = nullptr;
	delete myRenderManager;
	myRenderManager = nullptr;
}
bool Engine::Init(CWindowHandler::SWindowData aWindowData)
{
	if (!myWindowHandler.Init(aWindowData))
	{
		return false;
	}

	myFramework = new CDirectX11Framework();
	myRenderManager = new CRenderManager(myScene);
	if (!myFramework->Init(&myWindowHandler))
	{
		return false;
	}

	myRenderManager->Init(myFramework, &myWindowHandler);
	CCameraFactory::GetInstance().Init(&myWindowHandler);
	CModelFactory::GetInstance().Init(myFramework->GetDevice());
	CLightFactory::GetInstance().Init(myFramework->GetDevice());
	CParticleFactory::GetInstance().Init(myFramework);
	return true;
}

void Engine::BeginFrame()
{
	const std::array<float, 4>clearcolor = { .25f,.5f,1,1 };
	myFramework->BeginFrame(clearcolor);
}

void Engine::RenderFrame()
{
	myRenderManager->Render();
}

void Engine::EndFrame()
{
	myFramework->EndFrame();
}
