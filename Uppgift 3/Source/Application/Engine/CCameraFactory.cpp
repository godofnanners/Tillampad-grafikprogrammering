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
	camera->Init(aFoV, CommonUtilities::Vector2<float>(width, height));
	myCameras.Add(camera);
	return nullptr;
}

bool CCameraFactory::Init(CWindowHandler* aWindowHandler)
{
	if (!aWindowHandler)
	{
		return false;
	}
	myWindowHandler = aWindowHandler;
	return true;
}
