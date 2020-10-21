#pragma once
#include "Vector3.hpp"
#include "GrowingArray.h"
class CParticle;

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
	CommonUtilities::GrowingArray<CParticle::>
private:
};

