#include "CForwardRenderer.h"
#include "CDirectX11Framework.h"
#include <d3d11.h>
#include "CModel.h"
#include "CModelInstance.h"
CForwardRenderer::CForwardRenderer()
{
	myContext = nullptr;
}

CForwardRenderer::~CForwardRenderer()
{
	myContext = nullptr;
}

bool CForwardRenderer::Init(CDirectX11Framework* aFramework)
{
	if (!aFramework)
	{
		return false;
	}

	myContext = aFramework->GetContext();
	
	if (!myContext)
	{
		return false;
	}

	return true;
}

void CForwardRenderer::Render(std::vector<CModelInstance*>& aModelList)
{
	for (CModelInstance*instance:aModelList)
	{
		CModel* model = instance->GetModel();
		CModel::SModelData modelData = model->GetModelData();

		myContext->IASetPrimitiveTopology(modelData.myPrimitiveTopology);
		myContext->IASetInputLayout(modelData.myInputLayout);

		myContext->IASetVertexBuffers(0, 1, &modelData.myVertexBuffer, &modelData.myStride, &modelData.myOffset);

		myContext->VSSetShader(modelData.myVertexShader, nullptr, 0);
		myContext->PSSetShader(modelData.myPixelShader, nullptr, 0);

		myContext->Draw(modelData.myNumberOfVerticies, 0);
	}
}
