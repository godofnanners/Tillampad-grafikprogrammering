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
	void SetTransform(const CommonUtilities::Vector3<float>& aRotation, const CommonUtilities::Vector3<float>&aPosition);
	void SetRotation(const CommonUtilities::Vector3<float>& aRotation);
	void SetPosition(const CommonUtilities::Vector3<float>& aPosition);
	void Move(const CommonUtilities::Vector3<float>& aMovement);
	void Rotate(const CommonUtilities::Vector3<float>& aRotation);

	CModel* GetModel();
	const CommonUtilities::Matrix4x4<float>& GetTransform() const;
private:
	CModel* myModel;
	CommonUtilities::Matrix4x4<float> myTransform;
};

