#pragma once
#include <vector>
#include "Matrix4x4.hpp"
class CDirectX11Framework;
class CModelInstance;
class CCamera;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
class CForwardRenderer
{
public:
	CForwardRenderer();
	~CForwardRenderer();

	bool Init(CDirectX11Framework* aFramework);
	void Render(std::vector<CModelInstance*>& aModelList, CCamera* aMainCamera);
private:
	struct FrameBufferData
	{
		CommonUtilities::Matrix4x4<float>myToCamera;
		CommonUtilities::Matrix4x4<float>myToProjection;
	} myFrameBufferData;

	struct ObjectBufferData
	{
		CommonUtilities::Matrix4x4<float>myToWorld;
	} myObjectBufferData;

	ID3D11Buffer* myFrameBuffer;
	ID3D11Buffer* myObjectBuffer;
	ID3D11DeviceContext* myContext;
};

