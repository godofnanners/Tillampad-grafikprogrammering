#pragma once
#include "Vector3.hpp"
#include "Matrix4x4.hpp"
class CModel;
class CModelInstance
{
public:
	CModelInstance();
	~CModelInstance();
	
	void Init(CModel * aModel);
	void SetTransform(CommonUtilities::Vector3<float> aRotation, CommonUtilities::Vector3<float>aPosition);
	void SetRotation(CommonUtilities::Vector3<float> aRotation);
	void SetPosition(CommonUtilities::Vector3<float> aPosition);
	void Move(CommonUtilities::Vector3<float> aMovement);
	void Rotate(CommonUtilities::Vector3<float> aRotation);

	CModel* GetModel();
	const CommonUtilities::Matrix4x4<float>& GetTransform() const;
private:
	CModel* myModel;
	CommonUtilities::Matrix4x4<float> myTransform;
};

