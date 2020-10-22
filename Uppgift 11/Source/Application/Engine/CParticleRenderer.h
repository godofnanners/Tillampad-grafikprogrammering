#pragma once
#include <vector>
class CCamera;
class CParticleInstance;
class CParticleRenderer
{
public:
	void Render(CCamera* aCamera, std::vector<CParticleInstance*>& aParticleList);
private:
	myFrameBufferData;
};

