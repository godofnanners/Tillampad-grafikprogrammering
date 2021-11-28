#include "CFullscreenRenderer.h"
#include "CDirectX11Framework.h"
#include <assert.h>
#include <d3d11.h>
#include <fstream>
CFullscreenRenderer::CFullscreenRenderer()
{
	myPixelShaders = { nullptr };
	myVertexShader = nullptr;
	myContext = nullptr;
}

CFullscreenRenderer::~CFullscreenRenderer()
{
}

bool CFullscreenRenderer::Init(CDirectX11Framework* aFramework)
{
	if (!aFramework)
	{
		assert(!"Fullscreenrenderer was inited with a null pointer as framework");
	}

	myContext = aFramework->GetContext();
	if (!myContext)
	{
		assert(!"Fullscreenrenderer was inited with a null pointer as context");
	}

	ID3D11Device* device = aFramework->GetDevice();
	HRESULT result;

	std::ifstream vsFile;
	vsFile.open("FullscreenVertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile),std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	if (FAILED(result))
	{
		assert(!"FullscreenRenderer failed to create Vertexshader");
	}
	vsFile.close();
	myVertexShader = vertexShader;
	
	std::array<std::string, FullscreenShader::FULLSCREENSHADER_COUNT>filepaths;
	filepaths[FullscreenShader::FULLSCREENSHADER_COPY] = "FullscreenPixelShader_Copy.cso";
	filepaths[FullscreenShader::FULLSCREENSHADER_LUMINANCE] = "FullscreenPixelShader_Luminance.cso";
	filepaths[FullscreenShader::FULLSCREENSHADER_GAUSSIANHORIZONTAL] = "FullscreenPixelShader_GaussianBlurHorizontal.cso";
	filepaths[FullscreenShader::FULLSCREENSHADER_GAUSSIANVERTICAL] = "FullscreenPixelShader_GaussianBlurrVertical.cso";
	filepaths[FullscreenShader::FULLSCREENSHADER_BLOOM] = "FullscreenPixelShader_Bloom.cso";
	filepaths[FullscreenShader::FULLSCREENSHADER_GAMMACORRECTION] = "FullscreenPixelShader_GammaCorrection.cso";

	for (unsigned int shaderIndex = 0; shaderIndex < FullscreenShader::FULLSCREENSHADER_COUNT; shaderIndex++)
	{
		std::ifstream psFile;
		psFile.open(filepaths[shaderIndex], std::ios::binary);
		std::string psData = { std::istreambuf_iterator<char>(psFile),std::istreambuf_iterator<char>() };
		ID3D11PixelShader* pixelShader;
		result = device->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
		if (FAILED(result))
		{
			assert(!"FullscreenRenderer failed to create Pixelshader");
		}
		psFile.close();
		myPixelShaders[shaderIndex] = pixelShader;
	}

	return true;
}

void CFullscreenRenderer::Render(FullscreenShader aEffect)
{
	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	myContext->IASetInputLayout(nullptr);
	myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	myContext->GSSetShader(nullptr, nullptr, 0);
	myContext->VSSetShader(myVertexShader, nullptr, 0);
	myContext->PSSetShader(myPixelShaders[aEffect], nullptr, 0);

	myContext->Draw(3, 0);
}
