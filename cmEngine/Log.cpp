#include "EnginePch.h"
#include "Log.h"

namespace cmEngine
{
	void Log::Initialize()
	{
		mLogList.clear();
		mLogList.reserve(LOG_LIST_CAPACITY);
	}

}