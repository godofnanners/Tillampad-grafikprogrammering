#pragma once
#include "Vector2.h"

class CDirectX11Framework;
class CFullscreenTexture;
class CGBuffer;
struct ID3D11Texture2D;
enum DXGI_FORMAT;

class CFullscreenTextureFactory
{
public:
	~CFullscreenTextureFactory();
	CFullscreenTextureFactory(const CFullscreenTextureFactory&) = delete;
	static CFullscreenTextureFactory& GetInstance();
	bool Init(CDirectX11Framework* aFramework);

	CFullscreenTexture CreateTexture(CommonUtilities::Vector2<float> aSize, DXGI_FORMAT aFormat);
	CFullscreenTexture CreateTexture(ID3D11Texture2D* aTexture);
	CFullscreenTexture CreateDepth(CommonUtilities::Vector2<float> aSize, DXGI_FORMAT aFormat);
private:
	CFullscreenTextureFactory();
	CDirectX11Framework* myFramework;
	static CFullscreenTextureFactory myInstance;
};

