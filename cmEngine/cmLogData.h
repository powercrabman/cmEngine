#pragma once

enum class eLogLevel
{
	Trace,	/* 일반 메시지 */
	Debug,	/* 디버깅 모드에서만 활성화. 개발자용 로그 */
	Info,	/* 시스템 상태나 이벤트 정보 출력 */
	Warn,	/* 비정상적인 문제가 발생했지만, 시스템 작동에 문제가 없는 경우 */
	Error,	/* 오류가 발생하여 요청이 실패한 경우 */
	Fatal,	/* 심각한 오류로 시스템 작동에 오류가 발생한 경우 */

	Count
};

struct cmLogData
{
	float TimeStamp;
	eLogLevel Level;
	std::string Text;

	inline static const char* sLogLevelString[(uint32)eLogLevel::Count] =
	{
		"Trace",
		"Debug",
		"Info",
		"Warn",
		"Error",
		"Fatal"
	};

	inline static ImVec4 sLogLevelColor[(uint32)eLogLevel::Count] = {
	ImVec4{ 1.f, 0.980, 0.941f, 1.f },	/* Trace */
	ImVec4{ 0.283f, 0.758f, 0.914f, 1.f },	/* Debug */
	ImVec4{ 0.220f, 0.906f, 0.085f, 1.f },	/* Info */
	ImVec4{ 0.973f, 0.980f, 0.327f, 1.f },	/* Warn */
	ImVec4{ 0.946f, 0.283f, 0.283f, 1.f },	/* Error */
	ImVec4{ 1.f, 0.f, 0.8f, 1.f } 	/* Fatal */
	};
};