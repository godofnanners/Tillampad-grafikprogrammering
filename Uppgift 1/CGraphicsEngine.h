#pragma once
#include "CWindowHandler.h"
#include "CDirectX11Framework.h"
class CGraphicsEngine
{
public:
	CGraphicsEngine();
	~CGraphicsEngine();
	bool Init(CWindowHandler::SWindowData aWindowData);
	void BeginFrame();
	void EndFrame();
private:
	CWindowHandler myWindowHandler;
	CDirectX11Framework myFramework;
};

