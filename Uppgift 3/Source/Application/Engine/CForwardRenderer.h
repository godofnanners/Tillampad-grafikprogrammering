#pragma once
#include <vector>
class CDirectX11Framework;
class CModelInstance;
class CCamera;
struct ID3D11DeviceContext;
class CForwardRenderer
{
public:
	CForwardRenderer();
	~CForwardRenderer();

	bool Init(CDirectX11Framework* aFramework);
	void Render(std::vector<CModelInstance*>& aModelList, CCamera* aMainCamera);
private:
	ID3D11DeviceContext* myContext;
};

