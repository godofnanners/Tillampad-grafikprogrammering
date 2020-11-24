#include "CRenderStateManager.h"
#include "CDirectX11Framework.h"
#include <d3d11.h>
#include <assert.h>
#include <limits>
CRenderStateManager::CRenderStateManager()
{
}

CRenderStateManager::~CRenderStateManager()
{
}

bool CRenderStateManager::Init(CDirectX11Framework* aFramework)
{
    myContext = aFramework->GetContext();
    CreateBlendStates(aFramework->GetDevice());
    CreateDepthStencilState(aFramework->GetDevice());
    CreateRasterizerState(aFramework->GetDevice());
    CreateSamplerState(aFramework->GetDevice());
    return true;
}

void CRenderStateManager::SetBlendStates(BlendStates aBlendState)
{
    myContext->OMSetBlendState(myBlendStates[aBlendState],NULL,NULL);
}

void CRenderStateManager::SetDepthStencilState(DepthStencilStates aDepthStencilState)
{
    myContext->OMSetDepthStencilState(myDepthStencilStates[aDepthStencilState], D3D11_DEPTH_WRITE_MASK_ZERO);
}

void CRenderStateManager::SetRasterizerState(RasterizerStates aRasterizerState)
{
    myContext->RSSetState(myRasterizerStates[aRasterizerState]);
}

void CRenderStateManager::SetSamplerState(SamplerStates aSamplerState)
{
    myContext->PSSetSamplers(0, 1, &mySamplerStates[aSamplerState]);
}

void CRenderStateManager::SetAllStates(BlendStates aBlendState, DepthStencilStates aDepthStencilState, RasterizerStates aRasterizerState, SamplerStates aSamplerState)
{
    SetBlendStates(aBlendState);
    SetDepthStencilState(aDepthStencilState);
    SetRasterizerState(aRasterizerState);
    SetSamplerState(aSamplerState);
}

void CRenderStateManager::SetAllDefault()
{
    SetBlendStates(BlendStates::BLENDSTATE_ALPHABLEND);
    SetDepthStencilState(DepthStencilStates::DEPTHSTENCILSTATE_DEFAULT);
    SetRasterizerState(RasterizerStates::RASTERIZERSTATE_DEFAULT);
    SetSamplerState(SamplerStates::SAMPLERSTATE_POINT);
}

bool CRenderStateManager::CreateBlendStates(ID3D11Device* aDevice)
{
    HRESULT result;
    D3D11_BLEND_DESC alphblendDescription = { 0 };
    alphblendDescription.RenderTarget[0].BlendEnable = true;
    alphblendDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    alphblendDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    alphblendDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    alphblendDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    alphblendDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
    alphblendDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
    alphblendDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC additativeblendDescritption = { 0 };
    additativeblendDescritption.RenderTarget[0].BlendEnable = true;
    additativeblendDescritption.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    additativeblendDescritption.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    additativeblendDescritption.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    additativeblendDescritption.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    additativeblendDescritption.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
    additativeblendDescritption.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
    additativeblendDescritption.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    ID3D11BlendState* alphaBlendState;
    result = aDevice->CreateBlendState(&alphblendDescription, &alphaBlendState);
    if (FAILED(result))
    {
        assert(!" alphaBlendState failed to be created in RenderStateManager");
    }
    ID3D11BlendState* additativeBlendState;
    result = aDevice->CreateBlendState(&additativeblendDescritption, &additativeBlendState);
    if (FAILED(result))
    {
        assert(!"additativeBlendState failed to be created in RenderStateManager");
    }


    myBlendStates[BLENDSTATE_DISABLE] = nullptr;
    myBlendStates[BLENDSTATE_ALPHABLEND] = alphaBlendState;
    myBlendStates[BLENDSTATE_ADDITATIVEBLEND] = additativeBlendState;

    return true;
}

bool CRenderStateManager::CreateDepthStencilState(ID3D11Device* aDevice)
{
    HRESULT result;

    D3D11_DEPTH_STENCIL_DESC onlyreadDepthDescription = { 0 };
    onlyreadDepthDescription.DepthEnable = true;
    onlyreadDepthDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    onlyreadDepthDescription.DepthFunc = D3D11_COMPARISON_LESS;
    onlyreadDepthDescription.StencilEnable = false;

    ID3D11DepthStencilState* onlyreadDepthStencilState;
    result = aDevice->CreateDepthStencilState(&onlyreadDepthDescription, &onlyreadDepthStencilState);
    if (FAILED(result))
    {
        assert(!"DepthStencil failed to be created in RenderStateManager");
    }
    myDepthStencilStates[DEPTHSTENCILSTATE_DEFAULT] = nullptr;
    myDepthStencilStates[DEPTHSTENCILSTATE_ONLYREAD] = onlyreadDepthStencilState;
    return true;
}

bool CRenderStateManager::CreateRasterizerState(ID3D11Device* aDevice)
{
    HRESULT result;

    D3D11_RASTERIZER_DESC wireframerRasterizerDescription = {};
    wireframerRasterizerDescription.FillMode = D3D11_FILL_WIREFRAME;
    wireframerRasterizerDescription.CullMode = D3D11_CULL_BACK;
    wireframerRasterizerDescription.DepthClipEnable = true;

    ID3D11RasterizerState* wireframeRasterizerState;
    result = aDevice->CreateRasterizerState(&wireframerRasterizerDescription, &wireframeRasterizerState);
    if (FAILED(result))
    {
        assert(!"RasterizerState failed to be created in RenderStateManager");
    }

    myRasterizerStates[RASTERIZERSTATE_DEFAULT] = nullptr;
    myRasterizerStates[RASTERIZERSTATE_WIREFRAME] = wireframeRasterizerState;
    return true;
}

bool CRenderStateManager::CreateSamplerState(ID3D11Device* aDevice)
{
    HRESULT result;
    D3D11_SAMPLER_DESC pointSampleDescription = {};
    pointSampleDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    pointSampleDescription.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    pointSampleDescription.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    pointSampleDescription.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    pointSampleDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
    pointSampleDescription.MinLOD = -FLT_MAX;
    pointSampleDescription.MaxLOD = FLT_MAX;

    ID3D11SamplerState* pointSamplerState;
    result = aDevice->CreateSamplerState(&pointSampleDescription, &pointSamplerState);
    if (FAILED(result))
    {
        assert(!"PointsSampleState failed to be created in RenderStateManager");
    }
    
    mySamplerStates[SAMPLERSTATE_TRILINEAR] = nullptr;
    mySamplerStates[SAMPLERSTATE_POINT] = pointSamplerState;
    return true;
}
