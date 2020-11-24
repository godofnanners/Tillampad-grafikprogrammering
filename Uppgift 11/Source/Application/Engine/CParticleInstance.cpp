#include "CParticleInstance.h"
#include "CParticle.h"
#include <algorithm>
#include "Random.hpp"

CParticleInstance::CParticleInstance()
{
}

CParticleInstance::~CParticleInstance()
{
}

void CParticleInstance::Init(CParticle* aParticle)
{
	myParticle = aParticle;	
	mySpawnPerSec = 1 / myParticle->GetParticleData().mySpawnRate;
	CParticle::SParticleData particleData=myParticle->GetParticleData();
	myParticleVertices.reserve(ceilf(particleData.myParticleLifetime * particleData.mySpawnRate));
}

void CParticleInstance::SetTransform(CommonUtilities::Vector3<float> aPosition, CommonUtilities::Vector3<float> aRotation)
{
	myTransform.SetTranslation(aPosition);
	myTransform.SetRotation(aRotation);
}

void CParticleInstance::SetRotation(CommonUtilities::Vector3<float> aRotation)
{
	myTransform.SetRotation(aRotation);
}

void CParticleInstance::SetPosition(CommonUtilities::Vector3<float> aPosition)
{
	myTransform.SetTranslation(aPosition);
}

void CParticleInstance::Move(CommonUtilities::Vector3<float> aMovement)
{
	myTransform.AddToTranslation(aMovement);
}

void CParticleInstance::Rotate(CommonUtilities::Vector3<float> aRotation)
{
	myTransform.AddToRotation(aRotation, false);
}

void CParticleInstance::Update(float aDeltatime, CommonUtilities::Vector3<float> aCameraPosition)
{
	CParticle::SParticleData particleData = myParticle->GetParticleData();

	myTimeSinceLastParticle += aDeltatime;

	while (myTimeSinceLastParticle > mySpawnPerSec)
	{
		myTimeSinceLastParticle -= mySpawnPerSec;
		CParticle::SParticleVertex particleVertex;
		particleVertex.myPosition = { myTransform.GetPosition(),1 };
		particleVertex.myMovement = CommonUtilities::Vector4<float>(CommonUtilities::GetRandomFloat(1.f, 10.f), CommonUtilities::GetRandomFloat(1.f, 10.f), 0, 0).GetNormalized() * particleData.myParticleSpeed;
		particleVertex.myLifetime = particleData.myParticleLifetime;
		particleVertex.myColor = particleData.myParticleStartColor;
		particleVertex.myDistanceToCamera = (particleVertex.myPosition - CommonUtilities::Vector4<float>(aCameraPosition, 1)).Length();
		particleVertex.mySize = { particleData.myParticleStartSize,particleData.myParticleStartSize };
		myParticleVertices.emplace_back(particleVertex);
	}

	CommonUtilities::Vector4<float>startNendColorDiff = particleData.myParticleEndColor - particleData.myParticleStartColor;
	float startNendSizeDiff = particleData.myParticleEndSize - particleData.myParticleStartSize;
	//Update particles
	for (size_t i = 0; i < myParticleVertices.size(); i++)
	{
		CParticle::SParticleVertex& particleVertex = myParticleVertices[i];
		particleVertex.myLifetime -= aDeltatime;
		if (particleVertex.myLifetime < 0)
		{
			myParticleVertices.erase(myParticleVertices.begin() + i);
			i--;
			continue;
		}

		particleVertex.myPosition += particleVertex.myMovement * aDeltatime;
		float frameSizeChange = particleData.myPerSecSizeDiff * aDeltatime;
		particleVertex.mySize += CommonUtilities::Vector2<float>(frameSizeChange, frameSizeChange);
		particleVertex.myColor += particleData.myPerSecColorDiff * aDeltatime;
	}
	std::sort(myParticleVertices.begin(), myParticleVertices.end(), [](const CParticle::SParticleVertex& aFirstParticle, const CParticle::SParticleVertex& aSecondParticle)
		{
			return aFirstParticle.myDistanceToCamera > aSecondParticle.myDistanceToCamera;
		});
}

CParticle* CParticleInstance::GetParticle()
{
	return myParticle;
}

std::vector<CParticle::SParticleVertex>& CParticleInstance::GetParticleVerteces()
{
	return myParticleVertices;
}

CommonUtilities::Matrix4x4<float> CParticleInstance::GetTransform()
{
	return myTransform;
}
