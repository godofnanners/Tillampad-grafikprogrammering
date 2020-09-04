#pragma once
#include <vector>
class CDirectX11Framework;
class CModelInstance;
struct ID3D11DeviceContext;
class CForwardRenderer
{
public:
	CForwardRenderer();
	~CForwardRenderer();

	bool Init(CDirectX11Framework* aFramework);
	void Render(std::vector<CModelInstance*>& aModelList);
private:
	ID3D11DeviceContext* myContext;
};

