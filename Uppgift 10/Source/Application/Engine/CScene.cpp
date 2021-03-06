#include "CScene.h"
#include "CModelInstance.h"
#include "CCamera.h"
#include "CPointLight.h"

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

bool CScene::AddInstance(CPointLight* aPointLight)
{
	myPointLights.Add(aPointLight);
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

CommonUtilities::VectorOnStack<CPointLight*, 8> CScene::CullLights(CModelInstance* aModelInstance)
{
	//TODO Cull With main camera
	CommonUtilities::Vector3<float> pos = aModelInstance->GetTransform().GetPosition();
	CommonUtilities::VectorOnStack<CPointLight*, 8> lightsAffectingModelInstance;
	for (unsigned short lightIndex = 0; lightIndex < myPointLights.Size(); lightIndex++)
	{
		//if ( (pos-myPointLights[lightIndex]->GetPosition()).Length()< myPointLights[lightIndex]->GetRange())
		//{
			lightsAffectingModelInstance.Add(myPointLights[lightIndex]);
			
			if (lightsAffectingModelInstance.Size()> 7)
			{
				break;
			}
		//}
	}

	return lightsAffectingModelInstance;
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
