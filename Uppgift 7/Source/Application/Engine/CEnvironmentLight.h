#pragma once
#include "Vector3.hpp"
struct ID3D11ShaderResourceView;

class CEnvironmentLight
{
public:
	CEnvironmentLight(ID3D11ShaderResourceView * aCubemap);
	void SetDirection(CommonUtilities::Vector3<float> aDirection);
	void SetColor(CommonUtilities::Vector3<float> aColor);
private:
	ID3D11ShaderResourceView* myCubemap;
	CommonUtilities::Vector3<float>myDirection;
	CommonUtilities::Vector3<float>myColor;
};

