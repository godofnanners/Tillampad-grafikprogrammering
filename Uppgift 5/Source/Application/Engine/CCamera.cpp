#include "CCamera.h"
#include <cmath>

CCamera::CCamera()
{
	
}

CCamera::~CCamera()
{
}

void CCamera::Init(float aFov, CommonUtilities::Vector2<float> aDimensions)
{

	float nearPlane = 1.f;
	float farPlane = 10000.f;
	myProjection(1, 1) = (1 / std::tanf(aFov / 2));
	myProjection(1, 2) = 0;
	myProjection(1, 3) = 0;
	myProjection(1, 4) = 0;

	myProjection(2, 1) = 0;
	myProjection(2, 2) = (aDimensions.x / aDimensions.y / std::tanf(aFov / 2));
	myProjection(2, 3) = 0;
	myProjection(2, 4) = 0;

	myProjection(3, 1) = 0;
	myProjection(3, 2) = 0;
	myProjection(3, 3) = farPlane / (farPlane - nearPlane);
	myProjection(3, 4) = 1;

	myProjection(4, 1) = 0;
	myProjection(4, 2) = 0;
	myProjection(4, 3) = (-1 * nearPlane * farPlane) / (farPlane - nearPlane);
	myProjection(4, 4) = 0;
}

void CCamera::SetTransform(CommonUtilities::Vector3<float> aRotation, CommonUtilities::Vector3<float> aPosition)
{
    myTransform.SetTranslation(aPosition);
    myTransform.SetRotation(aRotation,false);
}

void CCamera::SetRotation(CommonUtilities::Vector3<float> aRotation)
{
    myTransform.SetRotation(aRotation,false);
}

void CCamera::SetPosition(CommonUtilities::Vector3<float> aPosition)
{
    myTransform.SetTranslation(aPosition);
}

void CCamera::Move(CommonUtilities::Vector3<float> aMovement)
{
    myTransform.AddToTranslation(aMovement);
}

void CCamera::Rotate(CommonUtilities::Vector3<float> aRotation)
{
    myTransform.AddToRotation(aRotation,false);
}

const CommonUtilities::Matrix4x4<float>& CCamera::GetTransform() const
{
    return myTransform;
}

const CommonUtilities::Matrix4x4<float>& CCamera::GetProjection() const
{
    return myProjection;
}
