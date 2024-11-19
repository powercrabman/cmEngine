#include "EnginePch.h"
#include "Log.h"

namespace cmEngine
{
	struct LogConfig : public JsonMetaData
	{
		std::array<ImVec4, static_cast<UINT>(eLogLevel::Count)> logLevelColor = {};

		JSON_STRUCT_BODY(
			LogConfig,
			L"SystemConfig.json",
			logLevelColor
		);
	};

	//===================================================

	void Log::Initialize()
	{
		mLogList.clear();
		mLogList.reserve(LOG_LIST_CAPACITY);

		LogConfig cf = {};
		JsonSerializer::Deserialize(cf);
		LogData::LogLevelColor = cf.logLevelColor;
	}

	void Log::Destory()
	{
		ClearLogList();

		LogConfig cf = {};
		cf.logLevelColor = LogData::LogLevelColor;
		JsonSerializer::Serialize(cf);
	}

}