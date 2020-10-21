#pragma once
#include "Vector2.h"
#include "Vector4.hpp"
#include <d3d11.h>
class ID3D11Buffer;
class CParticle
{
	struct SParticleVertex
	{
		float myLifetime;
		CommonUtilities::Vector4<float>myPosition;
		CommonUtilities::Vector4<float>myPosition;
		CommonUtilities::Vector4<float>myPosition;
		CommonUtilities::Vector2<float>myPosition;
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
		D3D11_PRIMITIVE_TOPOLOGY myPrimitiveTopology;
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
};

