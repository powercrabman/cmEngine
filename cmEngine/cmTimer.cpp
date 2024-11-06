#include "pch.h"
#include "cmTimer.h"

void cmTimer::Initialize()
{
	::QueryPerformanceCounter(&mPrevCount);
	::QueryPerformanceFrequency(&mFreq);
}

void cmTimer::Update()
{
	// Delta Time üũ
	LARGE_INTEGER curCount = {};
	::QueryPerformanceCounter(&curCount);

	mDelta = (curCount.QuadPart - mPrevCount.QuadPart) / static_cast<float>(mFreq.QuadPart);
	mPrevCount = curCount;

	mTimeAcc += mDelta;
	mTotalTime += mDelta;

	// ������ üũ
	++mCounter;

	if (mTimeAcc >= 1.f)
	{
		mTimeAcc -= 1.f;
		mFPS = mCounter;
		mCounter = 0;
	}
}

