#pragma once
#include <vector>
class CDirectX11Framework;
class CModelInstance;
class CForwardRenderer
{
public:
	CForwardRenderer();
	~CForwardRenderer();

	bool Init(CDirectX11Framework* aFramework);
	void Render(std::vector<CModelInstance*>& aModelList);
};

