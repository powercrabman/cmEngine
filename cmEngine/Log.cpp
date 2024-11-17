#include "EnginePch.h"
#include "Log.h"

namespace cmEngine
{
	void Log::Initialize()
	{
		mLogList.clear();
		mLogList.reserve(LOG_LIST_CAPACITY);
		LogConfig cf = {};
		ConfigEngine::Load(cf);
		LogData::LogLevelColor = cf.LogLevelColor;
	}

	void Log::Destory()
	{
		ClearLogList();
		LogConfig cf = {};
		cf.LogLevelColor = LogData::LogLevelColor;
		ConfigEngine::Save(cf);
	}

}