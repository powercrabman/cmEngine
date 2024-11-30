#include "EnginePch.h"
#include "Log.h"

namespace cmEngine
{
	struct LogConfig : public JsonMetaData
	{
		std::array<ImVec4, static_cast<UINT>(eLogLevel::Count)> logLevelColor = {};

		JSON_STRUCT_BODY(
			LogConfig,
			logLevelColor
		);
	};

	//===================================================

	void Log::Initialize()
	{
		mLogList.clear();
		mLogList.reserve(1000);
		mLogList.reserve(50000);
	}

	void Log::Destroy()
	{
		ClearLogList();
	}

	void Log::LogEx(eLogCaller inCaller, eLogLevel inLevel, std::string_view inMessage)
	{
		float timeStamp = Timer::GetTotalTime();

		size_t oldSize = mLogText.size();
		mLogText.appendf("[%.3f sec][%s][%s] %s\n", timeStamp, ToString(inCaller), ToString(inLevel), inMessage.data());
		for (int newSize = mLogText.size(); oldSize < newSize; oldSize++)
			if (mLogText[oldSize] == '\n')
			{
				mLogList.emplace_back(Timer::GetTotalTime(), inCaller, inLevel, oldSize + 1);
			}
	}
}
