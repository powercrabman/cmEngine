#pragma once

namespace cmEngine
{
	enum class eLogLevel
	{
		Trace, Debug, Info, Warn, Error, Fatal, Count
	};

	enum class eLogCaller
	{
		Client, Engine, Count
	};

	struct LogInfo
	{
		float		logTime;
		eLogCaller	logCaller;
		eLogLevel	logLevel;
		uint32		lineOffset;
	};

	class Log
	{
	public:
		static void Initialize();
		static void Destroy();
		static void ClearLogList()
		{
			mLogText.clear();
			mLogList.clear();
			mLogList.emplace_back(Timer::GetDeltaTime(), eLogCaller::Engine, eLogLevel::Debug, 0);
		}

		static void LogClient(eLogLevel inLevel, std::string_view inMessage);
		static void LogEngine(eLogLevel inLevel, std::string_view inMessage);

		static const char* GetLogTextBegin() { return mLogText.begin(); }
		static const char* GetLogTextEnd() { return mLogText.end(); }

		static std::vector<LogInfo>::iterator	GetLogListBegin() { return mLogList.begin(); }
		static std::vector<LogInfo>::iterator	GetLogListEnd() { return mLogList.end(); }
		static LogInfo*							GetLogListData() { return mLogList.data(); }
		static size_t							GetLogListSize() { return mLogList.size(); }

	private:
		static void LogEx(eLogCaller inCaller,eLogLevel inLevel, std::string_view inMessage);

	private:
		inline static std::vector<LogInfo>	mLogList = {};
		inline static ImGuiTextBuffer		mLogText = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void Log::LogClient(eLogLevel inLevel, std::string_view inMessage)
	{
		LogEx(eLogCaller::Client, inLevel, inMessage);
	}

	inline void Log::LogEngine(eLogLevel inLevel, std::string_view inMessage)
	{
		LogEx(eLogCaller::Engine, inLevel, inMessage);
	}

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eLogLevel inLogLevel)
	{
		switch (inLogLevel)
		{
		case cmEngine::eLogLevel::Trace:	return "Trace";
		case cmEngine::eLogLevel::Debug:	return "Debug";
		case cmEngine::eLogLevel::Info:		return "Info";
		case cmEngine::eLogLevel::Warn:		return "Warn";
		case cmEngine::eLogLevel::Error:	return "Error";
		case cmEngine::eLogLevel::Fatal:	return "Fatal";
		default:							return "Undefined";
		}
	}

	inline constexpr const char* ToString(eLogCaller inLogCaller)
	{
		switch (inLogCaller)
		{
		case cmEngine::eLogCaller::Client:	return "Client";
		case cmEngine::eLogCaller::Engine:	return "Engine";
		default:							return "Undefined";
		}
	}
}
