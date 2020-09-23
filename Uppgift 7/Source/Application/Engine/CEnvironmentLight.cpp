#include "CEnvironmentLight.h"
#include <d3d11.h>

CEnvironmentLight::CEnvironmentLight(ID3D11ShaderResourceView* aCubemap) :
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
