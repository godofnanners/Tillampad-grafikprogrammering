#include "CModelInstance.h"
#include "CModel.h"
CModelInstance::CModelInstance()
{
	myModel = nullptr;
}
CModelInstance::~CModelInstance()
{
}
void CModelInstance::Init(CModel * aModel)
{
	myModel = aModel;
}

CModel* CModelInstance::GetModel()
{
	return myModel;
}

void CModelInstance::SetTransform(CommonUtilities::Vector3<float> aRotation, CommonUtilities::Vector3<float> aPosition)
{
	myTransform.SetTranslation(aPosition);
	myTransform.SetRotation(aRotation, false);
}

void CModelInstance::SetRotation(CommonUtilities::Vector3<float> aRotation)
{
	myTransform.SetRotation(aRotation, false);
}

void CModelInstance::SetPosition(CommonUtilities::Vector3<float> aPosition)
{
	myTransform.SetTranslation(aPosition);
}

void CModelInstance::Move(CommonUtilities::Vector3<float> aMovement)
{
	myTransform.AddToTranslation(aMovement);
}

void CModelInstance::Rotate(CommonUtilities::Vector3<float> aRotation)
{
	myTransform.AddToRotation(aRotation, false);
}

const CommonUtilities::Matrix4x4<float>& CModelInstance::GetTransform() const
{
	return myTransform;
}
