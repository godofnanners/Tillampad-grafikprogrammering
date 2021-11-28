#pragma once
#include <string>
#include "GrowingArray.h"
class ID3D11Device;
class CParticle;
class CDirectX11Framework;
class CParticleFactory
{
public:
	CParticleFactory();
	~CParticleFactory();

	bool Init(CDirectX11Framework* aFramework);

	CParticle* GetPartticle(std::string aFilePath);
	CParticle* LoadParticle(std::string aFilePath);

	static CParticleFactory& GetInstance();

private:
	static CParticleFactory ourInstance;
	ID3D11Device* myDevice;
	CommonUtilities::GrowingArray<std::pair<std::string, CParticle*>>myParticles;
};

