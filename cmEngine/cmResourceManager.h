#pragma once

class cmResourceBase;

template <typename Ty>
concept DerivedOfResource = std::is_base_of<cmResourceBase, Ty>::value;

class cmResourceManager
{
	ENGINE_MODULE_BODY();
public:
	virtual ~cmResourceManager() = default;

	void Initialize();

	std::filesystem::path GetClientResourcePath() const { return mClientResourcePath; }
	std::filesystem::path GetCommonResourcePath() const { return mCommonResourcePath; }

	std::filesystem::path GetClientResourcePath(std::wstring_view inPath) const { return mClientResourcePath / inPath; }
	std::filesystem::path GetCommonResourcePath(std::wstring_view inPath) const { return mCommonResourcePath / inPath; }

	template <DerivedOfResource Ty>
	Ty* CreateResource(std::string_view inName)
	{
		std::unique_ptr<Ty> inst{ new Ty() };
		Ty* ret = inst.get();

		auto iter = mResourceRepo.find(TYPE_ID(Ty));
		if (iter == mResourceRepo.end())
		{
			auto [newIter, _] = mResourceRepo.emplace(TYPE_ID(Ty), ResourceMap{});
			iter = newIter;
		}

		std::string str(inName);
		auto mapIter = iter->second.find(str);
		if (mapIter != iter->second.end())
		{
			LOG_ERROR("Already exist Resource!");
			return static_cast<Ty*>(mapIter->second.get());
		}

		iter->second[str] = std::move(inst);
		return ret;
	}

	template <DerivedOfResource Ty>
	Ty* FindResourceOrNull(std::string_view inName)
	{
		auto iter = mResourceRepo.find(TYPE_ID(Ty));

		if (iter == mResourceRepo.end())
		{
			ASSERT(false, "Find Resource Fail.");
			LOG_ERROR("Find Resource Fail.");
			return nullptr;
		}

		std::string str = inName.data();
		auto mapIter = iter->second.find(str);	

		if (mapIter == iter->second.end())
		{
			ASSERT(false, "Find Resource Fail.");
			LOG_ERROR("Find Resource Fail.");
			return nullptr;
		}

		return static_cast<Ty*>(mapIter->second.get());
	}

private:
	cmResourceManager();

private:
	std::filesystem::path mClientResourcePath;
	std::filesystem::path mCommonResourcePath;

	using ResourceMap = std::unordered_map<std::string, std::unique_ptr<cmResourceBase>>;
	std::unordered_map<cmTypeID, ResourceMap> mResourceRepo;
};