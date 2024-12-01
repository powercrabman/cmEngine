#pragma once
namespace cmEngine
{
	class ResourceBase;

	template <typename ResourceType>
	concept AssetConstraint = std::is_base_of_v<ResourceBase, ResourceType>&& requires { ResourceType::sResourceType; };

	class ResourceManager
	{
		SINGLETON(ResourceManager);
		using ResourceMap = std::unordered_map<std::string, Scope<ResourceBase>>;
		using ResourceMapIterator = std::unordered_map<std::string, Scope<ResourceBase>>::iterator;

	public:
		template<AssetConstraint ResourceType>
		ResourceType* TryFindResource(std::string_view inString);

		template<AssetConstraint ResourceType>
		ResourceType* LoadResourceFromFile(std::wstring_view inFilePath);

		template<AssetConstraint ResourceType>
		ResourceType* LoadResourceFromSection(std::wstring_view inFilePath, std::string_view inSection);

		template<AssetConstraint ResourceType>
		ResourceType* CreateEmptyResource(std::string_view inName);

		template<AssetConstraint ResourceType>
		ResourceMapIterator GetBegin() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].begin(); }
		ResourceMapIterator GetBegin(eResourceType inType) { return mResourceRepo[static_cast<uint32>(inType)].begin(); }

		template<AssetConstraint ResourceType>
		ResourceMapIterator GetEnd() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].end(); }
		ResourceMapIterator GetEnd(eResourceType inType) { return mResourceRepo[static_cast<uint32>(inType)].end(); }

		template<AssetConstraint ResourceType>
		size_t				GetResourceListSize() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].size(); }
		size_t				GetResourceListSize(eResourceType inType) { return mResourceRepo[static_cast<uint32>(inType)].size(); }

		const std::filesystem::path& GetLocalDirectoryPath() const { return mLocalDirectory; }
		const std::filesystem::path& GetLocalResourceDirectoryPath() const { return mLocalResourcesDirectory; }

	private:
		ResourceManager();
		~ResourceManager() = default;

		template <AssetConstraint ResourceType>
		ResourceType* LoadResourceEx(Scope<ResourceType>& inLoadedResource);

		Scope<ResourceBase> CreateResourceByTypeEx(eResourceType inType);

		std::filesystem::path mLocalDirectory = {};
		std::filesystem::path mLocalResourcesDirectory = {};

		std::array<ResourceMap, static_cast<uint32>(eResourceType::Count)> mResourceRepo = {};
	};

	//===================================================
	//			          Inline
	//===================================================

	template <AssetConstraint ResourceType>
	ResourceType* ResourceManager::TryFindResource(std::string_view inString)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)];

		auto iter = repo.find(inString.data());

		if (iter == repo.end())
		{
			ENGINE_LOG_ERROR("{}::{} is not exist resource!", ToString(ResourceType::sResourceType), inString);
			return nullptr;
		}
		else
		{
			return static_cast<ResourceType*>(iter->second.get());
		}
	}

	template <AssetConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceFromFile(std::wstring_view inFilePath)
	{
		Scope<ResourceType> resource{ new ResourceType };

		// �ε� ����
		if (resource->LoadJsonFromFile(inFilePath))
		{
			return LoadResourceEx(resource);
		}
		else
		{
			return nullptr;
		}
	}

	template <AssetConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceFromSection(std::wstring_view inFilePath, std::string_view inSection)
	{
		Scope<ResourceType> resource{ new ResourceType };

		// �ε� ����
		if (resource->LoadJsonFromSection(inFilePath, inSection))
		{
			return LoadResourceEx(resource);
		}
		else
		{
			return nullptr;
		}
	}

	template <AssetConstraint ResourceType>
	ResourceType* ResourceManager::CreateEmptyResource(std::string_view inName)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)];

		auto [iter, result] = repo.emplace(inName.data(), Scope<ResourceType>(new ResourceType));
		ResourceType* ptr = static_cast<ResourceType*>(iter->second.get());

		if (result)
		{
			ptr->mName = inName;
			ENGINE_LOG_INFO("{}::{} create done.", ToString(ResourceType::sResourceType), inName);
			return ptr;
		}
		else
		{
			assert(false);
			ENGINE_LOG_ERROR("{}::{} is already exist resource!", ToString(ResourceType::sResourceType), inName);
			return ptr;
		}
	}

	template <AssetConstraint ResourceType>
	ResourceType* ResourceManager::LoadResourceEx(Scope<ResourceType>& inLoadedResource)
	{
		ResourceMap& repo = mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)];
		auto [iter, result] = repo.emplace(inLoadedResource->GetName(), std::move(inLoadedResource));
		ResourceType* ptr = static_cast<ResourceType*>(iter->second.get());

		if (result)
		{
			ENGINE_LOG_INFO("{}::{} create done.", ToString(ResourceType::sResourceType), ptr->GetName());
			return ptr;
		}
		else
		{
			assert(false);
			ENGINE_LOG_ERROR("{}::{} is already exist resource!", ToString(ResourceType::sResourceType), ptr->GetName());
			return ptr;
		}
	}
}
