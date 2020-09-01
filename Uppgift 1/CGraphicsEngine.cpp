#include "CGraphicsEngine.h"
#include <array>
CGraphicsEngine::CGraphicsEngine()
{
}
CGraphicsEngine::~CGraphicsEngine()
{
}
bool CGraphicsEngine::Init(CWindowHandler::SWindowData aWindowData)
{
	if (!myWindowHandler.Init(aWindowData))
	{
		return false;
	}

	if (!myFramework.Init(&myWindowHandler))
	{
		return false;
	}
	return true;
}

void CGraphicsEngine::BeginFrame()
{
	const std::array<float, 4>clearcolor = { .25f,.5f,1,1 };
	myFramework.BeginFrame(clearcolor);
}

void CGraphicsEngine::EndFrame()
{
	myFramework.EndFrame();
}
