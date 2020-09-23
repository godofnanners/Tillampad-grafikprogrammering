#include "CEnvironmentLight.h"
#include <d3d11.h>

CEnvironmentLight::CEnvironmentLight(ID3D11ShaderResourceView*aCubemap) :
	myCubemap(aCubemap)
{
	myDirection = { 1,1,1 };
	myColor = { 1,1,1 };
}

void CEnvironmentLight::SetDirection(CommonUtilities::Vector3<float> aDirection)
{
	myDirection = aDirection;
}

void CEnvironmentLight::SetColor(CommonUtilities::Vector3<float> aColor)
{
	myColor = aColor;
}

ID3D11ShaderResourceView * CEnvironmentLight::GetCubemap()
{
	return myCubemap;
}

CommonUtilities::Vector3<float> CEnvironmentLight::GetDirection()
{
	return myDirection;
}

CommonUtilities::Vector3<float> CEnvironmentLight::GetColor()
{
	return myColor;
}
