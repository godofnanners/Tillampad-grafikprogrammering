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
		unsigned int myEnvironmentLightMipCount;
		unsigned int trash[3];
	} myFrameBufferData;

	struct ObjectBufferData
	{
		CommonUtilities::Matrix4x4<float>myToWorld;
		struct SpointLightBufferData
		{
			CommonUtilities::Vector4<float>myPosition;
			CommonUtilities::Vector3<float> myColor;
			float myRange;
			float myIntensity;
			CommonUtilities::Vector3<float>myTrash;
		}myPointLights[8];
		unsigned int myNumberOfUsedPointLights;
		unsigned int myTrash[3];
	} myObjectBufferData;

	ID3D11Buffer* myFrameBuffer;
	ID3D11Buffer* myObjectBuffer;
	ID3D11DeviceContext* myContext;
};

