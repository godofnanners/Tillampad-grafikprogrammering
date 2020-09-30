#pragma once
#include "GrowingArray.h"
class CCamera;
class CWindowHandler;
class CCameraFactory
{
public:
	CCameraFactory(const CCameraFactory&) = delete;
	static CCameraFactory& GetInstance();
	CCamera* CreateCamera(float aFoV);
	bool Init(CWindowHandler* aWindowHandler);
private:
	CCameraFactory();
	static CCameraFactory myInstance;
	CWindowHandler* myWindowHandler;
	CommonUtilities::GrowingArray<CCamera*> myCameras;
};

