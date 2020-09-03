#include "CModel.h"
#include <d3d11.h>

void CModel::Init(SModelData aModelData)
{
	myModelData = aModelData;
}

const CModel::SModelData& CModel::GetModelData()
{
	return myModelData;
}
