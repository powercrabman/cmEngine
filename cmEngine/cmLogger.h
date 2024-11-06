#pragma once
#include "cmLogData.h"

class cmLoggerGUI;

class cmLogger
{
	ENGINE_MODULE_BODY();
public:
	virtual ~cmLogger();

	void Logging(eLogLevel inLevel, const char* format, ...);

	const std::vector<cmLogData>& GetLogData() const { return mLogDatas; }

	void ClearLog() { mLogDatas.clear(); }

private:
	cmLogger();

	void Initialize();

private:
	void LoggingCore(eLogLevel inLevel, const char* format, const va_list& args);

private:
	std::vector<cmLogData> mLogDatas = {};
	cmStaticTextBuffer<512> mTempBuffer;

	cmLoggerGUI* mGUI = nullptr;
};

// 로그 형태 
// |타임스태프|대상|레벨|메시지
// 로그 구조체