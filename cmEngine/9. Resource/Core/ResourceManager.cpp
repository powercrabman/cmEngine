#include "0. cmEngine/cmEngine.h"
#include "ResourceManager.h"

namespace cmEngine
{
	ResourceManager::ResourceManager()
	{
		LOG_INFO("Resource Manager Initialize Done.");

		// 府家胶 叼泛配府 积己
		namespace fs = std::filesystem;
		mLocalDirectory = fs::current_path();
		mLocalResourcesDirectory = mLocalDirectory / L"Resources";
		fs::create_directory(mLocalResourcesDirectory);
		fs::create_directory(mLocalResourcesDirectory / L"Texture");
		fs::create_directory(mLocalResourcesDirectory / L"Sprite");
		fs::create_directory(mLocalResourcesDirectory / L"Flipbook");
		fs::create_directory(mLocalResourcesDirectory / L"ShaderSet");

		EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) { Destroy(); });
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
}
