#pragma once
#include "Vector3.hpp"
class CPointLight
{
public:
	CPointLight();
	
	const CommonUtilities::Vector3<float>&GetPosition() const;
	const float GetRange()const;
	const CommonUtilities::Vector3<float>& GetColor()const;

	void SetPosition(const CommonUtilities::Vector3<float>& aPos);
	void SetRange(const float& aRange);
	void SetIntensity(const float& aIntensity);
	void SetColor(const CommonUtilities::Vector3<float>&aColor);
private:
	CommonUtilities::Vector3<float> myPos;
	float myRange;
	float myIntensity;
	CommonUtilities::Vector3<float>myColor;
};

