#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	class ResourceBase;

	template <typename ResourceType>
	concept ResourceConstraint = std::is_base_of_v<ResourceBase, ResourceType> && requires { ResourceType::ResourceType; };

	class ResourceManager
	{
		friend class EngineCore;

		using ResourceMap          = std::unordered_map<std::string, Scope<ResourceBase>>;
		using ResourceMapIterator  = std::unordered_map<std::string, Scope<ResourceBase>>::iterator;

	public:
		template<ResourceConstraint ResourceType>
		static ResourceType* TryFindResource(std::string_view inName);

		// this is runtime-function
		static ResourceBase* TryFindResourceByType(eResourceType inType, std::string_view inName);

		// this is runtime-function
		static ResourceBase* CreateResourceByType(eResourceType inType, std::string_view inName);

		// this is runtime-function
		static void LoadResourceBundleJson(std::wstring_view inJsonPath, bool useAbsolutePath = false);

		template<ResourceConstraint ResourceType>
		static ResourceType* LoadResourceFromFile(std::wstring_view inFilePath);

		template<ResourceConstraint ResourceType>
		static ResourceType* LoadResourceFromSection(std::wstring_view inFilePath, std::string_view inSection);

		template<ResourceConstraint ResourceType>
		static ResourceType* CreateEmptyResource(std::string_view inName);

		template<ResourceConstraint ResourceType>
		static ResourceMapIterator GetBegin() { return mResourceRepo[static_cast<uint32>(ResourceType::ResourceType)].begin(); }

		template<ResourceConstraint ResourceType>
		static ResourceMapIterator GetEnd() { return mResourceRepo[static_cast<uint32>(ResourceType::ResourceType)].end(); }

	private:
		static void Initialize();
		static void Destroy();

		template <ResourceConstraint ResourceType>
		static ResourceType* LoadResourceEx(Scope<ResourceType>& inLoadedResource);

		static Scope<ResourceBase> CreateResourceByTypeEx(eResourceType inType);

	private:
		inline static std::array<ResourceMap, static_cast<uint32>(eResourceType::Count)> mResourceRepo = {};
	};

	//===================================================
	//			          Inline
	//===================================================

	template <ResourceConstraint ResourceType>
	ResourceType* ResourceManager::TryFindResource(std::string_view inName)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::ResourceType)];

		auto iter = repo.find(inName.data());

		if (iter == repo.end())
		{
			ENGINE_LOG_ERROR("{}::{} is not exist resource!", ToString(ResourceType::ResourceType), inName);
			return nullptr;
		}
		else
		{
			return static_cast<ResourceType*>(iter->second.get());
		}
	}

	template <ResourceConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceFromFile(std::wstring_view inFilePath)
	{
		Scope<ResourceType> resource{ new ResourceType };

		// 로드 성공
		if (resource->LoadJsonFromFile(inFilePath))
		{
			return LoadResourceEx(resource);
		}
		else
		{
			return nullptr;
		}
	}

	template <ResourceConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceFromSection(std::wstring_view inFilePath, std::string_view inSection)
	{
		Scope<ResourceType> resource{ new ResourceType };

		// 로드 성공
		if (resource->LoadJsonFromSection(inFilePath, inSection))
		{
			return LoadResourceEx(resource);
		}
		else
		{
			return nullptr;
		}
	}

	template <ResourceConstraint ResourceType>
	ResourceType* ResourceManager::CreateEmptyResource(std::string_view inName)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::ResourceType)];

		auto [iter, result] = repo.emplace(inName, Scope<ResourceType>(new ResourceType));
		ResourceType* ptr   = static_cast<ResourceType*>(iter->second.get());

		if (result)
		{
			ptr->mName = inName;
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

	template <ResourceConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceEx(Scope<ResourceType>& inLoadedResource)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::ResourceType)];
		auto [iter, result]        = repo.emplace(inLoadedResource->GetName(), std::move(inLoadedResource));
		ResourceType* ptr          = static_cast<ResourceType*>(iter->second.get());

		if (result)
		{
			ENGINE_LOG_INFO("{}::{} create done.", ToString(ResourceType::ResourceType), ptr->GetName());
			return ptr;
		}
		else
		{
			assert(false);
			ENGINE_LOG_ERROR("{}::{} is already exist resource!", ToString(ResourceType::ResourceType), ptr->GetName());
			return ptr;
		}
	}

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eResourceType inType)
	{
		switch (inType)
		{
		case cmEngine::eResourceType::Texture:		return "texture";
		case cmEngine::eResourceType::Sprite:		return "Sprite";
		case cmEngine::eResourceType::Flipbook:		return "Flipbook";
		case cmEngine::eResourceType::ShaderSet:	return "ShaderSet";
		default: assert(false);						return "Undefined";
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
