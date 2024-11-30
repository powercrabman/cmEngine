#include "0. cmEngine/cmEngine.h"
#include "Log.h"

namespace cmEngine
{
	struct LogConfig
	{
		std::array<ImVec4, static_cast<UINT>(eLogLevel::Count)> logLevelColor = {};

		JSON_STRUCT_BODY(
			LogConfig,
			logLevelColor
		);
	};

	//===================================================

	void Log::ClearLogList()
	{
		mLogText.clear();
		mLogList.clear();
		mLogList.emplace_back(Timer::Ref().GetDeltaTime(), eLogCaller::Engine, eLogLevel::Debug, 0);
	}

	Log::Log()
	{
		mLogList.reserve(50'000);
		mLogText.reserve(100'000);
		EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e)
		{
			Destroy();
		});
	}

	void Log::LogEx(eLogCaller inCaller, eLogLevel inLevel, std::string_view inMessage)
	{
		float timeStamp = Timer::Ref().GetTotalTime();

		size_t oldSize = mLogText.size();
		mLogText.appendf("[%.3f sec][%s][%s] %s\n", timeStamp, ToString(inCaller), ToString(inLevel), inMessage.data());
		for (int newSize = mLogText.size(); oldSize < newSize; oldSize++)
			if (mLogText[oldSize] == '\n')
			{
				mLogList.emplace_back(Timer::Ref().GetTotalTime(), inCaller, inLevel, oldSize + 1);
			}
	}
}
