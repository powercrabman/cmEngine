#include "EnginePch.h"
#include "Timer.h"

namespace cmEngine
{
	void Timer::Initialize()
	{
		::QueryPerformanceCounter(&mTimerProp.PrevCount);
		::QueryPerformanceFrequency(&mTimerProp.Freq);
	}

	void Timer::Update()
	{
		// Delta Time üũ
		LARGE_INTEGER curCount = {};
		::QueryPerformanceCounter(&curCount);

		mTimerProp.DeltaTime = (curCount.QuadPart - mTimerProp.PrevCount.QuadPart) / static_cast<float>(mTimerProp.Freq.QuadPart);
		mTimerProp.PrevCount = curCount;

		mTimerProp.TimeAcc   += mTimerProp.DeltaTime;
		mTimerProp.TotalTime += mTimerProp.DeltaTime;
	}
}

