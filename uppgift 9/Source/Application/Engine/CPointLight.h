#pragma once
#include "Vector3.hpp"
class CPointLight
{
public:
	CPointLight();
	
	const CommonUtilities::Vector3<float>&GetPosition() const;
	const CommonUtilities::Vector3<float>&GetRange()const;
	const CommonUtilities::Vector3<float>&GetColor()const;

	void SetPosition(const CommonUtilities::Vector3<float>& aPos);
	void SetRange(const CommonUtilities::Vector3<float>&aRange);
	void SetColor(const CommonUtilities::Vector3<float>&aColor);
private:
	CommonUtilities::Vector3<float> myPos;
	CommonUtilities::Vector3<float> myRange;
	CommonUtilities::Vector3<float>myColor;
};

