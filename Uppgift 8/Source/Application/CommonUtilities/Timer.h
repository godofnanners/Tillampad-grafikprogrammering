#pragma once
#include <chrono>
#include <iostream>
namespace CommonUtilities
{
	void Print();
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;
		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		float myMicroConversion = 0.000001f;
		double myTotalTime;
		std::chrono::time_point<std::chrono::steady_clock> myLastFrameTime;
		std::chrono::time_point<std::chrono::steady_clock> myCurrentTime;
		std::chrono::time_point<std::chrono::steady_clock> myStartTime;

		std::chrono::time_point<std::chrono::steady_clock> StartTime() const;
	};
}
