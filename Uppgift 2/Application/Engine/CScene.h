#pragma once
#include <vector>
class CModelInstance;
class CScene
{
public:
	CScene(const CScene&) = delete;
	static CScene& GetInstance();
	bool AddInstance(CModelInstance* aModelInstance);
	std::vector<CModelInstance*> CullModels();
private:
	CScene();
	std::vector<CModelInstance*>myModels;
	static CScene myInstance;
};

