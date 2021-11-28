#pragma once
#include <vector>
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4x4.hpp"
class CCamera;
class CParticleInstance;
class ID3D11DeviceContext;
class ID3D11Buffer;
class CDirectX11Framework;
class CParticleRenderer
{
public:
	bool Init(CDirectX11Framework* aFramework);
	void Render(CCamera* aCamera, std::vector<CParticleInstance*>& aParticleList);
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

