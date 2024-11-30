#include "0. cmEngine/cmEngine.h"
#include "JsonSerializer.h"


namespace cmEngine
{
	JsonSerializer::JsonSerializer()
	{
		mDefaultJsonPath = std::filesystem::current_path() / std::filesystem::path("Json");
		if (!std::filesystem::exists(mDefaultJsonPath))
		{
			std::filesystem::create_directory(mDefaultJsonPath);
		}
		EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e)
		{
			Destroy();
		});
	}

	JsonSerializer::~JsonSerializer()
	{
		std::ofstream f = {};

		for (auto iter : mJsonRepo)
		{
			f.open(mDefaultJsonPath / iter.first);

			if (!f.is_open())
			{
				assert(false);
				f.clear();
				continue;
			}

			assert(!iter.second.is_null());
			f << iter.second.dump(4);

			f.close();
			f.clear();
		}

		mJsonRepo.clear();
	}
}
