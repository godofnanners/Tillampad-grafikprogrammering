#pragma once
#include <string>
class CEnvironmentLight;
struct ID3D11Device;
class CLightFactory
{
public:
	CLightFactory(const CLightFactory&) = delete;
	static CLightFactory& GetInstance();
	void Init(ID3D11Device*aDevice);
	CEnvironmentLight* CreateEnvironmentalLight(std::wstring aFilePath);
private:
	ID3D11Device* myDevice;
	static CLightFactory myInstance;
	CLightFactory();
};

