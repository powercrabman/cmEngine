#pragma once

class cmTimer
{
	ENGINE_MODULE_BODY();
public:
	virtual ~cmTimer() = default;

	void Update();

	float	GetTotalTime() const { return mTotalTime; }
	float	GetDeltaTime() const { return mDelta; }
	uint32	GetFPS() const { return mFPS; }

private:
	cmTimer() = default;
	void Initialize();

	LARGE_INTEGER mPrevCount = {};
	LARGE_INTEGER mFreq = {};

	float mDelta = 0.f;

	uint32 mFPS = 0;
	uint32 mCounter = 0;
	float mTimeAcc = 0.f;
	float mTotalTime = 0.f;
};