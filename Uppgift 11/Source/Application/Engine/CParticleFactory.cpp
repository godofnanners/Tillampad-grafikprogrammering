#include "CParticleFactory.h"
#include "CDirectX11Framework.h"
CParticleFactory CParticleFactory::ourInstance;

CParticleFactory::CParticleFactory()
{
    myDevice = nullptr;
}

CParticleFactory::~CParticleFactory()
{
}

bool CParticleFactory::Init(CDirectX11Framework* aFramework)
{
    myDevice = aFramework->GetDevice();
    return false;
}

CParticle* CParticleFactory::GetPartticle(std::string aFilePath)
{
    return nullptr;
}

CParticle* CParticleFactory::LoadParticle(std::string aFilePath)
{
    return nullptr;
}

CParticleFactory& CParticleFactory::GetInstance()
{
    return ourInstance;
}
