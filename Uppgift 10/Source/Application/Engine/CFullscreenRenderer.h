#pragma once
#include <array>
#include "Macro.h"
class CDirectX11Framework;
struct ID3D11DeviceContext;
struct ID3D11VertexShader;
struct ID3D11PixelShader;

class CFullscreenRenderer
{
public:
	enum class FullscreenShader
	{
		FULLSCREENSHADER_COPY,
		FULLSCREENSHADER_LUMINANCE,
		FULLSCREENSHADER_GAUSSIANHORIZONTAL,
		FULLSCREENSHADER_GAUSSIANVERTICAL,
		FULLSCREENSHADER_BLOOM,
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
	std::array<ID3D11PixelShader*, SC_INT(FullscreenShader::FULLSCREENSHADER_COUNT)>myPixelShaders;
};

