#include "CLightFactory.h"
#include "CEnvironmentLight.h"
#include "DDSTextureLoader.h"
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

CLightFactory::CLightFactory()
{
	myDevice = nullptr;
}
