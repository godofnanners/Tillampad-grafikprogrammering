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

void CModelInstance::SetTransform(const CommonUtilities::Vector3<float>& aRotation, const CommonUtilities::Vector3<float>& aPosition)
{
	myTransform.SetTranslation(aPosition);
	myTransform.SetRotation(aRotation, false);
}

void CModelInstance::SetRotation(const CommonUtilities::Vector3<float>& aRotation)
{
	myTransform.SetRotation(aRotation, false);
}

void CModelInstance::SetPosition(const CommonUtilities::Vector3<float>& aPosition)
{
	myTransform.SetTranslation(aPosition);
}

void CModelInstance::Move(const CommonUtilities::Vector3<float>& aMovement)
{
	myTransform.AddToTranslation(aMovement);
}

void CModelInstance::Rotate(const CommonUtilities::Vector3<float>& aRotation)
{
	myTransform.AddToRotation(aRotation, false);
}

CModel* CModelInstance::GetModel()
{
	return myModel;
}

const CommonUtilities::Matrix4x4<float>& CModelInstance::GetTransform() const
{
	return myTransform;
}
