#pragma once
#include <array>
class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11BlendState;
class ID3D11RasterizerState;
class ID3D11DepthStencilState;
class ID3D11SamplerState;
class CDirectX11Framework;



class CRenderStateManager
{

public:
	enum BlendStates
	{
		BLENDSTATE_DISABLE,
		BLENDSTATE_ALPHABLEND,
		BLENDSTATE_ADDITATIVEBLEND,
		BLENDSTATE_COUNT
	};
	enum DepthStencilStates
	{
		DEPTHSTENCILSTATE_DEFAULT,
		DEPTHSTENCILSTATE_ONLYREAD,
		DEPTHSTENCILSTATE_COUNT
	};
	enum RasterizerStates
	{
		RASTERIZERSTATE_DEFAULT,
		RASTERIZERSTATE_WIREFRAME,
		RASTERIZESTATE_COUNT
	};
	enum SamplerStates
	{
		SAMPLERSTATE_TRILINEAR,
		SAMPLERSTATE_POINT,
		SAMPLERSTATE_COUNT
	};

public:
	CRenderStateManager();
	~CRenderStateManager();

	bool Init(CDirectX11Framework* aFramework);

	void SetBlendStates(BlendStates aBlendState);
	void SetDepthStencilState(DepthStencilStates aDepthStencilState);
	void SetRasterizerState(RasterizerStates aRasterizerState);
	void SetSamplerState(SamplerStates aSamplerState);
	void SetAllStates(BlendStates aBlendState, DepthStencilStates aDepthStencilState, RasterizerStates aRasterizerState, SamplerStates aSamplerState);
	void SetAllDefault();
private:
	bool CreateBlendStates(ID3D11Device* aDevice);
	bool CreateDepthStencilState(ID3D11Device* aDevice);
	bool CreateRasterizerState(ID3D11Device* aDevice);
	bool CreateSamplerState(ID3D11Device* aDevice);

	ID3D11DeviceContext* myContext;
	std::array<ID3D11BlendState*, BlendStates::BLENDSTATE_COUNT>myBlendStates;
	std::array<ID3D11DepthStencilState*, DepthStencilStates::DEPTHSTENCILSTATE_COUNT>myDepthStencilStates;
	std::array<ID3D11RasterizerState*, RasterizerStates::RASTERIZESTATE_COUNT>myRasterizerStates;
	std::array<ID3D11SamplerState*, SamplerStates::SAMPLERSTATE_COUNT>mySamplerStates;

};

