#pragma once
#include <array>
class CDirectX11Framework;
class ID3D11DeviceContext;
class ID3D11VertexShader;
class ID3D11PixelShader;

class CFullscreenRenderer
{
public:
	enum FullscreenShader
	{
		FULLSCREENSHADER_COPY,
		FULLSCREENSHADER_LUMINANCE,
		FULLSCREENSHADER_GAUSSIANHORIZONTAL,
		FULLSCREENSHADER_GAUSSIANVERTICAL,
		FULLSCREENSHADER_BLOOM,
		FULLSCREENSHADER_GAMMACORRECTION,
		FULLSCREENSHADER_COUNT
	};
public:
	CFullscreenRenderer();
	~CFullscreenRenderer();

	bool Init(CDirectX11Framework* aFramework);

	void Render(FullscreenShader aEffect);

private:
	ID3D11DeviceContext* myContext;
	ID3D11VertexShader* myVertexShader;
	std::array<ID3D11PixelShader*, FullscreenShader::FULLSCREENSHADER_COUNT>myPixelShaders;
};

