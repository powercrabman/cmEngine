#pragma once
#include "ResourceBase.h"

class ResourceBase;

namespace cmEngine
{
	enum class eResourceType
	{
		Texture,
		Sprite,
		Flipbook,

		Count
	};

	class ResourceManager
	{
		friend class EngineCore;
	public:
		static std::wstring GetClientResourcePath() { return mClientResourcePath.c_str(); }
		static std::wstring GetCommonResourcePath() { return mCommonResourcePath.c_str(); }
		static std::wstring GetClientResourcePath(std::wstring_view inPath);
		static std::wstring GetCommonResourcePath(std::wstring_view inPath);

		template<typename ResourceType>
		static ResourceType* FindResourceOrNull(std::string_view inName)
		{
			ResourceUnorderedMap& repo = mResourceRepo[(uint32)ResourceType::ResourceType];
			
			auto iter = repo.find(inName);

			if (iter == repo.end())
			{
				ENGINE_LOG_ERROR("{}::{} is not exist resource!", ToString(ResourceType::ResourceType), inName);
				return nullptr;
			}
			else
			{
				return iter->second.get();
			}
		}

		template<typename ResourceType>
		static ResourceType* CreateResource(std::string_view inName)
		{
			ResourceUnorderedMap& repo = mResourceRepo[(uint32)ResourceType::ResourceType];

			auto [iter, result] = repo.emplace(inName, std::make_unique<ResourceType>(inName));
			ResourceType* ptr = static_cast<ResourceType*>(iter->second.get());

			if (result)
			{
				ENGINE_LOG_INFO("{}::{} create done.", ToString(ResourceType::ResourceType), inName);
				return ptr;
			}
			else
			{
				assert(false);
				ENGINE_LOG_ERROR("{}::{} is already exist resource!", ToString(ResourceType::ResourceType), inName);
				return ptr;
			}
		}
		
	private:
		static void Initialize();
		static void Destroy();

	private:
		static std::filesystem::path mClientResourcePath;
		static std::filesystem::path mCommonResourcePath;

		using ResourceUnorderedMap = std::unordered_map<std::string, std::unique_ptr<ResourceBase>>;
		static std::array<ResourceUnorderedMap, (uint32)eResourceType::Count> mResourceRepo;
	};

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eResourceType inType)
	{
		switch (inType)
		{
		case cmEngine::eResourceType::Texture:  return "Texture";
		case cmEngine::eResourceType::Sprite:	return "Sprite";
		case cmEngine::eResourceType::Flipbook: return "Flipbook";
		default: assert(false);					return "Undefined";
		}
	}

	inline void ResourceManager::Destroy()
	{
		for (auto& maps : mResourceRepo)
		{
			maps.clear();
		}
	}
}