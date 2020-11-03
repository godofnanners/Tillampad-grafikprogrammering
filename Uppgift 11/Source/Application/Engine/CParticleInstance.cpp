#include "CParticleInstance.h"
#include "CParticle.h"
#include <algorithm>

CParticleInstance::CParticleInstance()
{
}

CParticleInstance::~CParticleInstance()
{
}

void CParticleInstance::Init(CParticle* aParticle)
{
	myParticle = aParticle;

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

	if (myTimeSinceLastParticle > particleData.mySpawnRate)
	{
		myTimeSinceLastParticle = 0;
		myParticleVertices.emplace_back(CParticle::SParticleVertex());
		myParticleVertices.back().myPosition = { myTransform.GetPosition(),1 };
	}

	//Update particles
	for (size_t i = 0; i < myParticleVertices.size(); i++)
	{
		myParticleVertices[i].myLifetime -= aDeltatime;
		if (myParticleVertices[i].myLifetime < 0)
		{
			myParticleVertices.erase(myParticleVertices.begin() + i);
			i--;
			continue;
		}



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
