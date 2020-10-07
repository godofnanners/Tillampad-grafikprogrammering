#include "CLightFactory.h"
#include "CEnvironmentLight.h"
#include "DDSTextureLoader.h"
#include "CPointLight.h"
#include <d3d11.h>
CLightFactory CLightFactory::myInstance;

CLightFactory& CLightFactory::GetInstance()
{
	return myInstance;
}

void CLightFactory::Init(ID3D11Device* aDevice)
{
	myDevice = aDevice;
}

CEnvironmentLight* CLightFactory::CreateEnvironmentalLight(std::wstring aFilePath)
{
	HRESULT result;
	ID3D11ShaderResourceView* CubeMapShaderResourceView;
	result=DirectX::CreateDDSTextureFromFile(myDevice, aFilePath.c_str(), nullptr, &CubeMapShaderResourceView);
	CEnvironmentLight* envLight = new CEnvironmentLight(CubeMapShaderResourceView);
	return envLight;
}

CPointLight* CLightFactory::CreatePointLight(const CommonUtilities::Vector3<float>&aPos, const CommonUtilities::Vector3<float>&aRange,const CommonUtilities::Vector3<float>&aColor)
{
	CPointLight* pointLight = new CPointLight();
	pointLight->SetPosition(aPos);
	pointLight->SetRange(aRange);
	pointLight->SetColor(aColor);
	return pointLight;
}

CLightFactory::CLightFactory()
{
	myDevice = nullptr;
}
