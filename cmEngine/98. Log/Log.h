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
		SINGLETON(Log);
	public:
		void ClearLogList();

		void LogClient(eLogLevel inLevel, std::string_view inMessage);
		void LogEngine(eLogLevel inLevel, std::string_view inMessage);

		const char* GetLogTextBegin() const { return mLogText.begin(); }
		const char* GetLogTextEnd() const { return mLogText.end(); }

		std::vector<LogInfo>::iterator	GetLogListBegin() { return mLogList.begin(); }
		std::vector<LogInfo>::iterator	GetLogListEnd() { return mLogList.end(); }
		LogInfo*						GetLogListData() { return mLogList.data(); }
		size_t							GetLogListSize() const { return mLogList.size(); }

	private:
		Log();
		~Log() = default;

		void LogEx(eLogCaller inCaller,eLogLevel inLevel, std::string_view inMessage);

		std::vector<LogInfo>	mLogList;
		ImGuiTextBuffer			mLogText;
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
