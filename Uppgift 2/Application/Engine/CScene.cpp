#include "CScene.h"
#include "CModelInstance.h"

CScene CScene::myInstance;

CScene& CScene::GetInstance()
{
    // TODO: insert return statement here
    return myInstance;
}

bool CScene::AddInstance(CModelInstance* aModelInstance)
{
    myModels.push_back(aModelInstance);
    return true;
}

std::vector<CModelInstance*> CScene::CullModels()
{
    return myModels;
}

CScene::CScene()
{
}
