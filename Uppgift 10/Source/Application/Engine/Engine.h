#pragma once
#include "CWindowHandler.h"
#include "CScene.h"
#include "CRenderManager.h"
class CDirectX11Framework;
class Engine
{
public:
	Engine();
	~Engine();
	bool Init(CWindowHandler::SWindowData aWindowData);
	void BeginFrame();
	void RenderFrame();
	void EndFrame();
private:
	CWindowHandler myWindowHandler;
	CDirectX11Framework* myFramework;
	CRenderManager* myRenderManager;
	CScene& myScene;
};

