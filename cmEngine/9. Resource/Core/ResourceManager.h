#pragma once
namespace cmEngine
{
	class ResourceBase;

	template <typename ResourceType>
	concept ResourceConstraint = std::is_base_of_v<ResourceBase, ResourceType>&& requires { ResourceType::sResourceType; };

	class ResourceManager
	{
		SINGLETON(ResourceManager);
		using ResourceMap = std::unordered_map<std::string, Scope<ResourceBase>>;
		using ResourceMapIterator = std::unordered_map<std::string, Scope<ResourceBase>>::iterator;

	public:
		template<ResourceConstraint ResourceType>
		ResourceType* TryFindResource(std::string_view inString);

		template<ResourceConstraint ResourceType>
		ResourceType* LoadResourceFromFile(std::wstring_view inFilePath);

		template<ResourceConstraint ResourceType>
		ResourceType* LoadResourceFromSection(std::wstring_view inFilePath, std::string_view inSection);

		template<ResourceConstraint ResourceType>
		ResourceType* CreateEmptyResource(std::string_view inName);

		template<ResourceConstraint ResourceType>
		ResourceMapIterator GetBegin() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].begin(); }

		template<ResourceConstraint ResourceType>
		ResourceMapIterator GetEnd() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].end(); }

		template<ResourceConstraint ResourceType>
		size_t				GetResourceListSize() { return mResourceRepo[static_cast<uint32>(ResourceType::sResourceType)].size(); }

		const std::filesystem::path& GetLocalDirectoryPath() const { return mLocalDirectory; }
		const std::filesystem::path& GetLocalResourceDirectoryPath() const { return mLocalResourcesDirectory; }

	private:
		ResourceManager();
		~ResourceManager() = default;

		template <ResourceConstraint ResourceType>
		ResourceType* LoadResourceEx(Scope<ResourceType>& inLoadedResource);

		Scope<ResourceBase> CreateResourceByTypeEx(eResourceType inType);

		std::filesystem::path mLocalDirectory = {};
		std::filesystem::path mLocalResourcesDirectory = {};

		std::array<ResourceMap, static_cast<uint32>(eResourceType::Count)> mResourceRepo = {};
	};

	//===================================================
	//			          Inline
	//===================================================

	template <ResourceConstraint ResourceType>
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

	template <ResourceConstraint ResourceType>
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

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eResourceType inType)
	{
		switch (inType)
		{
		case cmEngine::eResourceType::Texture:		return "Texture";
		case cmEngine::eResourceType::Sprite:		return "Sprite";
		case cmEngine::eResourceType::Flipbook:		return "Flipbook";
		case cmEngine::eResourceType::ShaderSet:	return "ShaderSet";
		default: assert(false);						return "Undefined";
		}
	}
}
