#pragma once
#include <vector>
#include "Matrix4x4.hpp"
#include "Vector4.hpp"
#include "VectorOnStack.h"
#include "GrowingArray.h"
class CDirectX11Framework;
class CModelInstance;
class CCamera;
class CEnvironmentLight;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
class CPointLight;
class CForwardRenderer
{
public:
	CForwardRenderer();
	~CForwardRenderer();

	bool Init(CDirectX11Framework* aFramework);
	void Render(std::vector<CModelInstance*>& aModelList, CCamera* aCamera, const CommonUtilities::GrowingArray<CommonUtilities::VectorOnStack<CPointLight*, 8>>& aPointLightList, CEnvironmentLight* anEnvironmentLight);
private:
	struct FrameBufferData
	{
		CommonUtilities::Matrix4x4<float>myToCamera;
		CommonUtilities::Matrix4x4<float>myToProjection;
		CommonUtilities::Vector4<float>myCameraPosition;
		CommonUtilities::Vector4<float>myDirectionalLightDirection;
		CommonUtilities::Vector4<float>myDirectionalLightColor;
		unsigned int myEnvironmentLightMipCount = 0;
		unsigned int trash[3] = { 0,0,0 };
	} myFrameBufferData;

	struct ObjectBufferData
	{
		CommonUtilities::Matrix4x4<float>myToWorld;
		struct SPointLight
		{
			CommonUtilities::Vector4<float>myPosition = { 0,0,0,0 };
			CommonUtilities::Vector3<float> myColor = { 0,0,0 };
			float myRange = 0;
			float myIntensity = 0;
			CommonUtilities::Vector3<float>myTrash = { 0,0,0 };
		}myPointLights[8];
		unsigned int myNumberOfUsedPointLights = 0;
		unsigned int myTrash[3] = { 0,0,0 };
	} myObjectBufferData;

	ID3D11Buffer* myFrameBuffer;
	ID3D11Buffer* myObjectBuffer;
	ID3D11DeviceContext* myContext;
};

