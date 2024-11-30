#include "EnginePch.h"
#include "ResourceManager.h"
#include "Texture.h"

namespace cmEngine
{
	void ResourceManager::Initialize()
	{
		LOG_INFO("Resource Manager Initialize Done.");

		// Engine 리소스 로드
		LoadResourceBundleJson(L"C:\\Users\\Ahnjiwoo\\Desktop\\Projects\\cmEngine\\cmEngine\\Config\\EngineTexture.json", true);
	}

	Scope<ResourceBase> ResourceManager::CreateResourceByTypeEx(eResourceType inType)
	{
		Scope<ResourceBase> res = nullptr;

		switch (inType)
		{
		case eResourceType::Texture:
			res = Scope<Texture>(new Texture);
			break;
		case eResourceType::Sprite:
			res = Scope<Sprite>(new Sprite);
			break;
		case eResourceType::Flipbook:
			res = Scope<Flipbook>(new Flipbook);
			break;
		case eResourceType::ShaderSet:
			res = Scope<ShaderSet>(new ShaderSet);
			break;
		default:
			assert(false);
			break;
		}

		return res;
	}

	ResourceBase* ResourceManager::TryFindResourceByType(eResourceType inType, std::string_view inName)
	{
		const auto& map = mResourceRepo[static_cast<uint32>(inType)];
		auto iter = map.find(inName.data());
		if (iter == map.end())
		{
			return nullptr;
		}
		else
		{
			return iter->second.get();
		}
	}

	ResourceBase* ResourceManager::CreateResourceByType(eResourceType inType, std::string_view inName)
	{
		Scope<ResourceBase> res = CreateResourceByTypeEx(inType);
		auto& map = mResourceRepo[static_cast<uint32>(inType)];
		res->mName = inName;
		auto [iter, ret] = map.emplace(inName.data(), std::move(res));
		if (!ret) { ENGINE_LOG_ERROR("{} : Resource Create Error", inName); }
		return iter->second.get();
	}

	void ResourceManager::LoadResourceBundleJson(std::wstring_view inJsonPath, bool useAbsolutePath)
	{
		json& json = JsonSerializer::GetJson(inJsonPath, useAbsolutePath);

		for (auto [key, value] : json.items())
		{
			eResourceType type = value["resourceType"];

			Scope<ResourceBase> res = CreateResourceByTypeEx(type);
			if (res->LoadJsonFromSection(inJsonPath, key))
			{
				auto& map = mResourceRepo[static_cast<uint32>(type)];
				auto [iter, _] = map.emplace(res->GetName(), std::move(res));
			}
		}
	}
}
