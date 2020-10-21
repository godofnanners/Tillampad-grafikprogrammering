#pragma once
#include "Vector3.hpp"
#include "Vector2.h"
#include "Matrix4x4.hpp"
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(float aFov, CommonUtilities::Vector2<float> aDimensions);
	void SetTransform(CommonUtilities::Vector3<float> aRotation, CommonUtilities::Vector3<float>aPosition);
	void SetRotation(CommonUtilities::Vector3<float> aRotation);
	void SetPosition(CommonUtilities::Vector3<float> aPosition);
	void Move(CommonUtilities::Vector3<float> aMovement);
	void Rotate(CommonUtilities::Vector3<float> aRotation);


	const CommonUtilities::Matrix4x4<float>& GetTransform() const;
	const CommonUtilities::Matrix4x4<float>& GetProjection() const;

private:
	CommonUtilities::Matrix4x4<float> myTransform;
	CommonUtilities::Matrix4x4<float> myProjection;
};

