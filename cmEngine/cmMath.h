#pragma once

namespace cmMath
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
}
