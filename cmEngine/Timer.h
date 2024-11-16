#pragma once

namespace cmEngine
{
	struct TimerProp
	{
		LARGE_INTEGER PrevCount		= {};
		LARGE_INTEGER Freq			= {};

		float	DeltaTime			= 0.f;
		float	TimeAcc             = 0.f;
		float	TotalTime           = 0.f;

		UINT	FrameCount			= 0;
		UINT	FPS                 = 0;
	};

	class Timer
	{
		friend class EngineCore;
		friend class Application;
	public:
		static float GetTotalTime() { return mTimerProp.TotalTime; }
		static float GetDeltaTime() { return mTimerProp.DeltaTime; }
		static UINT	 GetFPS() { return mTimerProp.FPS; }

	private:
		static void Initialize();
		static void	Update();

		inline static TimerProp mTimerProp = {};
	};
}

