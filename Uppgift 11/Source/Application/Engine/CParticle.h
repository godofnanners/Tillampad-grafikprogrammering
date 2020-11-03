#pragma once
#include "Vector2.h"
#include "Vector4.hpp"
#include "GrowingArray.h"
#include <d3d11.h>

class CParticle
{
public:
	struct SParticleVertex
	{
		float myLifetime;
		CommonUtilities::Vector4<float>myPosition;
		CommonUtilities::Vector4<float>myMovement;
		CommonUtilities::Vector4<float>myColor;
		CommonUtilities::Vector2<float>mySize;
		float myDistanceToCamera;
	};
	struct SParticleData
	{
		unsigned int myNumberOfParticles = 0;
		unsigned int myStride = 0;
		unsigned int myOffset = 0;
		ID3D11Buffer* myPartcleVertexBuffer = nullptr;
		ID3D11VertexShader* myVertexShader = nullptr;
		ID3D11GeometryShader* myGeometryShader = nullptr;
		ID3D11PixelShader* myPixelShader = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
		ID3D11InputLayout* myInputLayout = nullptr;
		ID3D11ShaderResourceView* myTexture = nullptr;

		float mySpawnRate = 0.0f;
		float mySpawnAngle = 0.0f;
		float myParticleLifetime = 0.0f;
		float myParticleSpeed = 0.0f;
		CommonUtilities::Vector4<float>myParticleStartColor = { 0.0f,0.0f,0.0f,0.0f };
		CommonUtilities::Vector4<float>myParticleEndColor = { 0.0f,0.0f,0.0f,0.0f };
		float myParticleStartSize = 0.0f;
		float myParticleEndSize = 0.0f;
	};
public:
	CParticle();
	~CParticle();

	void Init(const SParticleData& aParticleData);

	SParticleData GetParticleData();
private:
	SParticleData myParticleData;

};

