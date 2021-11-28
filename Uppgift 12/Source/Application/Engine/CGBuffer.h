#pragma once
#include "CFullscreenTextureFactory.h"
#include "..\CommonUtilities\Vector4.hpp"
#include <array>
class ID3D11DeviceContext;
class ID3D11RenderTargetView;
class ID3D11ShaderResourceView;
class D3D11_VIEWPORT;
class CGBuffer
{
public:
	friend CFullscreenTextureFactory;

	enum GBufferTextures
	{
		GBUFFERTEXTURE_POSITION,
		GBUFFERTEXTURE_ALBEDO,
		GBUFFERTEXTURE_NORMAL,
		GBUFFERTEXTURE_VERTEXNORMAL,
		GBUFFERTEXTURE_METALNESS,
		GBUFFERTEXTURE_ROUGHNESS,
		GBUFFERTEXTURE_AMBIENTOCCLUSION,
		GBUFFERTEXTURE_EMISSIVEM,
		GBUFFERTEXTURE_COUNT
	};
	CGBuffer();
	~CGBuffer();
	bool Init(CDirectX11Framework& aFranework,CommonUtilities::Vector2<float> aScreensize);
	void SetViewport(D3D11_VIEWPORT* aViewport);
	void ClearTextures(CommonUtilities::Vector4<float> aClearColor = CommonUtilities::Vector4<float>(0.0f, 0.0f, 0.0f, 0.0f));
	void SetAsActiveTarget(CFullscreenTexture* aDepth = nullptr);
	void SetAsResourceOnSlot(GBufferTextures aResource, unsigned int aSlot);
	void SetAllAsResources();
private:
	ID3D11DeviceContext* myContext;
	std::array<ID3D11Texture2D*, GBUFFERTEXTURE_COUNT>myTextures;
	std::array<ID3D11RenderTargetView*, GBUFFERTEXTURE_COUNT>myRenderTargets;
	std::array<ID3D11ShaderResourceView*, GBUFFERTEXTURE_COUNT>myShaderResources;
	D3D11_VIEWPORT* myViewport;
};

