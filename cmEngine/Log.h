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

	struct LogData
	{
		eLogCaller	LogCaller;
		eLogLevel	LogLevel;
		std::string LogMessage;
	};

	class Log
	{
	public:
		static void Initialize();
		static void ClearLogList() { mLogList.clear(); }

		static void LogClient(eLogLevel inLevel, std::string_view inMessage);
		static void LogEngine(eLogLevel inLevel, std::string_view inMessage);

		static std::vector<LogData>::const_iterator GetLogDataConstBegin() { return mLogList.cbegin(); }
		static std::vector<LogData>::const_iterator GetLogDataConstEnd() { return mLogList.cend(); }

	private:

		enum { LOG_LIST_CAPACITY = 1024 };
		static std::vector<LogData> mLogList;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void Log::LogClient(eLogLevel inLevel, std::string_view inMessage)
	{
		mLogList.emplace_back(eLogCaller::Client, inLevel, inMessage.data());
	}

	inline void Log::LogEngine(eLogLevel inLevel, std::string_view inMessage)
	{
		mLogList.emplace_back(eLogCaller::Engine, inLevel, inMessage.data());
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
