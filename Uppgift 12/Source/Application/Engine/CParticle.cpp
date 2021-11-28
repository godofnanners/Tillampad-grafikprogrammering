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
	myParticleData.myPerSecColorDiff = (myParticleData.myParticleEndColor - myParticleData.myParticleStartColor) / myParticleData.myParticleLifetime;
	myParticleData.myPerSecSizeDiff = (myParticleData.myParticleEndSize - myParticleData.myParticleStartSize) / myParticleData.myParticleLifetime;
}

const CParticle::SParticleData& CParticle::GetParticleData()
{
	return myParticleData;
}


