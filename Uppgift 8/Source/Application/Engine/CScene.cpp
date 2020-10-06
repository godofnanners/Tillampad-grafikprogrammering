#include "CScene.h"
#include "CModelInstance.h"
#include "CCamera.h"

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

bool CScene::AddInstance(CEnvironmentLight* anEnvironmentLight)
{
    myEnvironmentLight = anEnvironmentLight;
    return true;
}

CEnvironmentLight* CScene::GetEnvironmentLight()
{
    return myEnvironmentLight;
}

std::vector<CModelInstance*> CScene::CullModels(CCamera* aCamera)
{
    //TODO Cull With main camera
    aCamera->GetTransform();
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
    myEnvironmentLight = nullptr;
}
