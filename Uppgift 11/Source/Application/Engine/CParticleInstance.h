#pragma once
#include "Vector3.hpp"
#include "GrowingArray.h"
#include "Matrix4x4.hpp"
#include <vector>
#include "CParticle.h"


class CParticleInstance
{
public:
	CParticleInstance();
	~CParticleInstance();

	void Init(CParticle*aParicle);
	void SetTransform(CommonUtilities::Vector3<float>aPosition, CommonUtilities::Vector3<float>aRotation);
	void SetRotation(CommonUtilities::Vector3<float>aRotation);
	void SetPosition(CommonUtilities::Vector3<float>aPosition);
	void Move(CommonUtilities::Vector3<float> aMovement);
	void Rotate(CommonUtilities::Vector3<float>aRotation);

	void Update(float aDeltatime, CommonUtilities::Vector3<float>aCameraPosition);

	CParticle* GetParticle();
	std::vector<CParticle::SParticleVertex>& GetParticleVerteces();
	CommonUtilities::Matrix4x4<float>GetTransform();
private:
	CParticle* myParticle;
	CommonUtilities::Matrix4x4<float>myTransform;
	float myTimeSinceLastParticle;
	float mySpawnPerSec;
	std::vector<CParticle::SParticleVertex>myParticleVertices;
};

