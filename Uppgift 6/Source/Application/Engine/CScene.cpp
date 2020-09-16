#include "CScene.h"
#include "CModelInstance.h"

CScene CScene::myInstance;

CScene& CScene::GetInstance()
{
    return myInstance;
}

bool CScene::AddInstance(CModelInstance* aModelInstance)
{
    myModels.push_back(aModelInstance);
    return true;
}

bool CScene::AddInstance(CCamera* aCameraInstance)
{
    myCameras.Add(aCameraInstance);
    return true;
}

std::vector<CModelInstance*> CScene::CullModels(CCamera* aCamera)
{
    //TODO Cull With main camera
    return myModels;
}

CCamera* CScene::GetMainCamera()
{
    return myMainCamera;
}

void CScene::SetMainCamera(CCamera* aCamera)
{
    myMainCamera = aCamera;
}

CScene::CScene()
{
    myMainCamera = nullptr;
}
