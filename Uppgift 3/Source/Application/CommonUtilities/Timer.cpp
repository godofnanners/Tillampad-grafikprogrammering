#include "Timer.h"

namespace CommonUtilities
{
	void Print()
	{
		std::cout << "cool, it works";
	}

	Timer::Timer()
	{
		myStartTime = StartTime();
	}

	void Timer::Update()
	{
		myLastFrameTime = myCurrentTime;
		myCurrentTime = std::chrono::high_resolution_clock::now();
	}

	float Timer::GetDeltaTime() const
	{
		
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(myCurrentTime-myLastFrameTime).count();

		if (myLastFrameTime.time_since_epoch().count()==0)
		{
			return 0;
		}

		return deltaTime*myMicroConversion;
		
	}

	double Timer::GetTotalTime() const
	{		
		double totalTime = std::chrono::duration_cast<std::chrono::microseconds>(myCurrentTime - myStartTime).count();

		return totalTime*myMicroConversion;
	}

	std::chrono::time_point<std::chrono::steady_clock> Timer::StartTime() const
	{
		return std::chrono::high_resolution_clock::now();
	}


}
