#pragma once

namespace cmEngine::Math
{
	constexpr float PI = 3.141592653589793238462643383279f;
	constexpr float PI_2 = PI * 2.f;
	constexpr float PI_H = PI * 0.5f;
	constexpr float PI_Q = PI * 0.25;

	constexpr float EULER = 2.718281828459045235360287471f;

	constexpr float SMALL_NUM = 1.0e-6;

	constexpr inline float RadToDeg(float inRad)
	{
		return inRad * (180.f / PI);
	}

	constexpr inline float DegToRad(float inDeg)
	{
		return inDeg * (PI / 180.f);
	}

	constexpr inline float Abs(float inNum)
	{
		return inNum >= 0 ? inNum : -inNum;
	}

	constexpr inline bool Tolerance(float inNum)
	{
		return Abs(inNum) < Math::SMALL_NUM;
	}

	constexpr inline bool ApproxEqual(float inLeft, float inRight)
	{
		return Abs(inLeft - inRight) < Math::SMALL_NUM;
	}

	const inline void GetSinCos(float* inOutSin, float* inOutCos, float inRad)
	{
		::XMScalarSinCos(inOutSin, inOutCos, inRad);
	}

	const inline void GetSinCosDegree(float* inOutSin, float* inOutCos, float inDeg)
	{
		GetSinCos(inOutSin, inOutCos, DegToRad(inDeg));
	}

	inline float Wrap(float num, float low, float high)
	{
		float range = high - low;
		num = std::fmod(num - low, range);
		if (num < 0.f) num += range;
		return num + low;
	}
}
