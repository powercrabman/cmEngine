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
		// Delta Time 
		LARGE_INTEGER curCount = {};
		::QueryPerformanceCounter(&curCount);

		mTimerProp.DeltaTime = (curCount.QuadPart - mTimerProp.PrevCount.QuadPart) / static_cast<float>(mTimerProp.Freq.QuadPart);
		mTimerProp.PrevCount = curCount;

		mTimerProp.TimeAcc   += mTimerProp.DeltaTime;
		mTimerProp.TotalTime += mTimerProp.DeltaTime;

		// Fps
		++mTimerProp.FrameCount;

		if (mTimerProp.TimeAcc >= 1.f)
		{
			mTimerProp.TimeAcc -= 1.f;
			mTimerProp.FPS = mTimerProp.FrameCount;
			mTimerProp.FrameCount = 0;
		}
	}
}

