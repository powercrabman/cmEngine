#include "EnginePch.h"
#include "Log.h"

namespace cmEngine
{
	void Log::Initialize()
	{
		mLogList.clear();
		mLogList.reserve(LOG_LIST_CAPACITY);

		LogConfig cf = {};
		if (ConfigSystem::Load(cf))
		{
			LogData::LogLevelColor[(uint32)eLogLevel::Error] = cf.LogErrorTextColor;
			LogData::LogLevelColor[(uint32)eLogLevel::Debug] = cf.LogDebugTextColor;
			LogData::LogLevelColor[(uint32)eLogLevel::Info] = cf.LogInfoTextColor;
			LogData::LogLevelColor[(uint32)eLogLevel::Trace] = cf.LogTraceTextColor;
			LogData::LogLevelColor[(uint32)eLogLevel::Fatal] = cf.LogFatalTextColor;
			LogData::LogLevelColor[(uint32)eLogLevel::Warn] = cf.LogWarnTextColor;
		}

	}

	void Log::Destory()
	{
		ClearLogList();

		LogConfig cf = {};
		cf.LogErrorTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Error];
		cf.LogDebugTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Debug];
		cf.LogInfoTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Info];
		cf.LogTraceTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Trace];
		cf.LogFatalTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Fatal];
		cf.LogWarnTextColor = LogData::LogLevelColor[(uint32)eLogLevel::Warn];

		ConfigSystem::Save(cf);
	}

}