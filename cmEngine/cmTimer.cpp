#include "pch.h"
#include "cmTimer.h"

void cmTimer::Initialize()
{
	::QueryPerformanceCounter(&mPrevCount);
	::QueryPerformanceFrequency(&mFreq);
}

void cmTimer::Update()
{
	// Delta Time 체크
	LARGE_INTEGER curCount = {};
	::QueryPerformanceCounter(&curCount);

	mDelta = (curCount.QuadPart - mPrevCount.QuadPart) / static_cast<float>(mFreq.QuadPart);
	mPrevCount = curCount;

	mTimeAcc += mDelta;
	mTotalTime += mDelta;

	// 프레임 체크
	++mCounter;

	if (mTimeAcc >= 1.f)
	{
		mTimeAcc -= 1.f;
		mFPS = mCounter;
		mCounter = 0;
	}
}

