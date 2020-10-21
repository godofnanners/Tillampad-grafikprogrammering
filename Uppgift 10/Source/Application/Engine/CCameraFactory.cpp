#include "CCameraFactory.h"
#include "CCamera.h"
#include "CWindowHandler.h"
#include "Vector2.h"

CCameraFactory CCameraFactory::myInstance;

CCameraFactory& CCameraFactory::GetInstance()
{
	return myInstance;
}

CCamera* CCameraFactory::CreateCamera(float aFoV)
{
	CCamera* camera = new CCamera();
	int width = myWindowHandler->GetWidth();
	int height = myWindowHandler->GetHeight();
	camera->Init(aFoV, CommonUtilities::Vector2<float>((float)width, (float)height));
	myCameras.Add(camera);
	return camera;
}

bool CCameraFactory::Init(CWindowHandler* aWindowHandler)
{
	if (!aWindowHandler)
	{
		assert(!"WindowHandler was nullptr when trying to create a camera");
	}
	myWindowHandler = aWindowHandler;
	return true;
}

CCameraFactory::CCameraFactory()
{
	myWindowHandler = nullptr;
}
