#pragma once
#include <vector>
#include "GrowingArray.h"
#include "VectorOnStack.h"
class CModelInstance;
class CCamera;
class CEnvironmentLight;
class CPointLight;
class CParticleInstance;
class CScene
{
public:
	CScene(const CScene&) = delete;
	static CScene& GetInstance();
	bool AddInstance(CModelInstance* aModelInstance);
	bool AddInstance(CCamera* aCameraInstance);
	bool AddInstance(CEnvironmentLight* anEnvironmentLight);
	bool AddInstance(CPointLight* anEnvironmentLight);
	bool AddInstance(CParticleInstance* aParticleInstance);
	CEnvironmentLight* GetEnvironmentLight();
	std::vector<CPointLight*> GetPointLights();
	std::vector<CModelInstance*> CullModels(CCamera* aCamera);
	CommonUtilities::VectorOnStack<CPointLight*,8> CullLights(CModelInstance* aModelInstance);
	std::vector<CParticleInstance*>CullParticles(CCamera* aCamera);
	CCamera *GetMainCamera();
	void SetMainCamera(CCamera* aCamera);
private:
	CScene();
	std::vector<CModelInstance*>myModels;
	CommonUtilities::GrowingArray<CCamera*>myCameras;
	CEnvironmentLight* myEnvironmentLight;
	std::vector<CPointLight*>myPointLights;
	std::vector<CParticleInstance*> myParticles;
	CCamera* myMainCamera;
	static CScene myInstance;
};

