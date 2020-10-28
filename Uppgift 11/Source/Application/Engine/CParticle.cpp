#include "CParticle.h"

CParticle::CParticle()
{
	
}

CParticle::~CParticle()
{
}

void CParticle::Init(const SParticleData& aParticleData)
{
	myParticleData = aParticleData;
}

CParticle::SParticleData CParticle::GetParticleData()
{
	return myParticleData;
}


