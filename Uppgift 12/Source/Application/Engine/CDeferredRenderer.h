#pragma once
#include "CCamera.h"
#include "CEnvironmentLight.h"
#include "CModelInstance.h"
#include <vector>
#include "CPointLight.h"
#include <d3d11.h>

class CDirectX11Framework;

class CDeferredRenderer
{
public:
	CDeferredRenderer() = default;
	~CDeferredRenderer() = default;

	bool Init(CDirectX11Framework& aFramework);

	void Render(CCamera* aMainCamera, CEnvironmentLight *aEnvironmentLight);
	void Render(CCamera* aMainCamera, std::vector<CPointLight*>& aPointLightList);
	void GenerateGBuffer(CCamera* aMainCamera, std::vector<CModelInstance*>aModelList);
private:
	ID3D11VertexShader* myFullscreenShader;
	ID3D11PixelShader* myEnvironmentLightShader;
	ID3D11PixelShader* myPointLightShader;
	struct FrameBufferData
	{
		CommonUtilities::Matrix4x4<float> myToCamera;
		CommonUtilities::Matrix4x4<float> myToProjection;
		CommonUtilities::Vector4<float> myCameraPosition;

	} myFrameBufferData;

	struct ObjectBufferData
	{
		CommonUtilities::Matrix4x4<float> myToWorld;
	}myObjectBufferData;

	struct EnvironmentLightBufferData
	{
		CommonUtilities::Vector4<float> myToDirectionalLight;
		CommonUtilities::Vector4<float> myDirectionalLightColor;
	}myEnviromentLightBufferData;

	struct PointLightBufferData
	{
		CommonUtilities::Vector3<float> myPosition;
		float myRange;
		CommonUtilities::Vector3<float> myColor;
		float myIntensity;
	}myPointLightBufferData;

	ID3D11DeviceContext* myContext;;
	ID3D11Device* myDevice;
	ID3D11Buffer* myFrameBuffer;
	ID3D11Buffer* myEnvironmentLightBuffer;
	ID3D11Buffer* myPointLightBuffer;
	ID3D11Buffer* myObjectBuffer;
	ID3D11PixelShader* myGBufferPixelShader;
};

