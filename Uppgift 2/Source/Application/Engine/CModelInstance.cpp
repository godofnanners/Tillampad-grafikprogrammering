#include "CModelInstance.h"
#include "CModel.h"
void CModelInstance::Init(CModel * aModel)
{
	myModel = aModel;
}

CModel* CModelInstance::GetModel()
{
	return myModel;
}
