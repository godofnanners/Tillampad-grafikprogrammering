#pragma once
#include <vector>
#include "GrowingArray.h"
class CModelInstance;
class CCamera;
class CScene
{
public:
	CScene(const CScene&) = delete;
	static CScene& GetInstance();
	bool AddInstance(CModelInstance* aModelInstance);
	bool AddInstance(CCamera* aCameraInstance);
	std::vector<CModelInstance*> CullModels(CCamera* aCamera);
	CCamera *GetMainCamera();
	void SetMainCamera(CCamera* aCamera);
private:
	CScene();
	std::vector<CModelInstance*>myModels;
	CommonUtilities::GrowingArray<CCamera*>myCameras;
	CCamera* myMainCamera;
	static CScene myInstance;
};

