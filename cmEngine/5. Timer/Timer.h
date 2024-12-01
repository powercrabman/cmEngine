#pragma once

namespace cmEngine
{
	struct TimerProp
	{
		LARGE_INTEGER PrevCount	= {};
		LARGE_INTEGER Freq		= {};

		float	DeltaTime		= 0.f;
		float	TimeAcc         = 0.f;
		float	TotalTime       = 0.f;

		UINT	FrameCount		= 0;
		UINT	FPS             = 0;
	};

	class Timer
	{
		SINGLETON(Timer);
	public:
		float	GetTotalTime() const { return mTimerProp.TotalTime; }
		float	GetDeltaTime() const { return mTimerProp.DeltaTime; }
		float	GetFPS() const { return mTimerProp.FPS; }

	private:
		Timer();
		~Timer() = default;

		void		Init();
		void		Update();

		TimerProp mTimerProp = {};
	};
}

