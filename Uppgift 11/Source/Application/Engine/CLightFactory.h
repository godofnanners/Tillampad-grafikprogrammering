#pragma once
#include <string>
#include "Vector3.hpp"
class CEnvironmentLight;
class CPointLight;
struct ID3D11Device;
class CLightFactory
{
public:
	CLightFactory(const CLightFactory&) = delete;
	static CLightFactory& GetInstance();
	void Init(ID3D11Device* aDevice);
	CEnvironmentLight* CreateEnvironmentalLight(std::wstring aFilePath);

	CPointLight* CreatePointLight(const CommonUtilities::Vector3<float>& aPos, const float& aRange, const float& aIntensity = 1.0f, const CommonUtilities::Vector3<float>& aColor = { 1,1,1 });

private:
	ID3D11Device* myDevice;
	static CLightFactory myInstance;
	CLightFactory();
};

