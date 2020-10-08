#include "CPointLight.h"

CPointLight::CPointLight()
{
}

const CommonUtilities::Vector3<float>& CPointLight::GetPosition()const
{
	return myPos;
}

const float CPointLight::GetRange() const
{
	return myRange;
}

const float CPointLight::GetIntensity() const
{
	return myIntensity;
}

const CommonUtilities::Vector3<float>& CPointLight::GetColor() const
{
	return myColor;
}

void CPointLight::SetPosition(const CommonUtilities::Vector3<float>& aPos)
{
	myPos = aPos;
}

void CPointLight::SetRange(const float& aRange)
{
	myRange = aRange;
}

void CPointLight::SetIntensity(const float& aIntensity)
{
	myIntensity = aIntensity;
}

void CPointLight::SetColor(const CommonUtilities::Vector3<float>& aColor)
{
	myColor = aColor;
}




