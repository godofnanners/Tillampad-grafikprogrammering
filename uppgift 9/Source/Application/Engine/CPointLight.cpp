#include "CPointLight.h"

CPointLight::CPointLight()
{
}

const CommonUtilities::Vector3<float>& CPointLight::GetPosition()const
{
	return myPos;
}

const CommonUtilities::Vector3<float>& CPointLight::GetRange() const
{
	return myRange;
}

const CommonUtilities::Vector3<float>& CPointLight::GetColor() const
{
	return myColor;
}

void CPointLight::SetPosition(const CommonUtilities::Vector3<float>& aPos)
{
	myPos = aPos;
}

void CPointLight::SetRange(const CommonUtilities::Vector3<float>& aRange)
{
	myRange = aRange;
}

void CPointLight::SetColor(const CommonUtilities::Vector3<float>& aColor)
{
	myColor = aColor;
}




